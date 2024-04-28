cmake_minimum_required(VERSION 3.12)
project(Amethyst CXX ASM_NASM)
include(FetchContent)

# Compiler Options
set(CMAKE_CXX_STANDARD 23)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Amethyst Options
set(MOD_VERSION "1.2.2")
set(MOD_TARGET_VERSION_MAJOR 1)
set(MOD_TARGET_VERSION_MINOR 20)
set(MOD_TARGET_VERSION_PATCH 7101)

# Fetch dependencies
FetchContent_Declare(
    libhat
    GIT_REPOSITORY  https://github.com/BasedInc/libhat.git
    GIT_TAG         9ef05d6961ce37a4c801f11159de895aa21878a9
)
FetchContent_MakeAvailable(libhat)

# Create AmethystAPI.
file(GLOB_RECURSE AmethystAPI_All
    "AmethystAPI/src/*.cpp" 
    "AmethystAPI/src/*.c" 
    "AmethystAPI/src/*.asm"
    "AmethystAPI/src/*.hpp" 
    "AmethystAPI/src/*.h" 
)

add_library(AmethystAPI STATIC ${AmethystAPI_All})

target_include_directories(AmethystAPI PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/AmethystAPI/include
    ${CMAKE_CURRENT_SOURCE_DIR}/AmethystAPI/src
)

target_link_libraries(AmethystAPI PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/AmethystAPI/lib/fmt.lib
    libhat
)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/AmethystAPI/src" FILES ${AmethystAPI_All})

# Create AmethystRuntime
file(GLOB_RECURSE AmethystRuntime_All
    "AmethystRuntime/src/*.cpp" 
    "AmethystRuntime/src/*.c" 
    "AmethystRuntime/src/*.asm"
    "AmethystRuntime/src/*.hpp" 
    "AmethystRuntime/src/*.h" 
) 

add_library(AmethystRuntime SHARED ${AmethystRuntime_All})

target_include_directories(AmethystRuntime PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/AmethystRuntime/src
)

target_link_libraries(AmethystRuntime PRIVATE 
    AmethystAPI 
    libhat
    ${CMAKE_CURRENT_SOURCE_DIR}/AmethystAPI/lib/fmt.lib
)

target_compile_definitions(AmethystRuntime PRIVATE 
    MOD_VERSION="${MOD_VERSION}"  
    MOD_TARGET_VERSION_MAJOR=${MOD_TARGET_VERSION_MAJOR}
    MOD_TARGET_VERSION_MINOR=${MOD_TARGET_VERSION_MINOR}
    MOD_TARGET_VERSION_PATCH=${MOD_TARGET_VERSION_PATCH}
)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/AmethystRuntime/src" FILES ${AmethystRuntime_All})
