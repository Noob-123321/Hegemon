#include "../../include/core/save.h"
#include <iostream>
#include <SDL3/SDL.h>
#include <sstream>

namespace {
    constexpr const char* FILENAME = "settings.txt";
}

void SaveGameSettings(const GameSettings& settings) {
    SDL_IOStream* file = SDL_IOFromFile(FILENAME, "w");
    SDL_IOprintf(file, "%d %d %d", settings.screenWidth, settings.screenHeight, settings.fullscreen ? 1 : 0);
    SDL_CloseIO(file);
}

GameSettings LoadGameSettings() {
    GameSettings settings;
    size_t dataSize;
    void* file = SDL_LoadFile(FILENAME, &dataSize);
    if (file != nullptr) {
        std::string fileContent(static_cast<char*>(file), dataSize);
        SDL_free(file);
        std::stringstream ss(fileContent);
        ss >> settings.screenWidth >> settings.screenHeight >> settings.fullscreen;
    } else {
        SaveGameSettings(settings);
    }
    return settings;
}
