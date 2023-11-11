cmake_minimum_required(VERSION 3.12)
project(AmethystAPI)

message("$ENV{amethyst}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO "$ENV{amethyst}/lib")

file(GLOB_RECURSE CPP_SOURCES "src/*.cpp")
file(GLOB_RECURSE H_FILES "src/*.h")

add_library(${PROJECT_NAME} STATIC ${CPP_SOURCES} ${H_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(${PROJECT_NAME} PRIVATE "$ENV{amethyst}/lib/fmt.lib")
target_link_libraries(${PROJECT_NAME} PRIVATE "$ENV{amethyst}/lib/libMinHook.x64.lib")