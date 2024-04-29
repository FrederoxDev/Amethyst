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