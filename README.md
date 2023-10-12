# Projects

Mono-repo for the Amethyst modding API for minecraft bedrock. WIP.

### AmethystLauncher:
 - Injects a target DLL into the running Minecraft process

### AmethystRuntime:
 - Loads mods into the game at runtime
 - Manages calling mod events

### AmethystAPI:
 - Utility functions, e.g. Sigscanning, hooking, etc

# To do:
 - [x] Hook Virtual functions
 - [x] Member variables
 - [x] Sig-scanning
 - [ ] Better sig scanning algorithm
 - [x] Build into a specific %amethyst% folder
 - [ ] Load mods at runtime / support multiple mods