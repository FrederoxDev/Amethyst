cmake_minimum_required(VERSION 3.12)
project(AmethystAPI)

# Amethyst folder location
set(AmethystFolder "$ENV{localappdata}/Packages/Microsoft.MinecraftUWP_8wekyb3d8bbwe/AC/Amethyst/")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO "${AmethystFolder}/lib")

# C++ Compile Options
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CONFIGURATION_TYPES "RelWithDebInfo" CACHE STRING "Build configurations" FORCE)
set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose the type of build, options are: RelWithDebInfo" FORCE)

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.h")
file(GLOB_RECURSE ASM "src/*.asm")

# Create AmethystAPI as a .lib
add_library(${PROJECT_NAME} STATIC ${SOURCES} ${ASM} ${HEADERS})

# Amethyst Dependencies
target_include_directories(${PROJECT_NAME} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)


target_link_libraries(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/fmt.lib
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/libMinHook.x6.lib
)

# EnTT Compile options
target_compile_definitions(${PROJECT_NAME} PUBLIC ENTT_PACKED_PAGE=128)

# Set the ASM sources for the library
set_property(TARGET ${PROJECT_NAME} PROPERTY ASM_SOURCES ${ASM})

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
foreach(_source IN ITEMS ${SOURCES} ${HEADERS} ${ASM})
    get_filename_component(_source_path "${_source}" PATH)
    file(RELATIVE_PATH _source_path_rel "${CMAKE_CURRENT_SOURCE_DIR}/src" "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()