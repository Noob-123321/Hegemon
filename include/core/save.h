#pragma once
struct GameSettings {
    int screenWidth = 1920;
    int screenHeight = 1080;
    bool fullscreen = true;
};
struct GameMap {

};
struct GameWorld {

};
void SaveGameSettings(const GameSettings& settings);
GameSettings LoadGameSettings();