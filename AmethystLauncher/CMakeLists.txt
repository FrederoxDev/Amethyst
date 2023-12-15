cmake_minimum_required(VERSION 3.12)
project(AmethystLauncher)

set(CMAKE_CXX_STANDARD 17)

set(AmethystFolder "$ENV{appdata}/Amethyst")
find_library(AMETHYST_API AmethystAPI PATHS "${AmethystFolder}/lib")
include_directories(${AmethystFolder}/include "include/")

add_executable(AmethystLauncher src/AmethystLauncher.cpp src/loader/Loader.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${AMETHYST_API})
target_link_libraries(${PROJECT_NAME} PRIVATE "${AmethystFolder}/lib/fmt.lib")
target_link_libraries(${PROJECT_NAME} PRIVATE "${AmethystFolder}/lib/libMinHook.x64.lib")