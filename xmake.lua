set_toolchains("clang-cl")

-- Mod Options
local mod_name = "Amethyst-Runtime" -- Replace with the name of your mod
local targetMajor, targetMinor, targetPatch = 1, 21, 3 -- 1.21.0.3 (Other versions not supported by Amethyst)
local config_options = {} -- Any additional options, see: https://github.com/AmethystAPI/Amethyst-Template/blob/main/README.md

-- Anything below here should not need to be changed
-- To update your build script if its outdated, replace everything below these comments
-- The latest version can be found here: https://github.com/AmethystAPI/Amethyst-Template/blob/main/xmake.lua
local MOD_BUILD_SCRIPT_VERSION = 2

option("automated_build")
    set_default(false)
    set_showmenu(true)
    set_description("Flag to indicate this is an automated build")
option_end()

option("platform")
    set_default("win-client")
    set_showmenu(true)
    set_values("win-client", "win-server")
    set_description("The platform to target building too")
option_end()

local automated = is_config("automated_build", true)
local platform = get_config("platform")

local amethystSrc = os.getenv("AMETHYST_SRC")
local build_script_path
if amethystSrc and os.isfile(path.join(amethystSrc, "AmethystAPI", "mod_build.lua")) then
    build_script_path = path.join(amethystSrc, "AmethystAPI", "mod_build.lua")
else
    build_script_path = path.join("Amethyst", "AmethystAPI", "mod_build.lua")
end

if not os.isfile(build_script_path) then
    print("Failed to find build script!" .. build_script_path)
else 
    includes(build_script_path)

    local build_config = {
        MOD_BUILD_SCRIPT_VERSION = MOD_BUILD_SCRIPT_VERSION,
        platform = platform,
    }

    for k, v in pairs(config_options) do
        build_config[k] = v
    end

    build_mod(mod_name, targetMajor, targetMinor, targetPatch, automated, build_config)
end