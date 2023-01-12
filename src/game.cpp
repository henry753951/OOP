#include "header/Game.h"
#include <SDL2/SDL_mixer.h>
// hi
#include <iostream>
#include <sstream>

#include "engine/Animation.h"
#include "engine/AssetManager.h"
#include "engine/Collision.h"
#include "engine/Components.h"
#include "engine/Raytrace.h"
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
Mix_Music *gMusic = NULL;
bool Game::isRunning = false;
auto &player(manager.addEntity());
auto &label(manager.addEntity());

auto &tiles(manager.getGroup(Game::groupMap));
auto &players(manager.getGroup(Game::groupPlayers));
auto &colliders(manager.getGroup(Game::groupColliders));
auto &enemys(manager.getGroup(Game::groupEnemys));
auto &hostages(manager.getGroup(Game::groupHostages));
auto &bullets(manager.getGroup(Game::groupBullets));
auto &UIs(manager.getGroup(Game::groupUIs));
auto &labels(manager.getGroup(Game::groupLabels));
SDL_Color white;
/**
 *  遊戲建構子
 *  載入設定檔、讀入物件內
 */
Game::Game() {
    white.r = 255;
    white.g = 255;
    white.b = 255;

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

    if(TTF_Init()==-1){
        cout << "TTF could not initialize!" << endl;
    }
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
    }
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
    }

    gMusic = Mix_LoadMUS( "Assets/Audio/background_ambient.mp3" );

    Mix_PlayMusic( gMusic, -1 );

    assets->AddTexture("blood", "Assets/Texture/blood_pool.png");
    assets->AddTexture("crosshair", "Assets/Texture/crosshair.png");
    assets->AddTexture("pistol_idle", "Assets/Texture/spritesheets/player/pistol/pistol_idle.png");
    assets->AddTexture("pistol_fire", "Assets/Texture/spritesheets/player/pistol/pistol_fire.png");
    assets->AddTexture("pistol_reload", "Assets/Texture/spritesheets/player/pistol/pistol_reload.png");
    assets->AddTexture("pistol_walk", "Assets/Texture/spritesheets/player/pistol/pistol_walk.png");
    assets->AddTexture("HP", "Assets/Texture/HP.png");
    assets->AddTexture("HPamount", "Assets/Texture/HPamount.png");
    assets->AddTexture("white", "Assets/Texture/white.png");
    assets->AddFont("Cubic","Assets/Font/Cubic_11_1.013_R.ttf",50);

    map = new Map("terrain", 1, 32);
    map->LoadMap("Assets/Texture/ground.png", "Assets/1f.map", 50, 50);
    // label.addComponent<UILabel>(10, 10, "Test String", "arial", white);

    player.addComponent<AimComponent>(0, 0, 0, 0, 200, 0.1);

    player.addComponent<TransformComponent>(800.0f, 640.0f, 0.3);
    Animation pistol_idle = Animation("pistol_idle", 255, 218, 0, 20, 150);
    Animation pistol_fire = Animation("pistol_fire", 262, 218, 0, 3, 30);
    Animation pistol_reload = Animation("pistol_reload", 262, 231, 0, 15, 60);
    Animation pistol_walk = Animation("pistol_walk", 260, 222, 0, 20, 150);
    std::vector<Animation> ids = {pistol_idle, pistol_fire, pistol_reload, pistol_walk};
    player.addComponent<SpriteComponent>(ids, true);
    player.addComponent<KeyboardController>();
    player.addComponent<ColliderComponent>("player");
    player.addComponent<PlayerStatComponent>(100);
    player.addGroup(groupPlayers);

    SDL_Color black = {0,0,0,255};

    AddEnemy(700.0f, 640.0f, 100, 0.5);
    AddEnemy(800.0f, 700.0f, 100, 0);
    AddHostage(200.0f, 600.0f, 100, 1.5);
    AddUI("white",0,0,30,700,90,110,1);
    AddUI("HPamount",0,0,30,780,100,520,1);
    AddUI("white",0,0,50,50,50,810,1);
    AddUI("white",0,0,1300,765,90,300,1);
    AddLabels(60, 50, "MISSION: RESCUE THE HOSTAGES", "Cubic", black);
    AddLabels(50, 715, "HP", "Cubic", black);
    AddLabels(1360, 780, "BULLETS", "Cubic", black);
}

