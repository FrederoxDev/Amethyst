# Amethyst Options
set(MOD_VERSION "1.2.2")
set(MOD_TARGET_VERSION_MAJOR 1)
set(MOD_TARGET_VERSION_MINOR 20)
set(MOD_TARGET_VERSION_PATCH 7101)

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

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src" FILES ${AmethystRuntime_All})