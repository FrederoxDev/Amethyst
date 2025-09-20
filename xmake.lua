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

-- Use a conditional include for automated builds
if os.getenv("GITHUB_ACTIONS") then
    includes("AmethystAPI")
else
    includes(path.join(os.getenv("AMETHYST_SRC"), "AmethystAPI"))
end

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

-- Add the build hook to run before the build starts
before_build(function (target)
    local importer_dir = path.join(os.curdir(), ".importer");
    local generated_dir = path.join(importer_dir)
    local input_dir = path.join(os.curdir(), "src")
    local include_dir = path.join(os.curdir(), "AmethystAPI", "amethyst", "include")

    -- Check if we are in a GitHub Actions environment
    local is_github_actions = os.getenv("GITHUB_ACTIONS")
    local yes_flag = is_github_actions and "--yes" or ""

    local gen_sym_args = {
        ".importer/bin/Amethyst.RuntimeImporter.exe",
        "--",
        "-x c++",
        "-include-pch", path.join(generated_dir, "pch.hpp.pch"),
        "-std=c++23",
        "-fms-extensions",
        "-fms-compatibility",
        string.format('-I%s', include_dir),
        string.format('-I%s', input_dir)
    }

    if yes_flag then
        table.insert(gen_sym_args, yes_flag)
    end

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

    local tweaker_dir = path.join(os.curdir(), "build", "windows", "x64", "release")
    local src_dll = path.join(tweaker_dir, "AmethystRuntime.dll")
    local src_pdb = path.join(tweaker_dir, "AmethystRuntime.pdb")

    local dst_dll = path.join(modFolder, "AmethystRuntime.dll")
    local dst_pdb = path.join(modFolder, "AmethystRuntime.pdb")

    os.cp(src_dll, dst_dll)
    os.cp(src_pdb, dst_pdb)
end)

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
        'ENTT_PACKED_PAGE=128',
        'AMETHYST_EXPORTS'
    )