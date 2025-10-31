function build_mod(mod_name, targetMajor, targetMinor, targetPatch, automated_build, config)
    config = config or {}

    add_rules("plugin.vsxmake.autoupdate")
    set_languages("c++23")

    -- Allow flexible configuration
    local extra_deps          = config.extra_deps or {}
    local extra_links         = config.extra_links or {}
    local extra_include_dirs  = config.extra_include_dirs or {}
    local extra_header_files  = config.extra_header_files or {}
    local extra_files         = config.extra_files or {}

    local platform = config.platform or "win-client"

    local modFolder
    local amethystApiPath

    -- Automated builds use project-local paths
    if automated_build then
        modFolder = path.join(os.projectdir(), "dist")
        amethystApiPath = path.join(os.projectdir(), "Amethyst", "AmethystAPI")
    else
        set_symbols("debug")
        local amethystSrc = os.getenv("AMETHYST_SRC")
        amethystApiPath = amethystSrc and path.join(amethystSrc, "AmethystAPI") or nil

        local amethystFolder

        if platform == "win-client" then
            amethystFolder = path.join(
                os.getenv("localappdata"),
                "Packages",
                "Microsoft.MinecraftUWP_8wekyb3d8bbwe",
                "LocalState",
                "games",
                "com.mojang",
                "amethyst"
            )
        elseif platform == "win-server" then
            amethystFolder = path.join(
                os.getenv("AMETHYST_BDS_TARGET"),
                "amethyst"
            )
        end

        modFolder = path.join(
            amethystFolder,
            "mods",
            string.format("%s@0.0.0-dev", mod_name)
        )
    end

    local binary_dir = path.join(modFolder, platform)

    -- Only include AmethystAPI if present on disk at configure-time
    if amethystApiPath and os.isdir(amethystApiPath) then
        includes(amethystApiPath)
        includes(path.join(amethystApiPath, "packages", "libhat"))
    end

    -- RelWithDebInfo flags
    add_cxxflags("/O2", "/DNDEBUG", "/MD", "/EHsc", "/FS", "/MP")
    add_ldflags("/OPT:REF", "/OPT:ICF", "/INCREMENTAL:NO", {force = true})

    set_targetdir(binary_dir)

    package("Runtime-Importer")
        set_kind("binary")
        set_homepage("https://github.com/AmethystAPI/Runtime-Importer")
        set_description("The runtime importer enables importing functions and variables from the game just by defining annotations in header files")

        on_load(function (package)
            import("net.http")
            import("core.base.json")
            import("utils.archive")

            local releases_file = path.join(os.tmpdir(), "runtime-importer.releases.json")
            http.download("https://api.github.com/repos/AmethystAPI/Runtime-Importer/releases/latest", releases_file)

            local importer_dir = path.join(os.curdir(), ".importer");
            local bin_dir = path.join(importer_dir, "bin");
            local release = json.loadfile(releases_file)
            local latest_tag = release.tag_name
            local installed_version_file = path.join(importer_dir, "version.txt")
            local installed_version = os.isfile(installed_version_file) and io.readfile(installed_version_file) or "None"
            local should_reinstall = installed_version ~= latest_tag

            local is_first_install = should_reinstall and installed_version == "None"

            if should_reinstall and not is_first_install and not automated_build then
                io.write("Runtime-Importer is outdated (installed: " .. installed_version .. ", latest: " .. latest_tag .. "), install? (y/n): ")
                io.flush()
                local answer = (io.read() or ""):lower()
                should_reinstall = (answer == "" or answer == "y")
            end

            if should_reinstall then
                local url = "https://github.com/AmethystAPI/Runtime-Importer/releases/latest/download/Runtime-Importer.zip"
                local zipfile = path.join(os.tmpdir(), "Runtime-Importer.zip")
                print("Installing Runtime-Importer " .. latest_tag .. "...")

                http.download(url, zipfile)
                archive.extract(zipfile, bin_dir)
                io.writefile(installed_version_file, latest_tag)
            end

            local generated_dir = path.join(importer_dir)
            local pch_file = path.join(generated_dir, "pch.hpp.pch")
            local should_regenerate_pch = os.exists(pch_file) == false or should_reinstall

            if should_regenerate_pch then
                print("Generating precompiled header of STL...")
                os.mkdir(generated_dir)

                local clang_args = {
                    path.join(bin_dir, "clang++.exe"),
                    "-x", "c++-header",
                    path.join(path.join(bin_dir, "utils"), "pch.hpp"),
                    "-std=c++23",
                    "-fms-extensions",
                    "-fms-compatibility",
                    "-o", pch_file
                }
                os.exec(table.concat(clang_args, " "))
            end
        end)
        
        on_install(function (package)
        end)
    package_end()

    add_requires("Runtime-Importer", {system = false})
    set_project(mod_name)

    target(mod_name)
        set_languages("c++23")
        set_kind("shared")
        set_toolchains("msvc")
        add_deps("AmethystAPI", "libhat")

        -- Hard fail if AmethystAPI is missing
        on_load(function (t)
            if not (amethystApiPath and os.isdir(amethystApiPath)) then
                raise("AmethystAPI not found at: " .. tostring(amethystApiPath) ..
                    "\nCI: ensure repo is checked out to Amethyst/AmethystAPI" ..
                    "\nLocal: set AMETHYST_SRC to point to your Amethyst clone.")
            end
        end)


        set_policy("build.across_targets_in_parallel", true)

        -- Main mod sources
        add_files("src/**.cpp")
        add_includedirs("src", { public = true })
        add_headerfiles("src/**.hpp")

        -- Apply user-specified extras
        for _, dir in ipairs(extra_include_dirs) do
            add_includedirs(dir, { public = true })
        end

        for _, hdr in ipairs(extra_header_files) do
            add_headerfiles(hdr, { public = true })
        end

        for _, f in ipairs(extra_files) do
            add_files(f)
        end

        for _, dep in ipairs(extra_deps) do
            add_deps(dep)
        end

        for _, lib in ipairs(extra_links) do
            add_links(lib)
        end

        if platform == "win-client" then
            add_defines("CLIENT")
            add_defines("WIN_CLIENT")
        elseif platform == "win-server" then
            add_defines("SERVER")
            add_defines("WIN_SERVER")
        end

        add_packages("AmethystAPI", "libhat")

        libs_folder = path.join(".importer", platform)

        add_links("user32", "windowsapp", path.join(libs_folder, "Minecraft.Windows.*.lib"), "Dbghelp")

        add_defines(
            string.format('MOD_TARGET_VERSION_MAJOR=%d', targetMajor),
            string.format('MOD_TARGET_VERSION_MINOR=%d', targetMinor),
            string.format('MOD_TARGET_VERSION_PATCH=%d', targetPatch),
            'ENTT_PACKED_PAGE=128',
            'AMETHYST_EXPORTS'
        )

        before_build(function (target)
            local importer_dir = path.join(os.curdir(), ".importer");
            local generated_dir = path.join(importer_dir)
            local input_dir = path.join(amethystApiPath, "src"):gsub("\\", "/")
            local include_dir = path.join(amethystApiPath, "include"):gsub("\\", "/")

            local gen_sym_args = {
                ".importer/bin/Amethyst.SymbolGenerator.exe",
                "--input", string.format("%s", input_dir),
                "--output", string.format("%s", generated_dir),
                "--filters", "mc",
                "--platform " .. platform,
                "--",
                "-x c++",
                "-include-pch", path.join(generated_dir, "pch.hpp.pch"),
                "-std=c++23",
                "-fms-extensions",
                "-fms-compatibility",
                string.format('-I%s', include_dir),
                string.format('-I%s', input_dir)
            }
            print('Generating *.symbols.json files for headers...')
            os.exec(table.concat(gen_sym_args, " "))

            local gen_lib_args = {
                ".importer/bin/Amethyst.LibraryGenerator.exe",
                "--platform " .. platform,
                "--input", string.format("%s", generated_dir),
                "--output", string.format("%s", generated_dir)
            }
            print('Generating Minecraft.Windows.lib file...')
            os.exec(table.concat(gen_lib_args, " "))
        end)

        after_build(function (target)
            local importer_dir = path.join(os.curdir(), ".importer");
            local generated_dir = path.join(importer_dir)
            local src_json = path.join("mod.json")

            local mod_json = io.readfile(src_json)

            if not automated_build then
                mod_json = mod_json:gsub('("version"%s*:%s*")([^"]*)(")', '%1' .. "0.0.0-dev" .. '%3')
            end

            local dst_json = path.join(modFolder, "mod.json")
            if not os.isdir(modFolder) then
                os.mkdir(modFolder)
            end

            io.writefile(dst_json, mod_json)

            local tweaker_args = {
                ".importer/bin/Amethyst.ModuleTweaker.exe",
                "--platform", platform,
                "--module", target:targetfile(),
                "--input", string.format("%s", generated_dir),
                "--output", string.format("%s", generated_dir)
            }
            print('Tweaking output file...')
            os.exec(table.concat(tweaker_args, " "))    
        end)
end