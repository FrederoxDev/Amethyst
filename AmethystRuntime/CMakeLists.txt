cmake_minimum_required(VERSION 3.12)
project(AmethystRuntime)
set(MOD_VERSION "1.0.2")

set(CMAKE_CONFIGURATION_TYPES "RelWithDebInfo" CACHE STRING "Build configurations" FORCE)
set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose the type of build, options are: Debug Release RelWithDebInfo" FORCE)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(AmethystFolder "$ENV{appdata}/Amethyst")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${AmethystFolder}/mods/${PROJECT_NAME}@${MOD_VERSION}")

find_library(AMETHYST_API AmethystAPI PATHS "${AmethystFolder}/lib")
include_directories(${AmethystFolder}/include "include/")

file(GLOB_RECURSE CPP_SOURCES "src/*.cpp")
file(GLOB_RECURSE H_FILES "src/*.h")
add_library(${PROJECT_NAME} SHARED ${CPP_SOURCES} ${H_FILES})

# Pass MOD_VERSION to the source code
target_compile_definitions(${PROJECT_NAME} PRIVATE MOD_VERSION="${MOD_VERSION}")

target_link_libraries(${PROJECT_NAME} PRIVATE ${AMETHYST_API})
target_link_libraries(${PROJECT_NAME} PRIVATE "${AmethystFolder}/lib/fmt.lib")
target_link_libraries(${PROJECT_NAME} PRIVATE "${AmethystFolder}/lib/libMinHook.x64.lib")