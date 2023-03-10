#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <string>

#include "../engine/AssetManager.h"
#include "../engine/TextureManager.h"

class AssetManager;
class ColliderComponent;
enum class GameState {
    PLAY,
    EXIT
};

class Game {
   private:
    void init(const char* title, int x, int y, int w, int h, Uint32 flags);
    void AddEnemy(float, float, int, float);
    void AddHostage(float, float, int, float);
    void gameLoop();
    void handleEvents();
    void AddUI(std::string, int, int, int, int, int, int, float);
    void AddLabels(int, int, std::string, std::string, SDL_Color);

    int _screenWidth;
    int _screenHight;
    int _windowMode;

    GameState _gameState;

   public:
    SDL_Window* _window;
    static AssetManager* assets;
    static SDL_Renderer* _renderer;
    static SDL_Rect camera;
    static bool isRunning;
    static SDL_Event event;
    int FPS = 60;
    int frameDelay = 1000 / FPS;

    enum groupLabels : std::size_t {
        groupMap,
        groupPlayers,
        groupColliders,
        groupEnemys,
        groupBullets,
        groupHostages,
        groupUIs,
        groupLabels,
    };
    Game();
    ~Game();

    void run();
    void update();
    void render();
    void quit();
};
