cmake_minimum_required(VERSION 3.12)
project(AmethystRuntime)
set(MOD_VERSION "1.2.1")

set(MOD_TARGET_VERSION_MAJOR 1)
set(MOD_TARGET_VERSION_MINOR 20)
set(MOD_TARGET_VERSION_PATCH 7101)


# C++ Build Settings
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /await")
set(CMAKE_CONFIGURATION_TYPES "RelWithDebInfo" CACHE STRING "Build configurations" FORCE)
set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose the type of build, options are: Debug Release RelWithDebInfo" FORCE)
set(CMAKE_CXX_STANDARD 23)

# Build into %appdata%/Amethyst
set(AmethystFolder "$ENV{localappdata}/Packages/Microsoft.MinecraftUWP_8wekyb3d8bbwe/AC/Amethyst/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${AmethystFolder}/mods/${PROJECT_NAME}@${MOD_VERSION}")

# Include Amethyst
find_library(AMETHYST_API AmethystAPI PATHS "${AmethystFolder}/lib")
include_directories(${AmethystFolder}/include "src/")

# Compile definitions 
if (AMETHYST_INPUT_SYSTEM) 
    add_compile_definitions(AMETHYST_INPUT_SYSTEM)
endif()

# Project Files
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.hpp" )
add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})

# EnTT Config Options
target_compile_definitions(${PROJECT_NAME} PUBLIC ENTT_PACKED_PAGE=128)

# Organize source files into virtual folders in Visual Studio
foreach(source IN LISTS SOURCES HEADERS)
    get_filename_component(source_path "${source}" DIRECTORY)
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" source_path_relative "${source_path}")
    string(REPLACE "/" "\\" source_path_relative "${source_path_relative}")
    source_group("${source_path_relative}" FILES "${source}")
endforeach()

# Pass MOD_VERSION to the source code
target_compile_definitions(${PROJECT_NAME} PRIVATE 
MOD_VERSION="${MOD_VERSION}"  
MOD_TARGET_VERSION_MAJOR=${MOD_TARGET_VERSION_MAJOR}
MOD_TARGET_VERSION_MINOR=${MOD_TARGET_VERSION_MINOR}
MOD_TARGET_VERSION_PATCH=${MOD_TARGET_VERSION_PATCH}
)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE ${AMETHYST_API})
target_link_libraries(${PROJECT_NAME} PRIVATE "${AmethystFolder}/lib/fmt.lib")
target_link_libraries(${PROJECT_NAME} PRIVATE "${AmethystFolder}/lib/libhat.lib")

# Code Style
add_custom_target(ClangFormat
    COMMAND clang-format
    -i
    ${SOURCES} ${HEADERS}
)

# Write a mod.json file to provide meta data about the mod
configure_file(mod.json.in "${AmethystFolder}/mods/${PROJECT_NAME}@${MOD_VERSION}/mod.json" @ONLY)