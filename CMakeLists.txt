cmake_minimum_required(VERSION 3.12)
project(Amethyst CXX ASM_NASM)
include(FetchContent)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /await")

# Compiler Options
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_CONFIGURATION_TYPES "RelWithDebInfo" CACHE STRING "Build configurations" FORCE)
set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose the type of build, options are: RelWithDebInfo" FORCE)

# Fetch dependencies
FetchContent_Declare(
    libhat
    GIT_REPOSITORY  https://github.com/BasedInc/libhat.git
    GIT_TAG         9ef05d6961ce37a4c801f11159de895aa21878a9
)
FetchContent_MakeAvailable(libhat)

add_subdirectory(AmethystAPI)
add_subdirectory(AmethystRuntime)