#pragma once

#include "../header/Game.h"
#include "Components.h"
#include "ECS/ECS.h"
#include "SpriteComponent.h"
#include "TextureManager.h"
#include "TransformComponent.h"

extern Manager manager;
using std::cin;
using std::cout;
using std::endl;
using std::vector;

class PlayerStatComponent : public Component {
   private:
   public:
    SDL_Rect rect;
    bool DeadorAlive;
    int healthPoint;

    PlayerStatComponent(int hp) {
        DeadorAlive = true;
        healthPoint = hp;
    }

    void init() override {
        rect.x = 60;
        rect.y = 800;
        rect.w = 460;
        rect.h = 50;
    }

    void damaged(float damage) {
        if (healthPoint <= 0) {
            healthPoint = 0;
        } else {
            healthPoint -= damage;
        }
    }

    void update() override {
        rect.w = healthPoint * 4.6;
    }

    void draw() override {
        SDL_SetRenderDrawColor(Game::_renderer, 252, 10, 80, 0xFF);
        SDL_RenderFillRect(Game::_renderer, &rect);
        SDL_SetRenderDrawColor(Game::_renderer, 0x00, 0x00, 0x00, 0x00);
    }
};