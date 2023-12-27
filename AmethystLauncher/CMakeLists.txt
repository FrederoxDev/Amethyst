cmake_minimum_required(VERSION 3.12)
project(AmethystLauncher)

# Define only RelWithDebInfo as the available build configuration
set(CMAKE_CONFIGURATION_TYPES "RelWithDebInfo" CACHE STRING "Build configurations" FORCE)
set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose the type of build, options are: Debug Release RelWithDebInfo" FORCE)

set(CMAKE_CXX_STANDARD 17)

set(AmethystFolder "$ENV{appdata}/Amethyst")
find_library(AMETHYST_API AmethystAPI PATHS "${AmethystFolder}/lib")
include_directories(${AmethystFolder}/include "include/")

set(
    MANIFEST_FILE
    "${CMAKE_CURRENT_SOURCE_DIR}/AmethystLauncher.exe.manifest"
)
# Add a custom target to copy the manifest file to the build directory
add_custom_command(
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/AmethystLauncher.exe.manifest"
    COMMAND ${CMAKE_COMMAND} -E copy "${MANIFEST_FILE}" "${CMAKE_CURRENT_BINARY_DIR}/AmethystLauncher.exe.manifest"
    DEPENDS "${MANIFEST_FILE}"
    COMMENT "Copying manifest file"
)
# Add a custom target to embed the manifest into the executable
add_custom_target(
    EmbedManifest ALL
    COMMAND mt.exe -manifest "${CMAKE_CURRENT_BINARY_DIR}/AmethystLauncher.exe.manifest" -outputresource:"${CMAKE_CURRENT_BINARY_DIR}/RelWithDebInfo/AmethystLauncher.exe"
    DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/AmethystLauncher.exe.manifest"
    COMMENT "Embedding manifest file"
)


# add source files
set(SOURCE_FILES
        src/AmethystLauncher.cpp
        src/loader/Loader.cpp
        src/loader/PermissionChanger.cpp
        )

# add header files
set(HEADER_FILES
        src/loader/Loader.h
        src/loader/PermissionChanger.h
        )

add_executable(AmethystLauncher 
        ${SOURCE_FILES}
        ${HEADER_FILES}
        )
target_link_libraries(${PROJECT_NAME} PRIVATE ${AMETHYST_API})
target_link_libraries(${PROJECT_NAME} PRIVATE "${AmethystFolder}/lib/fmt.lib")
target_link_libraries(${PROJECT_NAME} PRIVATE "${AmethystFolder}/lib/libMinHook.x64.lib")


# Ensure the EmbedManifest target runs after the executable is built
add_dependencies(AmethystLauncher EmbedManifest)