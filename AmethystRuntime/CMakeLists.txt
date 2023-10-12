cmake_minimum_required(VERSION 3.12)
project(AmethystRuntime)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "$ENV{amethyst}/mods/${PROJECT_NAME}")

find_library(AMETHYST_API AmethystAPI PATHS "$ENV{amethyst}/lib")
include_directories($ENV{amethyst}/include)

file(GLOB_RECURSE CPP_SOURCES "src/*.cpp")
file(GLOB_RECURSE H_FILES "src/*.h")
add_library(${PROJECT_NAME} SHARED ${CPP_SOURCES} ${H_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE ${AMETHYST_API})
target_link_libraries(${PROJECT_NAME} PRIVATE "$ENV{amethyst}/lib/fmt.lib")
target_link_libraries(${PROJECT_NAME} PRIVATE "$ENV{amethyst}/lib/libMinHook.x64.lib")