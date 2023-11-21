#include "Utils.h"

std::string GetAmethystFolder() {
    char* path;
    size_t path_length;
    errno_t err = _dupenv_s(&path, &path_length, "AppData");
    
    if (err) {
        Log::Info("_dupenv_s failed to find %AppData%\n");
        return 0;
    }

    if (path == 0) {
        Log::Info("%AppData% was 0\n");
        return 0;
    }

    std::string app_data(path);
    free(path);

    std::string amethyst_folder = app_data + "/Amethyst/";
    return amethyst_folder;
}