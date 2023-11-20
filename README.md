# Projects

Mono-repository for the core AmethystAPI projects.

**AmethystAPI**: Provides re-usable functionality such as Sigscanning, Hooking and headers for Minecraft.

**AmethystRuntime**: A mod which loads other mods at runtime and manages calling functions like `ModInitialize` and `ModTick`

**AmethystLauncher**: An application which is in charge of starting minecraft and injecting the AmethystRuntime mod

## Creating a mod
```cmake
cmake_minimum_required(VERSION 3.12)
project(ModName) # Replace with the name of your mod

set(AmethystFolder "$ENV{appdata}/Amethyst")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${AmethystFolder}/mods/${PROJECT_NAME}")

find_library(AMETHYST_API AmethystAPI PATHS "${AmethystFolder}/lib")
include_directories(${AmethystFolder}/include)

file(GLOB_RECURSE CPP_SOURCES "src/*.cpp")
file(GLOB_RECURSE H_FILES "src/*.h")
add_library(${PROJECT_NAME} SHARED ${CPP_SOURCES} ${H_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE ${AMETHYST_API})
target_link_libraries(${PROJECT_NAME} PRIVATE "${AmethystFolder}/lib/fmt.lib")
target_link_libraries(${PROJECT_NAME} PRIVATE "${AmethystFolder}/lib/libMinHook.x64.lib")
```

## Goals of AmethystAPI

 - AmethystAPI does not aim to have completed headers
 - Add to headers as needed for projects
 - Sticking to one version (currently 1.20.30.02)
 - Follow the same folder structure as Minecraft