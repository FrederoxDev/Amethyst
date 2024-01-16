cmake_minimum_required(VERSION 3.12)
project(AmethystAPI)

# Amethyst folder location
set(AmethystFolder "$ENV{localappdata}/Packages/Microsoft.MinecraftUWP_8wekyb3d8bbwe/AC/Amethyst/")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO "${AmethystFolder}/lib")

# C++ Compile Options
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CONFIGURATION_TYPES "RelWithDebInfo" CACHE STRING "Build configurations" FORCE)
set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose the type of build, options are: RelWithDebInfo" FORCE)

# Fix STL structures on debug mode
add_compile_definitions(_ITERATOR_DEBUG_LEVEL=0)

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.h")

# Create AmethystAPI as a .lib
add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

# Amethyst Dependencies
include(FetchContent)
target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# MinHook dependency
FetchContent_Declare(
        minhook
        GIT_REPOSITORY https://github.com/TsudaKageyu/minhook.git
        GIT_TAG f5485b8454544c2f034c78f8f127c1d03dea3636
)
FetchContent_GetProperties(minhook)
if(NOT minhook_POPULATED)
    FetchContent_Populate(minhook)
    add_subdirectory(${minhook_SOURCE_DIR} ${minhook_BINARY_DIR})
endif()

# libhat dependency
FetchContent_Declare(
        libhat
        GIT_REPOSITORY https://github.com/BasedInc/libhat.git
        GIT_TAG 224fd84f37bb5ebcfb65d45db9af438ee68bac59
)
FetchContent_GetProperties(libhat)
if(NOT libhat_POPULATED)
    FetchContent_Populate(libhat)
    add_subdirectory(${libhat_SOURCE_DIR} ${libhat_BINARY_DIR})
endif()

# EnTT dependency
FetchContent_Declare(
        entt
        GIT_REPOSITORY https://github.com/skypjack/entt.git
        GIT_TAG v3.12.2
        OVERRIDE_FIND_PACKAGE
)
FetchContent_GetProperties(entt)
if(NOT entt_POPULATED)
    FetchContent_Populate(entt)
    add_subdirectory(${entt_SOURCE_DIR} ${entt_BINARY_DIR})
endif()

# nlohmann json dependency
FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.3
        OVERRIDE_FIND_PACKAGE
)
FetchContent_GetProperties(json)
if(NOT json_POPULATED)
    FetchContent_Populate(json)
    add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR})
endif()

# GLM dependency
FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 0.9.9.8
        OVERRIDE_FIND_PACKAGE
)
FetchContent_GetProperties(glm)
if(NOT glm_POPULATED)
    FetchContent_Populate(glm)
    add_subdirectory(${glm_SOURCE_DIR} ${glm_BINARY_DIR})
endif()


# GSL dependency
FetchContent_Declare(
        gsl
        GIT_REPOSITORY https://github.com/microsoft/GSL.git
        GIT_TAG v4.0.0
)
FetchContent_GetProperties(gsl)
if(NOT gsl_POPULATED)
    FetchContent_Populate(gsl)
    add_subdirectory(${gsl_SOURCE_DIR} ${gsl_BINARY_DIR})
endif()

# FMT dependency
FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG 10.1.1
        OVERRIDE_FIND_PACKAGE
)
FetchContent_GetProperties(fmt)
if(NOT fmt_POPULATED)
    FetchContent_Populate(fmt)
    add_subdirectory(${fmt_SOURCE_DIR} ${fmt_BINARY_DIR})
endif()

# EnTT Compile options
target_compile_definitions(${PROJECT_NAME} PUBLIC ENTT_SPARSE_PAGE = 2048)
target_compile_definitions(${PROJECT_NAME} PUBLIC ENTT_PACKED_PAGE=128)

# Link the dependencies to the target
target_link_libraries(${PROJECT_NAME} PUBLIC minhook libhat EnTT glm GSL fmt nlohmann_json)

# Copy Amethyst's Headers to AmethystFolder/include
foreach(HEADER ${HEADERS})
    file(RELATIVE_PATH HEADER_RELATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src ${HEADER})
    get_filename_component(HEADER_NAME ${HEADER} NAME)
    set(DESTINATION_PATH ${AmethystFolder}/include/${HEADER_RELATIVE_PATH})
    configure_file(${HEADER} ${DESTINATION_PATH} COPYONLY)

endforeach()

# Copy Amethyst's dependencies to AmethystFolder/include
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION ${AmethystFolder}/include/)

# Create source groups to reflect the directory structure in Visual Studio
foreach(_source IN ITEMS ${SOURCES} ${HEADERS})
    get_filename_component(_source_path "${_source}" PATH)
    file(RELATIVE_PATH _source_path_rel "${CMAKE_CURRENT_SOURCE_DIR}/src" "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()