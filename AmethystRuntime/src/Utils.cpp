#include "Utils.h"

std::string GetAmethystFolder() {
    char* path;
    size_t path_length;
    errno_t err = _dupenv_s(&path, &path_length, "AppData");
    
    if (err) {
        Log::Error("_dupenv_s failed to find %AppData%\n");
        throw std::exception();
    }

    if (path == 0) {
        Log::Error("%AppData% was 0\n");
        throw std::exception();
    }

    std::string app_data(path);
    free(path);

    std::string amethyst_folder = app_data + "/Amethyst/";
    return amethyst_folder;
}

std::string GetAmethystUWPFolder() {
    char* path;
    size_t path_length;
    errno_t err = _dupenv_s(&path, &path_length, "LocalAppData");

    if (err) {
        Log::Error("_dupenv_s failed to find %LocalAppData%\n");
        throw std::exception();
    }

    if (path == 0) {
        Log::Error("%AppData% was 0\n");
        throw std::exception();
    }

    std::string app_data(path);
    free(path);

    std::string amethyst_folder = app_data + "/Amethyst/";
    return amethyst_folder;
}