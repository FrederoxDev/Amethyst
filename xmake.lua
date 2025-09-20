-- Mod Options
local mod_name = "AmethystRuntime"
local modMajor = 2
local modMinor = 0
local modPatch = 0

-- Minecraft version
local major = 1
local minor = 21
local patch = 3

set_languages("c++23")
set_project(mod_name)
set_version(string.format("%d.%d.%d", modMajor, modMinor, modPatch))

-- RelWithDebInfo flags
add_cxxflags("/O2", "/Zi", "/DNDEBUG", "/MD", "/EHsc", "/FS", "/MP")
add_ldflags("/DEBUG", "/OPT:REF", "/OPT:ICF", "/INCREMENTAL:NO", {force = true})
includes(path.join(os.getenv("AMETHYST_SRC"), "AmethystAPI"))

-- Project dependencies
local amethystFolder = path.join(
    os.getenv("localappdata"),
    "Packages",
    "Microsoft.MinecraftUWP_8wekyb3d8bbwe",
    "LocalState",
    "games",
    "com.mojang",
    "amethyst"
)

local modFolder = path.join(
    amethystFolder,
    "mods",
    string.format("%s@%d.%d.%d", mod_name, modMajor, modMinor, modPatch)
)

set_symbols("debug")
set_targetdir(modFolder)

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
        local installed_version = os.isfile(installed_version_file) and io.readfile(installed_version_file) or "0.0.0"
        local should_reinstall = installed_version ~= latest_tag
        

        if should_reinstall then
            print("Runtime-Importer is outdated, reinstalling...")
            print("Latest version is " .. latest_tag)
            local url = "https://github.com/AmethystAPI/Runtime-Importer/releases/latest/download/Runtime-Importer.zip"
            local zipfile = path.join(os.tmpdir(), "Runtime-Importer.zip")
            print("Installing Runtime-Importer...")

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

target("AmethystRuntime")
    set_kind("shared")
    set_toolchains("nasm")
    add_deps("AmethystAPI", {public = true})
    set_default(true)
    add_files("src/**.cpp")

    add_defines(
        string.format('MOD_VERSION="%d.%d.%d"', modMajor, modMinor, modPatch),
        string.format('MOD_TARGET_VERSION_MAJOR=%d', major),
        string.format('MOD_TARGET_VERSION_MINOR=%d', minor),
        string.format('MOD_TARGET_VERSION_PATCH=%d', patch),
        'ENTT_PACKED_PAGE=128'
    )

    -- Deps
    add_packages("Runtime-Importer")
    add_packages("AmethystAPI", "libhat")
    add_links("user32", "oleaut32", "windowsapp", path.join(os.curdir(), ".importer/lib/Minecraft.Windows.lib"))
    add_includedirs("src", {public = true})

    add_headerfiles("src/**.hpp")

    before_build(function (target)
        local importer_dir = path.join(os.curdir(), ".importer");
        local generated_dir = path.join(importer_dir)
        local input_dir = path.join(os.curdir(), "AmethystAPI/src"):gsub("\\", "/")
        local include_dir = path.join(os.curdir(), "AmethystAPI/include"):gsub("\\", "/")
        
        local gen_sym_args = {
            ".importer/bin/Amethyst.SymbolGenerator.exe",
            "--input", string.format("%s", input_dir),
            "--output", string.format("%s", generated_dir),
            "--filters", "minecraft",
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
            "--input", string.format("%s/symbols", generated_dir),
            "--output", string.format("%s/lib", generated_dir)
        }
        print('Generating Minecraft.Windows.lib file...')
        os.exec(table.concat(gen_lib_args, " "))
    end)

    after_build(function (target)
        local importer_dir = path.join(os.curdir(), ".importer");
        local generated_dir = path.join(importer_dir)
        local src_json = path.join(os.curdir(), "mod.json")
        local dst_json = path.join(modFolder, "mod.json")
        if not os.isdir(modFolder) then
            os.mkdir(modFolder)
        end
        os.cp(src_json, dst_json)

        local tweaker_args = {
            ".importer/bin/Amethyst.ModuleTweaker.exe",
            "--module", target:targetfile(),
            "--symbols", string.format("%s/symbols", generated_dir)
        }
        print('Tweaking output file...')
        os.exec(table.concat(tweaker_args, " "))
    end)