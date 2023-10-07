cmake_minimum_required(VERSION 3.12)
project(AmethystAPI)

# Use RelWithDebInfo as using Debug will cause certain types to change in size
# E.g. std::string will only work in release
# While also retaining debugging information
set(CMAKE_BUILD_TYPE "RelWithDebInfo")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D_ITERATOR_DEBUG_LEVEL=0")

# Build into the amethystAPI specific folders
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "$ENV{amethyst}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO "$ENV{amethyst}")

# Find all cpp and h files
file(GLOB_RECURSE CPP_SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADER_FILES "src/*.h" "src/*.hpp")

include_directories(${CMAKE_SOURCE_DIR}/include)

# Create the DLL and PDB
add_library(AmethystAPI SHARED ${CPP_SOURCES} ${HEADER_FILES})
target_link_libraries(AmethystAPI PRIVATE ${CMAKE_SOURCE_DIR}/lib/fmt.lib)
target_link_libraries(AmethystAPI PRIVATE ${CMAKE_SOURCE_DIR}/lib/libMinHook.x64.lib)

set(HEADER_OUTPUT_DIR "$ENV{amethyst}/include")

# Create a custom target to copy the header files
add_custom_target(CopyHeaders ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory ${HEADER_OUTPUT_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${HEADER_FILES} ${HEADER_OUTPUT_DIR}
    DEPENDS ${HEADER_FILES}
)

add_dependencies(AmethystAPI CopyHeaders)