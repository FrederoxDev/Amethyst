cmake_minimum_required(VERSION 3.12)
project(AmethystRuntime)
set(MOD_VERSION "1.1.0")

# C++ Build Settings
set(CMAKE_CONFIGURATION_TYPES "RelWithDebInfo" CACHE STRING "Build configurations" FORCE)
set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose the type of build, options are: Debug Release RelWithDebInfo" FORCE)
set(CMAKE_CXX_STANDARD 20)

# Build into %appdata%/Amethyst
set(AmethystFolder "$ENV{localappdata}/Packages/Microsoft.MinecraftUWP_8wekyb3d8bbwe/AC/Amethyst/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${AmethystFolder}/mods/${PROJECT_NAME}@${MOD_VERSION}")

# Project Files
file(GLOB_RECURSE CPP_SOURCES "src/*.cpp")
file(GLOB_RECURSE H_FILES "include/*.h" )
add_library(${PROJECT_NAME} SHARED ${CPP_SOURCES} ${H_FILES})

# Include the AmethystRuntime headers
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)

# EnTT Config Options
target_compile_definitions(${PROJECT_NAME} PUBLIC ENTT_SPARSE_PAGE=2048)
target_compile_definitions(${PROJECT_NAME} PUBLIC ENTT_PACKED_PAGE=128)

# Organize source files into virtual folders in Visual Studio
foreach(source IN LISTS CPP_SOURCES H_FILES)
    get_filename_component(source_path "${source}" DIRECTORY)
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" source_path_relative "${source_path}")
    string(REPLACE "/" "\\" source_path_relative "${source_path_relative}")
    source_group("${source_path_relative}" FILES "${source}")
endforeach()

# Pass MOD_VERSION to the source code
target_compile_definitions(${PROJECT_NAME} PRIVATE MOD_VERSION="${MOD_VERSION}")

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE AmethystAPI)

# Code Style
add_custom_target(ClangFormat
    COMMAND clang-format
    -i
    ${CPP_SOURCES} ${H_FILES}
)