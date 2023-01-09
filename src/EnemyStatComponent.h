#pragma once

#include "engine/ECS/ECS.h"
// #include "engine/TextureManager.h"
#include "engine/Vector2D.h"
#include "header/Game.h"

class EnemyStatComponent : public Component {
public:
    bool DeadorAlive;
    int healthPoint;
    int nowMode;
    float speed;
    // SDL_Texture* texture;
    // SDL_Rect srcRect, destRect;
    // Vector2D position;
    // int offset;
    EnemyStatComponent() = default;

    // ~EnemyStatComponent() {
    //     SDL_DestroyTexture(texture);
    // }

    EnemyStatComponent(bool DoA, int hp, int m, float s) {
        DeadorAlive = DoA;
        healthPoint = hp;
        nowMode = m;
        speed = s;
        // texture = Game::assets->GetTexture("crosshair");

        // srcRect.x = srcX;
        // srcRect.y = srcY;
        // srcRect.w = srcRect.h = tsize;
        // position.x = static_cast<float>(xpos);
        // position.y = static_cast<float>(ypos);
        // destRect.w = destRect.h = tsize * tscale;
        // offset = (srcRect.w * tscale) / 2;
    }

    // void update() override {
    //     int x, y = 0;
    //     SDL_GetMouseState(&x, &y);
    //     position.x = static_cast<int>(x - offset);
    //     position.y = static_cast<int>(y - offset);
    //     destRect.x = static_cast<int>(x - offset);
    //     destRect.y = static_cast<int>(y - offset);
    // }
    // void draw() override {
    //     TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
    // }
};