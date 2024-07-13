# Amethyst Options
set(MOD_VERSION "1.4.0")
set(MOD_AUTHOR "FrederoxDev")

set(MOD_TARGET_VERSION_MAJOR 1)
set(MOD_TARGET_VERSION_MINOR 21)
set(MOD_TARGET_VERSION_PATCH 3)

# Amethyst Minecraft Folder
set(AmethystFolder "$ENV{localappdata}/Packages/Microsoft.MinecraftUWP_8wekyb3d8bbwe/LocalState/games/com.mojang/amethyst/") 

# Configure to build within the Amethyst Folder
configure_file(mod.json.in "${AmethystFolder}/mods/AmethystRuntime@${MOD_VERSION}/mod.json" @ONLY)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${AmethystFolder}/mods/AmethystRuntime@${MOD_VERSION}")  

# Create AmethystRuntime 
file(GLOB_RECURSE AmethystRuntime_All  
    "src/*.cpp" 
    "src/*.c"  
    "src/*.asm" 
    "src/*.hpp" 
    "src/*.h"  
)   

add_library(AmethystRuntime SHARED ${AmethystRuntime_All})

target_include_directories(AmethystRuntime PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(AmethystRuntime PRIVATE 
    AmethystAPI 
    libhat
    ${CMAKE_CURRENT_SOURCE_DIR}/../AmethystAPI/lib/fmt.lib
) 

target_compile_definitions(AmethystRuntime PRIVATE 
    MOD_VERSION="${MOD_VERSION}"  
    MOD_TARGET_VERSION_MAJOR=${MOD_TARGET_VERSION_MAJOR}
    MOD_TARGET_VERSION_MINOR=${MOD_TARGET_VERSION_MINOR}
    MOD_TARGET_VERSION_PATCH=${MOD_TARGET_VERSION_PATCH}
)

target_compile_options(AmethystRuntime PRIVATE
    $<$<COMPILE_LANGUAGE:CXX>:/MP> 
)

# EnTT Config Options
target_compile_definitions(AmethystRuntime PUBLIC ENTT_PACKED_PAGE=128)

# Make the folder structure with Visual Studio's virtual folders
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src" FILES ${AmethystRuntime_All}) 
