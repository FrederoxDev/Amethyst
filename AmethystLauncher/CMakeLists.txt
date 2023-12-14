cmake_minimum_required(VERSION 3.12)
project(AmethystLauncher)

set(CMAKE_CXX_STANDARD 17)
add_executable(AmethystLauncher src/AmethystLauncher.cpp src/loader/Loader.cpp)