Uint32 frameStart;
Uint32 TimerStart;
int TimerTime;
int frameTime;

void Game::AddEnemy(float srcX, float srcY, int hp, float speed) {
    auto &enemy(manager.addEntity());
    enemy.addComponent<TransformComponent>(srcX, srcY, 0.3);
    Animation pistol_idle = Animation("pistol_idle", 255, 218, 0, 20, 150);
    Animation pistol_fire = Animation("pistol_fire", 225, 218, 0, 3, 150);
    Animation pistol_reload = Animation("pistol_reload", 225, 218, 0, 15, 150);
    Animation pistol_walk = Animation("pistol_walk", 260, 222, 0, 20, 150);

    std::vector<Animation> ids = {pistol_idle, pistol_fire, pistol_reload, pistol_walk};
    enemy.addComponent<SpriteComponent>(ids, true);
    enemy.addComponent<EnemyController>(true, hp, 1, speed);
    enemy.addComponent<ColliderComponent>("enemy");
    enemy.addGroup(groupEnemys);
}

void Game::AddHostage(float srcX, float srcY, int hp, float speed) {
    auto &hostage(manager.addEntity());
    hostage.addComponent<TransformComponent>(srcX, srcY, 0.3);
    Animation pistol_idle = Animation("pistol_idle", 255, 218, 0, 20, 150);
    Animation pistol_fire = Animation("pistol_fire", 225, 218, 0, 3, 150);
    Animation pistol_reload = Animation("pistol_reload", 225, 218, 0, 15, 150);
    Animation pistol_walk = Animation("pistol_walk", 260, 222, 0, 20, 150);

    std::vector<Animation> ids = {pistol_idle, pistol_fire, pistol_reload, pistol_walk};
    hostage.addComponent<SpriteComponent>(ids, true);
    hostage.addComponent<HostageController>(true, hp, 0, speed);
    hostage.addComponent<ColliderComponent>("hostage");
    hostage.addGroup(groupHostages);
}

void Game::AddUI(std::string n, int srcX, int srcY, int xpos, int ypos, int htsize, int wtsize, float tscale) {
    auto &UI(manager.addEntity());
    UI.addComponent<UIComponent>(n, srcX, srcY, xpos, ypos, htsize, wtsize, tscale);
    UI.addGroup(groupUIs);
}

void Game::AddLabels(int X, int Y, std::string content,std::string font,SDL_Color colour)
{
    auto &label(manager.addEntity());
    label.addComponent<UILabel>(X, Y, content, font, colour);
    label.addGroup(groupLabels);
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
    int clips = player.getComponent<KeyboardController>().clip;

    std::stringstream ss;
    ss << clips << "/15";
    labels[2]->getComponent<UILabel>().SetLabelText(ss.str(),"Cubic");

    manager.refresh();
    manager.update();

    for (auto &c : colliders) {
        SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
        if (Collision::AABB(cCol, playerCol)) {
            player.getComponent<TransformComponent>().position = playerPos;
        }
        for (auto &b : bullets) {
            Vector2D pos = (*b).getComponent<BulletComponent>().position;
            if (Collision::AABB(cCol, pos)) {
                b->getComponent<BulletComponent>().~BulletComponent();
            }
            //     for (auto &e : enemys) {
            //     SDL_Rect eCol = (*e).getComponent<ColliderComponent>().collider;
            //     if (Collision::AABB(eCol, pos)) {
            //         // b->getComponent<BulletComponent>().Damaging(e);
            //         std::cout << "hit" << std::endl;
            //         delete this;
            //     }
            // }
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
    for (auto &C : colliders) {
        C->draw();
    }
    for (auto &e : enemys) {
        e->draw();
    }
    for (auto &h : hostages) {
        h->draw();
    }
    for (auto &b : bullets) {
        b->draw();
    }
    for (auto &p : players) {
        p->draw();
    }
    for (auto &u : UIs) {
        u->draw();
    }
    for (auto &l : labels)
    {
        l->draw();
    }

    SDL_RenderPresent(_renderer);
}
void Game::quit() {
    SDL_DestroyWindow(_window);
    SDL_DestroyRenderer(_renderer);
    SDL_Quit();
    Mix_FreeMusic( gMusic );
    gMusic = NULL;
}