#include "header/Game.h"
// hi
#include <iostream>
#include <sstream>

#include "engine/Animation.h"
#include "engine/AssetManager.h"
#include "engine/Collision.h"
#include "engine/Components.h"
#include "engine/Vector2D.h"
#include "header/Configuration.h"
#include "header/Map.h"
using std::cin;
using std::cout;
using std::endl;
Map *map;
SDL_Rect Game::camera = {0, 0, 0, 0};
SDL_DisplayMode DM;
Manager manager;
AssetManager *Game::assets = new AssetManager(&manager);
SDL_Renderer *Game::_renderer = nullptr;
SDL_Event Game::event;
bool Game::isRunning = false;
auto &player(manager.addEntity());
auto &label(manager.addEntity());

auto &tiles(manager.getGroup(Game::groupMap));
auto &players(manager.getGroup(Game::groupPlayers));
auto &colliders(manager.getGroup(Game::groupColliders));
auto &enemys(manager.getGroup(Game::groupEnemys));
auto &bullets(manager.getGroup(Game::groupBullets));

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
    Game::camera = {0, 0, DM.w, DM.h};
    gameLoop();
}

/**
 *  初始化視窗、render
 */
void Game::init(const char *title, int x, int y, int w, int h, Uint32 flags) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        std::cerr << "Error: Failed at SDL_Init()" << endl;
    _window = SDL_CreateWindow(title, x, y, w, h, flags);
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    isRunning = true;
    if (_renderer) {
        SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    }

    assets->AddTexture("crosshair", "Assets/Texture/crosshair.png");
    assets->AddTexture("pistol_idle", "Assets/Texture/spritesheets/player/pistol/pistol_idle.png");
    assets->AddTexture("pistol_fire", "Assets/Texture/spritesheets/player/pistol/pistol_fire.png");
    assets->AddTexture("pistol_reload", "Assets/Texture/spritesheets/player/pistol/pistol_reload.png");
    assets->AddTexture("pistol_walk", "Assets/Texture/spritesheets/player/pistol/pistol_walk.png");

    map = new Map("terrain", 1, 32);
    map->LoadMap("Assets/Texture/ground.png", "Assets/1f.map", 50, 50);
    // label.addComponent<UILabel>(10, 10, "Test String", "arial", white);

    player.addComponent<AimComponent>(0, 0, 0, 0, 200, 0.1);

    player.addComponent<TransformComponent>(800.0f, 640.0f, 1);
    Animation pistol_idle = Animation("pistol_idle", 255, 218, 0, 20, 150);
    Animation pistol_fire = Animation("pistol_fire", 225, 218, 0, 3, 150);
    Animation pistol_reload = Animation("pistol_reload", 225, 218, 0, 15, 150);
    Animation pistol_walk = Animation("pistol_walk", 260, 222, 0, 20, 150);
    std::vector<Animation> ids = {pistol_idle, pistol_fire, pistol_reload, pistol_walk};
    player.addComponent<SpriteComponent>(ids, true);
    player.addComponent<KeyboardController>();
    player.addComponent<ColliderComponent>("player");
    player.addGroup(groupPlayers);

    AddEnemy(700.0f, 640.0f);
    AddEnemy(800.0f, 1500.0f);
}

Uint32 frameStart;
int frameTime;

void Game::AddEnemy(float srcX, float srcY) {
    auto &enemy(manager.addEntity());
    enemy.addComponent<TransformComponent>(srcX, srcY, 1);
    Animation pistol_idle = Animation("pistol_idle", 255, 218, 0, 20, 150);
    Animation pistol_fire = Animation("pistol_fire", 225, 218, 0, 3, 150);
    Animation pistol_reload = Animation("pistol_reload", 225, 218, 0, 15, 150);
    Animation pistol_walk = Animation("pistol_walk", 260, 222, 0, 20, 150);

    std::vector<Animation> ids = {pistol_idle, pistol_fire, pistol_reload, pistol_walk};
    enemy.addComponent<SpriteComponent>(ids, true);
    enemy.addComponent<EnemyController>();
    enemy.addComponent<ColliderComponent>("enemy");
    enemy.addGroup(groupEnemys);
}

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
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            _gameState = GameState::EXIT;
            break;
    }
}

void Game::update() {
    SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;
    Vector2D playerPos = player.getComponent<TransformComponent>().position;

    std::stringstream ss;
    ss << "Player position: " << playerPos;

    manager.refresh();
    manager.update();

    for (auto &c : colliders) {
        SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
        if (Collision::AABB(cCol, playerCol)) {
            player.getComponent<TransformComponent>().position = playerPos;
        }
    }

    camera.x = static_cast<int>(player.getComponent<TransformComponent>().position.x - DM.w / 2 + 256);
    camera.y = static_cast<int>(player.getComponent<TransformComponent>().position.y - DM.h / 2 + 128);

    if (camera.x < 0)
        camera.x = 0;
    if (camera.y < 0)
        camera.y = 0;
    if (camera.x > camera.w)
        camera.x = camera.w;
    if (camera.y > camera.h)
        camera.y = camera.h;
}

void Game::render() {
    SDL_RenderClear(_renderer);
    for (auto &t : tiles) {
        t->draw();
    }

    for (auto &e : enemys) {
        e->draw();
    }
    for (auto &b : bullets) {
        b->draw();
    }
    for (auto &p : players) {
        p->draw();
    }

    SDL_RenderPresent(_renderer);
}
void Game::quit() {
    SDL_DestroyWindow(_window);
    SDL_DestroyRenderer(_renderer);
    SDL_Quit();
}