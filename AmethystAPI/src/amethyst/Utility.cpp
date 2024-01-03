#include "amethyst/Utility.h"

std::string GetAmethystFolder() {
    static std::string amethystFolder;

    if (amethystFolder.empty()) {
        char* path;
        size_t path_length;
        errno_t err = _dupenv_s(&path, &path_length, "LocalAppData");

        if (err) throw std::exception("Failed to get environment variable %LocalAppData%");
        if (path == NULL) throw std::exception("%LocalAppData% was null");

        std::string localAppDataFolder(path);
        free(path);

        amethystFolder = localAppDataFolder + "/Amethyst/";
    }

    return amethystFolder;
}