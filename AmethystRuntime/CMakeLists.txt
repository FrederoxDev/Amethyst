# Amethyst Options
set(MOD_VERSION "1.4.0")
set(MOD_AUTHOR "FrederoxDev")

set(MOD_TARGET_VERSION_MAJOR 1)
set(MOD_TARGET_VERSION_MINOR 21)
set(MOD_TARGET_VERSION_PATCH 3)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /await")
# Some dependency is using <experimental/X>, ^^

# Amethyst Minecraft Folder
if (CI_CD_BUILD)
    configure_file(mod.json.in "${CMAKE_SOURCE_DIR}/dist/AmethystRuntime@${MOD_VERSION}/mod.json" @ONLY)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_SOURCE_DIR}/dist/AmethystRuntime@${MOD_VERSION}")  
else()
    set(AmethystFolder "$ENV{localappdata}/Packages/Microsoft.MinecraftUWP_8wekyb3d8bbwe/LocalState/games/com.mojang/amethyst/") 
    configure_file(mod.json.in "${AmethystFolder}/mods/AmethystRuntime@${MOD_VERSION}/mod.json" @ONLY)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${AmethystFolder}/mods/AmethystRuntime@${MOD_VERSION}")  
endif()

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
