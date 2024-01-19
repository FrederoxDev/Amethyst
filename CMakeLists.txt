# Set Minimum CMAKE Version
cmake_minimum_required(VERSION 3.27.0)

# Set Project Name
project(AmethystMono)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 20)

# Add the AmethystAPI subfolder as a subdirectory
add_subdirectory(AmethystAPI)

# Add the AmethystRuntime subfolder as a subdirectory
add_subdirectory(AmethystRuntime)

# Make the API first
add_dependencies(AmethystRuntime AmethystAPI)