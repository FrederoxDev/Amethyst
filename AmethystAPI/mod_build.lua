function build_mod(mod_name, automated_build, config)
    config = config or {}

    add_rules("plugin.vsxmake.autoupdate")
    set_languages("c++23")
    
    -- Allow flexible configuration
    local extra_deps          = config.extra_deps or {}
    local extra_links         = config.extra_links or {}
    local extra_include_dirs  = config.extra_include_dirs or {}
    local extra_header_files  = config.extra_header_files or {}
    local extra_files         = config.extra_files or {}
    local mc_headers_path     = config.mc_headers_path or nil
    local platform = config.platform or "win-client"
    
    local BUILD_SCRIPT_VERSION = 2
    local MOD_BUILD_SCRIPT_VERSION = config.MOD_BUILD_SCRIPT_VERSION or 1

    if not automated_build then -- choco downloads 3.0.1 - but not important for CI builds since no .sln is generated
        set_xmakever("3.0.4") -- 3.0.x versions before this have a bug where a .sln cant be generated with options
    end
    
    if MOD_BUILD_SCRIPT_VERSION ~= BUILD_SCRIPT_VERSION then
        print("The mods xmake.lua is in an outdated format, consider updating! Mods version: " .. tostring(MOD_BUILD_SCRIPT_VERSION) .. ", Build script version: " .. tostring(BUILD_SCRIPT_VERSION) .. 
            "\n\tLatest version here: https://github.com/AmethystAPI/Amethyst-Template/blob/main/xmake.lua")
    end

    local modFolder
    local amethystApiPath

    local amethystSrc = os.getenv("AMETHYST_SRC")
    amethystApiPath = amethystSrc and path.join(amethystSrc, "AmethystAPI") or nil

    if automated_build then
        -- Raw shipping layout: the archive is written beside it as dist/<name>@<version>.amethyst.
        modFolder = path.join(os.projectdir(), "dist", "unpackaged")
    else
        set_symbols("debug")

        local amethystFolder

        if platform == "win-client" then
            modFolder = path.join(
                os.getenv("appdata"),
                "Amethyst",
                "Launcher",
                "Mods",
                string.format("%s@0.0.0-dev", mod_name)
            )
        elseif platform == "win-server" then
            amethystFolder = path.join(
                os.getenv("AMETHYST_BDS_TARGET"),
                "amethyst"
            )

            modFolder = path.join(
                amethystFolder,
                "mods",
                string.format("%s@0.0.0-dev", mod_name)
            )
        end
    end

    local binary_dir = path.join(modFolder, platform)

    -- Resolve Runtime-Importer bin directory (shared across on_load, before_build, after_build)
    local importer_bin_dir = path.join(os.curdir(), ".importer", "bin")
    local local_importer = os.getenv("RUNTIME_IMPORTER_PATH")
    if local_importer and os.isdir(local_importer) then
        importer_bin_dir = local_importer
        print("Using local Runtime-Importer from: " .. local_importer)
    end

    -- Only include AmethystAPI if present on disk at configure-time
    if amethystApiPath and os.isdir(amethystApiPath) then
        PLATFORM = platform -- This is kinda horrible, declare a non local variable here which is read in the xmake.lua of AmethystAPI 
        includes(amethystApiPath)
        includes(path.join(amethystApiPath, "packages", "libhat"))
    end

    includes(mc_headers_path)

    -- RelWithDebInfo flags
    add_cxxflags("/O2", "/DNDEBUG", "/MD", "/EHsc", "/FS", "/MP")
    add_ldflags("/OPT:REF", "/OPT:ICF", "/INCREMENTAL:NO", {force = true})

    package("Runtime-Importer")
        set_kind("binary")
        set_homepage("https://github.com/AmethystAPI/Runtime-Importer")
        set_description("The runtime importer enables importing functions and variables from the game just by defining annotations in header files")

        on_load(function (package)
            local importer_dir = path.join(os.curdir(), ".importer");
            local bin_dir = importer_bin_dir
            local should_reinstall = false

            if not local_importer then
                import("net.http")
                import("core.base.json")
                import("utils.archive")

                local releases_file = path.join(os.tmpdir(), "runtime-importer.releases.json")
                http.download("https://api.github.com/repos/AmethystAPI/Runtime-Importer/releases/latest", releases_file)

                local release = json.loadfile(releases_file)
                local latest_tag = release.tag_name
                local installed_version_file = path.join(importer_dir, "version.txt")
                local installed_version = os.isfile(installed_version_file) and io.readfile(installed_version_file) or "None"
                should_reinstall = installed_version ~= latest_tag

                local is_first_install = should_reinstall and installed_version == "None"

                -- Only ask when a terminal is there to answer. A non-interactive shell never returns from
                -- io.read(), which stalls the build with no output, so take the update instead of asking.
                local interactive = false
                try
                {
                    function () interactive = io.stdin:isatty() end,
                    catch { function () interactive = false end }
                }

                if should_reinstall and not is_first_install and not automated_build and interactive then
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
            end

            local generated_dir = path.join(importer_dir)
            local pch_file = path.join(generated_dir, "pch.hpp.pch")
            local should_regenerate_pch = os.exists(pch_file) == false or should_reinstall

            -- clang++ and pch.hpp always come from the installed release, not the local override
            local installed_bin_dir = path.join(importer_dir, "bin")
            if should_regenerate_pch then
                print("Generating precompiled header of STL...")
                os.mkdir(generated_dir)

                local clang_args = {
                    path.join(installed_bin_dir, "clang++.exe"),
                    "-x", "c++-header",
                    path.join(path.join(installed_bin_dir, "utils"), "pch.hpp"),
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
        set_toolchains("clang-cl")
        if automated_build then
            -- Omitting debug symbols is not the same as suppressing them: without these the
            -- linker still emits a CodeView record naming the mod's PDB.
            set_symbols("none")
            add_ldflags("/DEBUG:NONE", { force = true })
        else
            set_targetdir(binary_dir)
            add_ldflags("/RELEASE", { force = true })
        end
        add_deps("AmethystAPI", "libhat", "MC")

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
            add_defines("CLIENT", "WIN_CLIENT", {  public = true })
        elseif platform == "win-server" then
            add_defines("SERVER", "WIN_SERVER", {  public = true })
        end

        if automated_build then
            add_defines("AMETHYST_OBFUSCATE", { public = true })
            -- Strip absolute source paths from __FILE__ so obfuscated binaries don't
            -- embed user-specific filesystem paths. /d1trimfile rewrites any __FILE__
            -- whose prefix matches the given path to start at the remainder.
            local trim_roots = { os.projectdir() }
            if amethystSrc then table.insert(trim_roots, amethystSrc) end
            for _, root in ipairs(trim_roots) do
                add_cxflags("/d1trimfile:" .. root, { force = true })
            end
        end

        add_packages("AmethystAPI", "libhat")

        libs_folder = path.join(".importer", platform)

        add_links("user32", "windowsapp", "Dbghelp")
        add_linkdirs(libs_folder)
        for _, f in ipairs(os.files(path.join(libs_folder, "Minecraft.Windows.*.lib"))) do
            add_links(f)
        end

        add_defines(
            'ENTT_PACKED_PAGE=128',
            'ENTT_NO_MIXIN',
            'AMETHYST_EXPORTS'
        )

        before_build(function (target)
            local importer_dir = path.join(os.curdir(), ".importer");

            local generated_dir = path.join(importer_dir)
            local input_dir = path.join(amethystApiPath, "src"):gsub("\\", "/")
            local include_dir = path.join(amethystApiPath, "include"):gsub("\\", "/")

            local pch_file = path.join(generated_dir, "pch.hpp.pch")
            local installed_bin_dir = path.join(importer_dir, "bin")
            local pch_src = path.join(installed_bin_dir, "utils", "pch.hpp")
            local clang_exe = path.join(installed_bin_dir, "clang++.exe")
            -- The PCH is built by, and later consumed with, this exact clang++.
            -- A PCH left over from a previous Runtime-Importer (a different
            -- clang++) is rejected at consume time with a fatal ASTReadError, and
            -- a changed pch.hpp yields stale STL decls. Rebuild when the PCH is
            -- missing OR older than either input (the clang++ binary or pch.hpp)
            -- so it self-heals instead of requiring a manual delete.
            local pch_stale = not os.isfile(pch_file)
            if not pch_stale then
                local pch_mtime = os.mtime(pch_file)
                if (os.isfile(clang_exe) and os.mtime(clang_exe) > pch_mtime)
                   or (os.isfile(pch_src) and os.mtime(pch_src) > pch_mtime) then
                    pch_stale = true
                end
            end
            if pch_stale then
                print("Generating precompiled header of STL...")
                os.mkdir(generated_dir)
                os.exec(table.concat({
                    '"' .. clang_exe .. '"',
                    "-x", "c++-header",
                    '"' .. pch_src .. '"',
                    "-std=c++23",
                    "-fms-extensions",
                    "-fms-compatibility",
                    "-o", '"' .. pch_file .. '"'
                }, " "))
            end

            -- Build SymbolGenerator arguments
            local mc_headers_root = os.getenv("MC_HEADERS")

            local gen_sym_args = {
                '"' .. path.join(importer_bin_dir, "Amethyst.SymbolGenerator.exe") .. '"',
                "--input", string.format("%s", input_dir),
            }

            -- Add MC headers as additional input directory for SymbolGenerator
            if mc_headers_root and os.isdir(mc_headers_root) then
                gen_sym_args[#gen_sym_args + 1] = "--input"
                gen_sym_args[#gen_sym_args + 1] = mc_headers_root:gsub("\\", "/")
            end

            -- Remaining CLI args (before the -- separator)
            gen_sym_args[#gen_sym_args + 1] = "--output"
            gen_sym_args[#gen_sym_args + 1] = string.format("%s", generated_dir)
            gen_sym_args[#gen_sym_args + 1] = "--filters"
            gen_sym_args[#gen_sym_args + 1] = "mc"
            gen_sym_args[#gen_sym_args + 1] = "--platform " .. platform

            -- Build Clang arguments and write to a response file to avoid command line length limits
            -- One argument per line; flags with separate values must be on separate lines
            local clang_args = {
                "-x",
                "c++",
                "-include-pch",
                path.join(generated_dir, "pch.hpp.pch"):gsub("\\", "/"),
                "-ferror-limit=0",
                "-std=c++23",
                "-fms-extensions",
                "-fms-compatibility",
                "-Wno-c++11-narrowing",
                string.format('-I%s', include_dir),
                string.format('-I%s', input_dir),
            }

            -- Add MC headers include directories so Clang can resolve includes
            -- First add the MC_HEADERS root itself (Generated.cpp uses paths relative to it)
            if mc_headers_root and os.isdir(mc_headers_root) then
                clang_args[#clang_args + 1] = string.format('-I%s', mc_headers_root:gsub("\\", "/"))
            end
            -- Then add the MC target's public include directories
            local mc_dep = target:dep("MC")
            if mc_dep then
                local inc_dirs = mc_dep:get("includedirs")
                if inc_dirs then
                    for _, dir in ipairs(inc_dirs) do
                        local abs = path.absolute(dir):gsub("\\", "/")
                        clang_args[#clang_args + 1] = string.format('-I%s', abs)
                    end
                end
                local defs = mc_dep:get("defines")
                if defs then
                    for _, def in ipairs(defs) do
                        clang_args[#clang_args + 1] = string.format('-D%s', def)
                    end
                end
            end

            local response_file = path.join(generated_dir, "clang_args.txt")
            io.writefile(response_file, table.concat(clang_args, "\n"))

            gen_sym_args[#gen_sym_args + 1] = "--"
            gen_sym_args[#gen_sym_args + 1] = "@" .. response_file

            -- SymbolGenerator now also produces Minecraft.Windows.lib in-process; no separate LibraryGenerator invocation.
            print('Generating symbols and library...')
            os.exec(table.concat(gen_sym_args, " "))
        end)

        after_build(function (target)
            local importer_dir = path.join(os.curdir(), ".importer");
            local generated_dir = path.join(importer_dir)
            local src_json = path.join("mod.json")

            local mod_json = io.readfile(src_json)

            if not automated_build then
                -- Rewrite the field, not every "version" in the file: game_builds entries carry one too
                import("core.base.json")
                local manifest = json.decode(mod_json)
                manifest.meta.version = "0.0.0-dev"
                mod_json = json.encode(manifest)
            end

            local dst_json = path.join(modFolder, "mod.json")
            if not os.isdir(modFolder) then
                os.mkdir(modFolder)
            end

            io.writefile(dst_json, mod_json)

            -- For automated builds the link byproducts (.lib/.exp/.pdb) stay in xmake's
            -- build dir. Only the DLL is copied into the shipping folder, which the
            -- tweaker then patches in place.
            local module_to_tweak = target:targetfile()
            if automated_build then
                if not os.isdir(binary_dir) then
                    os.mkdir(binary_dir)
                end
                local shipped_dll = path.join(binary_dir, path.filename(target:targetfile()))
                os.cp(target:targetfile(), shipped_dll)
                module_to_tweak = shipped_dll
            end

            local tweaker_args = {
                '"' .. path.join(importer_bin_dir, "Amethyst.ModuleTweaker.exe") .. '"',
                "--platform", platform,
                "--module", '"' .. module_to_tweak .. '"',
                "--input", string.format("%s", generated_dir),
                "--output", string.format("%s", generated_dir)
            }
            if automated_build then
                table.insert(tweaker_args, "--obfuscate")
            end
            print('Tweaking output file...')
            os.exec(table.concat(tweaker_args, " "))

            if automated_build then
                local f = io.open(module_to_tweak, "rb")
                if not f then
                    raise("Obfuscation audit: could not open shipped DLL '" .. module_to_tweak .. "'")
                end
                local data = f:read("*all")
                f:close()

                -- Normalize-friendly search helpers: binary-safe check for a needle and
                -- its case-variants across forward/back slashes.
                local function contains_literal(haystack, needle)
                    return haystack:find(needle, 1, true) ~= nil
                end
                local function contains_path(haystack, path_needle)
                    -- Match either slash flavor, case-insensitive for the Windows drive/user prefix.
                    local variants = {
                        path_needle,
                        (path_needle:gsub("\\", "/")),
                        (path_needle:gsub("/", "\\")),
                    }
                    for _, v in ipairs(variants) do
                        if contains_literal(haystack, v) then return v end
                        if contains_literal(haystack:lower(), v:lower()) then return v end
                    end
                    return nil
                end

                -- Decode the PE debug directory rather than scanning for "RSDS": those four
                -- bytes occur naturally in .text as instruction encodings, and a scan flags
                -- a clean binary. Only a CODEVIEW (type 2) entry is a real PDB reference.
                local function u16(off) return data:byte(off + 1) + data:byte(off + 2) * 256 end
                local function u32(off)
                    return data:byte(off + 1) + data:byte(off + 2) * 256
                        + data:byte(off + 3) * 65536 + data:byte(off + 4) * 16777216
                end
                local peOff = u32(0x3C)
                local optOff = peOff + 24
                local dataDirOff = (u16(optOff) == 0x20B) and (optOff + 112) or (optOff + 96)
                local debugRva = u32(dataDirOff + 6 * 8)
                local debugSize = u32(dataDirOff + 6 * 8 + 4)
                if debugRva ~= 0 and debugSize >= 28 then
                    local sectionOff = peOff + 24 + u16(peOff + 20)
                    local sectionCount = u16(peOff + 6)
                    local debugOff
                    for i = 0, sectionCount - 1 do
                        local s = sectionOff + i * 40
                        local va, vsize, raw = u32(s + 12), u32(s + 16), u32(s + 20)
                        if debugRva >= va and debugRva < va + vsize then
                            debugOff = raw + (debugRva - va)
                            break
                        end
                    end
                    if debugOff then
                        for i = 0, math.floor(debugSize / 28) - 1 do
                            if u32(debugOff + i * 28 + 12) == 2 then
                                raise("Obfuscation audit FAILED: shipped DLL has a CODEVIEW debug directory entry (PDB reference). Check /DEBUG:NONE and tweaker debug-directory zeroing.")
                            end
                        end
                    end
                end
                if contains_literal(data, ".pdb") then
                    raise("Obfuscation audit FAILED: shipped DLL contains '.pdb' (likely an embedded PDB path).")
                end
                -- Any absolute Windows user-profile path leaks the machine's user name.
                -- Matches `:\Users\` and `:/Users/` case-insensitively without naming anyone.
                local lower = data:lower()
                if lower:find(":\\users\\", 1, true) or lower:find(":/users/", 1, true) then
                    raise("Obfuscation audit FAILED: shipped DLL contains a ':\\Users\\' path. Check /d1trimfile coverage and __FILE__ usage.")
                end
                -- Dynamic: the literal project + AmethystAPI source roots must not appear.
                local leak_roots = { os.projectdir() }
                if amethystSrc then table.insert(leak_roots, amethystSrc) end
                for _, root in ipairs(leak_roots) do
                    local hit = contains_path(data, root)
                    if hit then
                        raise("Obfuscation audit FAILED: shipped DLL contains source root '" .. hit .. "'. Check /d1trimfile coverage.")
                    end
                end
                print("Obfuscation audit passed: no RSDS, .pdb, user-profile paths, or source-root paths in shipped DLL.")
            end

            print("Built '" .. mod_name .. "' for '" .. platform .. "'")
        end)
end

-- Distributable build, available to every mod that includes this script. Reconfigures with
-- automated_build=y so the mod compiles without symbols and the tweaker runs with --obfuscate,
-- stages the shipping layout in dist/unpackaged/, then zips it beside it as
-- dist/<name>@<version>.amethyst. Reads the mod's identity from its own mod.json.
task("package")
    set_category("plugin")
    set_menu({
        usage = "xmake package",
        description = "Bump the patch version, build the obfuscated mod, and zip the distributable into dist/"
    })
    on_run(function ()
        import("core.base.json")

        local projectdir = os.projectdir()
        local manifestpath = path.join(projectdir, "mod.json")
        local name = json.loadfile(manifestpath).meta.name

        -- Every distributable is a new release, so the version moves before anything is built:
        -- the staged mod.json is copied verbatim and must already carry the shipped version.
        -- Spliced into the raw text rather than re-encoded, so hand-authored formatting and key
        -- order survive. The first "version" key is meta's; game_builds entries carry one too.
        local raw = io.readfile(manifestpath)
        local first, last, major, minor, patch = raw:find('"version"%s*:%s*"(%d+)%.(%d+)%.(%d+)"')
        if not first then
            raise("mod.json has no meta.version of the form major.minor.patch")
        end
        local platformsAt = raw:find('"platforms"', 1, true)
        if platformsAt and first > platformsAt then
            raise("mod.json meta.version must appear before platforms; refusing to bump a game_builds version")
        end
        local version = string.format("%d.%d.%d", tonumber(major), tonumber(minor), tonumber(patch) + 1)
        io.writefile(manifestpath, raw:sub(1, first - 1)
            .. string.format('"version": "%s"', version) .. raw:sub(last + 1))
        print("version bumped to %s", version)

        local distdir = path.join(projectdir, "dist")
        local stagedir = path.join(distdir, "unpackaged")
        local zipfile = path.join(distdir, string.format("%s@%s.amethyst", name, version))

        os.tryrm(stagedir)
        os.tryrm(zipfile)
        os.mkdir(distdir)

        os.execv("xmake", { "f", "-y", "--automated_build=y" })
        local failure
        try {
            function ()
                os.execv("xmake", { "build", "-y", name })
            end,
            catch {
                function (errors)
                    failure = errors
                end
            }
        }
        os.execv("xmake", { "f", "-y", "--automated_build=n" })
        if failure then
            raise(failure)
        end

        for _, f in ipairs(os.files(path.join(stagedir, "**"))) do
            local ext = path.extension(f):lower()
            if ext == ".lib" or ext == ".exp" or ext == ".pdb" or ext == ".ilk" or ext == ".bak" then
                os.rm(f)
            end
        end

        local zipscript = path.join(projectdir, "build", "package-zip.ps1")
        os.mkdir(path.directory(zipscript))
        io.writefile(zipscript, string.format([[
$ErrorActionPreference = 'Stop'
Add-Type -AssemblyName System.IO.Compression.FileSystem
[System.IO.Compression.ZipFile]::CreateFromDirectory('%s', '%s')
]], stagedir, zipfile))
        os.vrunv("powershell", { "-NoProfile", "-NonInteractive", "-ExecutionPolicy", "Bypass", "-File", zipscript })
        os.tryrm(zipscript)

        if not os.isfile(zipfile) then
            raise("packaging failed: %s was not produced", zipfile)
        end
        print("packaged %s (%.1f MB)", zipfile, os.filesize(zipfile) / 1048576)
    end)
task_end()