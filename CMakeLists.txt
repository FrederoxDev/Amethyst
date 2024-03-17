# Set Minimum CMAKE Version
cmake_minimum_required(VERSION 3.27.0)

# Set Project Name
project(AmethystMono)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 23)

# Validate C++ compiler support
if (NOT MSVC OR NOT CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    message(FATAL_ERROR "Unsupported Compiler")
endif()

# Add the AmethystAPI subfolder as a subdirectory
add_subdirectory(AmethystAPI)

# Add the AmethystRuntime subfolder as a subdirectory
add_subdirectory(AmethystRuntime)

# Make the API first
add_dependencies(AmethystRuntime AmethystAPI)