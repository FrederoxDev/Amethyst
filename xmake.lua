-- Mod Options
local mod_name = "AmethystRuntime" -- Replace with the name of your mod
local targetMajor, targetMinor, targetPatch = 1, 21, 101 -- Replace with the target minecraft version

option("automated_build")
    set_default(false)
    set_showmenu(true)
    set_description("Flag to indicate this is an automated build")
option_end()

set_languages("c++23")

local function get_mod_version()
    if os.isfile("mod.json") then
        local content = os.readfile("mod.json")
        local version = content:match('"version"%s*:%s*"([^"]+)"')
        return version or "1.0.0"
    end
    return "1.0.0"
end

local mod_version = get_mod_version()
local automated = is_config("automated_build", true)
local modFolder
local amethystApiPath

if automated then
    modFolder = path.join(os.projectdir(), "dist")
    amethystApiPath = path.join(os.projectdir(), "Amethyst", "AmethystAPI")
else
    set_symbols("debug")
    local amethystSrc = os.getenv("AMETHYST_SRC")
    amethystApiPath = amethystSrc and path.join(amethystSrc, "AmethystAPI") or nil

    local amethystFolder = path.join(
        os.getenv("localappdata"),
        "Packages",
        "Microsoft.MinecraftUWP_8wekyb3d8bbwe",
        "LocalState",
        "games",
        "com.mojang",
        "amethyst"
    )

    modFolder = path.join(
        amethystFolder,
        "mods",
        string.format("%s@dev", mod_name)
    )
end

-- Only include AmethystAPI if present on disk at configure-time
if amethystApiPath and os.isdir(amethystApiPath) then
    includes(amethystApiPath)
    includes(path.join(amethystApiPath, "packages", "libhat"))
end

-- RelWithDebInfo flags
add_cxxflags("/O2", "/DNDEBUG", "/MD", "/EHsc", "/FS", "/MP")
add_ldflags("/OPT:REF", "/OPT:ICF", "/INCREMENTAL:NO", {force = true})

set_targetdir(modFolder)
set_toolchains("msvc", {asm = "nasm"})

set_project(mod_name)

target(mod_name)
    set_kind("shared")
    add_deps("AmethystAPI", "libhat")

    -- Hard fail if AmethystAPI is missing
    on_load(function (t)
        if not (amethystApiPath and os.isdir(amethystApiPath)) then
            raise("AmethystAPI not found at: " .. tostring(amethystApiPath) ..
                  "\nCI: ensure repo is checked out to Amethyst/AmethystAPI" ..
                  "\nLocal: set AMETHYST_SRC to point to your Amethyst clone.")
        end
    end)

    -- Force rebuild when any source file changes
    set_policy("build.optimization.lto", true )
    set_policy("build.across_targets_in_parallel", true )
    set_policy("script.allow_io", true)

    add_files("src/**.cpp")

    -- Uncomment if you plan to use ASM
    -- add_files("src/**.asm")
    --     set_toolset("as", "nasm")
    --     add_asflags("-f win64", { force = true })

    add_defines(
        string.format('MOD_TARGET_VERSION_MAJOR=%d', targetMajor),
        string.format('MOD_TARGET_VERSION_MINOR=%d', targetMinor),
        string.format('MOD_TARGET_VERSION_PATCH=%d', targetPatch),
        string.format('MOD_VERSION="%s"', mod_version),
        'ENTT_PACKED_PAGE=128',
        'AMETHYST_EXPORTS'
    )

    -- Deps
    add_packages("AmethystAPI", "libhat")
    add_links("user32", "oleaut32", "windowsapp")

    add_includedirs("src", {public = true})
    add_headerfiles("src/**.hpp")

    after_build(function (target)
        local src_json = path.join("mod.json")
        local dst_json = path.join(modFolder, "mod.json")
        if not os.isdir(modFolder) then
            os.mkdir(modFolder)
        end
        os.cp(src_json, dst_json)
    end)
