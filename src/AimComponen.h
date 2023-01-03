#pragma once

#include "engine/ECS/ECS.h"
#include "engine/TextureManager.h"
#include "engine/Vector2D.h"
#include "header/Game.h"

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
    }
    void draw() override {
        TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
    }
};