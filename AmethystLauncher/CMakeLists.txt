cmake_minimum_required(VERSION 3.12)
project(AmethystLauncher)

# Define only RelWithDebInfo as the available build configuration
set(CMAKE_CONFIGURATION_TYPES "RelWithDebInfo" CACHE STRING "Build configurations" FORCE)
set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose the type of build, options are: Debug Release RelWithDebInfo" FORCE)

set(CMAKE_CXX_STANDARD 17)

set(AmethystFolder "$ENV{appdata}/Amethyst")
find_library(AMETHYST_API AmethystAPI PATHS "${AmethystFolder}/lib")
include_directories(${AmethystFolder}/include "include/")

file(READ ${CMAKE_CURRENT_SOURCE_DIR}/src/default_config.json JSON_CONTENT)
file(WRITE ${CMAKE_CURRENT_SOURCE_DIR}/src/default_config.h 
"const char* default_config = R\"(
${JSON_CONTENT}
)\";")

add_executable(AmethystLauncher src/AmethystLauncher.cpp src/loader/Loader.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE ${AMETHYST_API})
target_link_libraries(${PROJECT_NAME} PRIVATE "${AmethystFolder}/lib/fmt.lib")
target_link_libraries(${PROJECT_NAME} PRIVATE "${AmethystFolder}/lib/libMinHook.x64.lib")