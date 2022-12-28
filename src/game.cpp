#include "header/Game.h"

#include <iostream>

#include "engine/AssetManager.h"
#include "engine/Components.h"
#include "engine/Vector2D.h"
#include "header/Configuration.h"
#include "header/Map.h"
using std::cin;
using std::cout;
using std::endl;
Map* map;
SDL_Rect Game::camera = {0, 0, 1600, 900};
Manager manager;
AssetManager* Game::assets = new AssetManager(&manager);
SDL_Renderer* Game::_renderer = nullptr;

auto& player(manager.addEntity());
auto& label(manager.addEntity());
auto& tiles(manager.getGroup(Game::groupMap));

/**
 *  遊戲建構子
 *  載入設定檔、讀入物件內
 */
Game::Game() {
    _window = nullptr;
    _renderer = nullptr;
    cout << "Load Config File ...\n------------------" << endl;

    // [Window Resolution]
    _screenHight = std::stoi(getConfig("screenHight"));
    _screenWidth = std::stoi(getConfig("screenWidth"));
    cout << "resolution:" << _screenWidth << 'x' << _screenHight << endl;
    // [Window Mode]
    _windowMode = std::stoi(getConfig("windowMode"));
    cout << "windowMode:" << _windowMode << endl;

    _gameState = GameState::PLAY;
};
Game::~Game(){};

/**
 *  遊戲主執行函式
 *  初始化視窗、render -> Game::init()
 */
void Game::run() {
    char WindowName[] = "Game";

    init(WindowName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHight, SDL_WINDOW_SHOWN);
    SDL_ShowCursor(1);

    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);

    // load WindowMode
    switch (_windowMode) {
        case 0:
            break;
        case 1:
            SDL_SetWindowSize(_window, DM.w, DM.h);
            SDL_SetWindowBordered(_window, SDL_FALSE);
            SDL_SetWindowFullscreen(_window, SDL_WINDOW_FULLSCREEN_DESKTOP);
            break;
        case 2:
            SDL_SetWindowSize(_window, DM.w, DM.h);
            SDL_SetWindowFullscreen(_window, SDL_WINDOW_FULLSCREEN);
            break;
        default:
            break;
    }
    gameLoop();
}

/**
 *  初始化視窗、render
 */
void Game::init(const char* title, int x, int y, int w, int h, Uint32 flags) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) std::cerr << "Error: Failed at SDL_Init()" << endl;
    _window = SDL_CreateWindow(title, x, y, w, h, flags);
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);

    if (_renderer) {
        SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    }

    assets->AddTexture("terrain", "Assets/Texture/ground.png");

    map = new Map("terrain", 3, 32);
    map->LoadMap("Assets/map.map", 25, 20);
    // label.addComponent<UILabel>(10, 10, "Test String", "arial", white);
}

Uint32 frameStart;
int frameTime;

void Game::gameLoop() {
    while (_gameState != GameState::EXIT) {
        frameStart = SDL_GetTicks();
        handleEvents();
        update();
        render();
        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    quit();
}

void Game::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            _gameState = GameState::EXIT;
            break;
    }
}

void Game::update() {
}

void Game::render() {
    SDL_RenderClear(_renderer);
    for (auto& t : tiles) {
        t->draw();
    }
    SDL_RenderPresent(_renderer);
}
void Game::quit() {
    SDL_DestroyWindow(_window);
    SDL_DestroyRenderer(_renderer);
    SDL_Quit();
}