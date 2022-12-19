#include "header/Game.h"

#include <iostream>

#include "header/Configuration.h"
using std::cin;
using std::cout;
using std::endl;

Manager manager;
AssetManager* Game::assets = new AssetManager(&manager);
SDL_Renderer* Game::_renderer = nullptr;

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

void Game::init(const char* title, int x, int y, int w, int h, Uint32 flags) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) std::cerr << "Error: Failed at SDL_Init()" << endl;
    _window = SDL_CreateWindow(title, x, y, w, h, flags);
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);

    if (_renderer) {
        SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
    }
}

void Game::gameLoop() {
    while (_gameState != GameState::EXIT) {
        handleEvents();
        update();
        render();
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
    SDL_Surface* tmpSurface = IMG_Load("Assets/player/image.png");
    auto playerTex = SDL_CreateTextureFromSurface(_renderer, tmpSurface);
    SDL_RenderCopy(_renderer, playerTex, NULL, NULL);

    SDL_RenderPresent(_renderer);
}
void Game::quit() {
    SDL_DestroyWindow(_window);
    SDL_DestroyRenderer(_renderer);
    SDL_Quit();
}