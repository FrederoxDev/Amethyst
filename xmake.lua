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

-- Check if we are in an automated build
local isAutomatedBuild = os.getenv("GITHUB_ACTIONS") == "true"
local amethystApiSrc = ""

if isAutomatedBuild then
    -- Use the hardcoded path for the GitHub Actions runner
    amethystApiSrc = "C:\\Users\\runneradmin\\Documents\\Amethyst"
else
    -- For a local build, first try the environment variable
    amethystApiSrc = os.getenv("AMETHYST_SRC")

    -- If the environment variable is not set, try the default Documents folder
    if amethystApiSrc == nil then
        local documentsPath = path.join(os.getenv("USERPROFILE"), "Documents", "Amethyst")
        if os.isdir(documentsPath) then
            amethystApiSrc = documentsPath
        else
            -- If all else fails, print a warning and let the includes() fail gracefully
            print("AMETHYST_SRC environment variable is not set and Amethyst API was not found in the expected folder.")
        end
    end
end

-- RelWithDebInfo flags
add_cxxflags("/O2", "/Zi", "/DNDEBUG", "/MD", "/EHsc", "/FS", "/MP")
add_ldflags("/DEBUG", "/OPT:REF", "/OPT:ICF", "/INCREMENTAL:NO", {force = true})
includes(path.join(amethystApiSrc, "AmethystAPI"))

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

    -- Deps
    add_packages("AmethystAPI", "libhat")
    add_links("user32", "oleaut32", "windowsapp")
    add_includedirs("src", {public = true})

    add_headerfiles("src/**.hpp")

    after_build(function (target)
        local src_json = path.join(os.curdir(), "mod.json")
        local dst_json = path.join(modFolder, "mod.json")
        if not os.isdir(modFolder) then
            os.mkdir(modFolder)
        end
        os.cp(src_json, dst_json)
    end)
