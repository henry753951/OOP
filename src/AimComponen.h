#pragma once

#include <bits/stdc++.h>

#include "engine/ECS/ECS.h"
#include "engine/TextureManager.h"
#include "engine/Vector2D.h"
#include "header/Game.h"
extern Manager manager;
class AimComponent : public Component {
   public:
    SDL_Texture* texture;
    SDL_Rect srcRect, destRect;
    Vector2D position;
    int offset;
    AimComponent() = default;

    ~AimComponent() {
        SDL_DestroyTexture(texture);
    }

    AimComponent(int srcX, int srcY, int xpos, int ypos, int tsize, float tscale) {
        texture = Game::assets->GetTexture("crosshair");

        srcRect.x = srcX;
        srcRect.y = srcY;
        srcRect.w = srcRect.h = tsize;
        position.x = static_cast<float>(xpos);
        position.y = static_cast<float>(ypos);
        destRect.w = destRect.h = tsize * tscale;
        offset = (srcRect.w * tscale) / 2;
    }

    void update() override {
        int x, y = 0;
        SDL_GetMouseState(&x, &y);
        position.x = static_cast<int>(x - offset);
        position.y = static_cast<int>(y - offset);
        destRect.x = static_cast<int>(x - offset);
        destRect.y = static_cast<int>(y - offset);

        float deltaX;
        float deltaY;
        deltaX = *(&entity->getComponent<TransformComponent>().position.x) + *(&entity->getComponent<SpriteComponent>().destRect.w) / 2 - Game::camera.x - x;
        deltaY = *(&entity->getComponent<TransformComponent>().position.y) + *(&entity->getComponent<SpriteComponent>().destRect.h) / 2 - Game::camera.y - y;

        *(&entity->getComponent<SpriteComponent>().angle) = 170 + (atan2(deltaY, deltaX) * 180.0000) / M_PI;
    }
    void draw() override {
        TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
    }
};