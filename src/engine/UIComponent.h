#pragma once

#include <bits/stdc++.h>
#include "ECS/ECS.h"
#include "TextureManager.h"
#include "Vector2D.h"
#include "../header/Game.h"


extern Manager manager;
class UIComponent : public Component {
   public:
    SDL_Texture* texture;
    SDL_Rect srcRect, destRect;
    Vector2D position;
    UIComponent() = default;

    ~UIComponent() {
        SDL_DestroyTexture(texture);
    }

    UIComponent(std::string n, int srcX, int srcY, int xpos, int ypos, int htsize, int wtsize, float tscale) {
        texture = Game::assets->GetTexture(n);

        srcRect.x = srcX;
        srcRect.y = srcY;
        srcRect.w = wtsize;
        srcRect.h = htsize;
        position.x = static_cast<float>(xpos);
        position.y = static_cast<float>(ypos);
        destRect.w = wtsize * tscale;
        destRect.h = htsize * tscale;
        destRect.x = static_cast<int>(xpos);
        destRect.y= static_cast<int>(ypos);
    }

    void update() override {
        // int x, y = 0;
        // SDL_GetMouseState(&x, &y);
        // position.x = static_cast<int>(x - offset);
        // position.y = static_cast<int>(y - offset);
        // destRect.x = static_cast<int>(x - offset);
        // destRect.y = static_cast<int>(y - offset);

        // float deltaX;
        // float deltaY;
        // deltaX = *(&entity->getComponent<TransformComponent>().position.x) + *(&entity->getComponent<SpriteComponent>().destRect.w) / 2 - Game::camera.x - x;
        // deltaY = *(&entity->getComponent<TransformComponent>().position.y) + *(&entity->getComponent<SpriteComponent>().destRect.h) / 2 - Game::camera.y - y;
    }
    void draw() override {
        TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
    }
};