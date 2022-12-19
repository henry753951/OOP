#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>

#include "../engine/AssetManager.h"
#include "../engine/TextureManager.h"

enum class GameState {
    PLAY,
    EXIT
};

class Game {
   private:
    void init(const char* title, int x, int y, int w, int h, Uint32 flags);
    void gameLoop();
    void handleEvents();

    int _screenWidth;
    int _screenHight;
    int _windowMode;

    GameState _gameState;

   public:
    SDL_Rect camera = {0, 0, 800, 640};
    SDL_Window* _window;
    static AssetManager* assets;
    static SDL_Renderer* _renderer;
    Game();
    ~Game();

    void run();
    void update();
    void render();
    void quit();
};
