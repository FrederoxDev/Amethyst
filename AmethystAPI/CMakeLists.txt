include(FetchContent)

# Fetch dependencies
FetchContent_Declare(
    libhat
    GIT_REPOSITORY  https://github.com/BasedInc/libhat.git
    GIT_TAG         9ef05d6961ce37a4c801f11159de895aa21878a9
)
FetchContent_MakeAvailable(libhat)

file(GLOB_RECURSE AmethystAPI_All
    "src/*.cpp" 
    "src/*.c" 
    "src/*.asm"
    "src/*.hpp" 
    "src/*.h" 
)

add_library(AmethystAPI STATIC ${AmethystAPI_All})

target_include_directories(AmethystAPI PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(AmethystAPI PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/fmt.lib
    libhat
)

target_compile_options(AmethystAPI PRIVATE
    $<$<COMPILE_LANGUAGE:CXX>:/MP>
)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src" FILES ${AmethystAPI_All})