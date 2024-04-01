cmake_minimum_required(VERSION 3.12)
project(AmethystAPI CXX ASM_NASM)
include(FetchContent)

# Amethyst folder location
set(AmethystFolder "$ENV{localappdata}/Packages/Microsoft.MinecraftUWP_8wekyb3d8bbwe/AC/Amethyst/")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO "${AmethystFolder}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${AmethystFolder}/lib")

# C++ Compile Options
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CONFIGURATION_TYPES "RelWithDebInfo" CACHE STRING "Build configurations" FORCE)
set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose the type of build, options are: RelWithDebInfo" FORCE)

add_compile_definitions(_ITERATOR_DEBUG_LEVEL=0)
set_property(GLOBAL PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.c" "src/*.asm")
file(GLOB_RECURSE HEADERS "src/*.hpp")
  
# Create AmethystAPI as a .lib
add_library(${PROJECT_NAME} STATIC 
    ${SOURCES}
    ${HEADERS}
    src/minecraft/src/common/world/item/Item.asm
    src/minecraft/src/common/world/level/block/BlockLegacy.asm
    src/minecraft/src-deps/minecraftrenderer/renderer/MaterialPtr.asm
)

# Amethyst Dependencies
target_include_directories(${PROJECT_NAME} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/fmt.lib
)


# EnTT Compile options
target_compile_definitions(${PROJECT_NAME} PUBLIC ENTT_PACKED_PAGE=128)

# Include libhat for SigScan
FetchContent_Declare(
    libhat
    GIT_REPOSITORY  https://github.com/BasedInc/libhat.git
    GIT_TAG         9ef05d6961ce37a4c801f11159de895aa21878a9
)
FetchContent_MakeAvailable(libhat)
target_link_libraries(${PROJECT_NAME} PRIVATE libhat)

# Use proper runtime library
set_property(
    TARGET ${PROJECT_NAME} libhat
    PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreadedDLL"
)

# Copy Amethyst's Headers to AmethystFolder/include
foreach(HEADER ${HEADERS})
    file(RELATIVE_PATH HEADER_RELATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src ${HEADER})
    get_filename_component(HEADER_NAME ${HEADER} NAME)
    set(DESTINATION_PATH ${AmethystFolder}/include/${HEADER_RELATIVE_PATH})
    configure_file(${HEADER} ${DESTINATION_PATH} COPYONLY)

endforeach()


# Copy Amethyst's dependencies to AmethystFolder/include
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION ${AmethystFolder}/include/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/lib/ DESTINATION ${AmethystFolder}/lib/)

# Create source groups to reflect the directory structure in Visual Studio
foreach(_source IN ITEMS ${SOURCES} ${HEADERS})
    get_filename_component(_source_path "${_source}" PATH)
    file(RELATIVE_PATH _source_path_rel "${CMAKE_CURRENT_SOURCE_DIR}/src" "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()
