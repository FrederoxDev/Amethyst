set_languages("c++23")

add_cxxflags("/O2", "/Zi", "/DNDEBUG", "/MD", "/EHsc", "/FS", "/MP")
add_ldflags("/DEBUG", "/OPT:REF", "/OPT:ICF", "/INCREMENTAL:NO", {force = true})

includes("packages/libhat")

set_toolchains("clang-cl")

local mc_headers_path = os.getenv("MC_HEADERS")
includes(mc_headers_path)

target("AmethystAPI")
    set_kind("static")
    set_default(false)
    add_deps("MC")

    add_files("src/**.cpp", "src/**.c", "include/**.cpp")

    -- PCH
    set_pcxxheader("src/amethyst/Imports.hpp", {pchheader = "amethyst/Imports.hpp"})

    -- Deps
    add_deps("libhat")

    add_includedirs("include", "src", {public = true})
    add_headerfiles("src/**.hpp", "include/**.hpp", "include/**.h")

    add_defines("WIN32_LEAN_AND_MEAN", "NOMINMAX", { public = true })

    -- Janky fix, this is set in the mod_build.lua script by defining a non-local variable
    -- But it does mean it propagates down so good enough xD
    PLATFORM = PLATFORM or "win-client"

    if PLATFORM == "win-client" then
        add_defines("CLIENT", "WIN_CLIENT", {  public = true })
    elseif PLATFORM == "win-server" then
        add_defines("SERVER", "WIN_SERVER", {  public = true })
    end