cmake_minimum_required(VERSION 3.12)
project(AmethystAPI)

set(AmethystFolder "$ENV{appdata}/Amethyst")
message("${AmethystFolder}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO "${AmethystFolder}/lib")

file(GLOB_RECURSE CPP_SOURCES "src/*.cpp")
file(GLOB_RECURSE H_FILES "include/*.h")

add_library(${PROJECT_NAME} STATIC ${CPP_SOURCES} ${H_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    "lib/fmt.lib",
    "lib/libMinHook.x64.lib"
)

add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMENT "Copying .h and .lib's to ${AmethystFolder}"
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/include" "${AmethystFolder}/include"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_CURRENT_SOURCE_DIR}/lib/fmt.lib" "${AmethystFolder}/lib/fmt.lib"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_CURRENT_SOURCE_DIR}/lib/libMinHook.x64.lib" "${AmethystFolder}/lib/libMinHook.x64.lib"
)