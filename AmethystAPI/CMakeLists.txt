cmake_minimum_required(VERSION 3.12)
project(AmethystAPI)

set(CMAKE_CXX_STANDARD 20)

# Define only RelWithDebInfo as the available build configuration
set(CMAKE_CONFIGURATION_TYPES "RelWithDebInfo" CACHE STRING "Build configurations" FORCE)
set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose the type of build, options are: Debug Release RelWithDebInfo" FORCE)

# Project Configuration
set(AmethystFolder "$ENV{appdata}/Amethyst")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO "${AmethystFolder}/lib")

file(GLOB_RECURSE CPP_SOURCES "src/*.cpp")
file(GLOB_RECURSE H_FILES "include/*.h")

add_library(${PROJECT_NAME} STATIC ${CPP_SOURCES} ${H_FILES})

target_compile_definitions(${PROJECT_NAME} PUBLIC ENTT_PACKED_PAGE=128)

set_property(
    TARGET ${PROJECT_NAME}
    PROPERTY MSVC_RUNTIME_LIBRARY
    # use /MD in debug mode (dynamic linking) and /MT in release mode (static linking)
    $<$<CONFIG:Debug>:MultiThreadedDLL>$<$<CONFIG:Release>:MultiThreaded>
)

# Organize source files into virtual folders in Visual Studio
foreach(source IN LISTS CPP_SOURCES H_FILES)
    get_filename_component(source_path "${source}" DIRECTORY)
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" source_path_relative "${source_path}")
    string(REPLACE "/" "\\" source_path_relative "${source_path_relative}")
    source_group("${source_path_relative}" FILES "${source}")
endforeach()

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    lib/fmt.lib
    lib/libMinHook.x64.lib
)

# Auto copy headers to %Appdata%/Amethyst/lib for use
add_custom_target(CopyHeaders
    COMMENT "Copying .h and .lib's to ${AmethystFolder}"
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/include" "${AmethystFolder}/include"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_CURRENT_SOURCE_DIR}/lib/fmt.lib" "${AmethystFolder}/lib/fmt.lib"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_CURRENT_SOURCE_DIR}/lib/libMinHook.x64.lib" "${AmethystFolder}/lib/libMinHook.x64.lib"
)

add_dependencies(${PROJECT_NAME} CopyHeaders)