#pragma once

#include "engine/ECS/ECS.h"
#include "engine/TextureManager.h"
#include "engine/Vector2D.h"
#include "header/Game.h"

class BulletComponent : public Component {
   public:
    SDL_Texture* texture;
    SDL_Rect srcRect, destRect;
    Vector2D position;

    BulletComponent() = default;

    ~BulletComponent() {
        SDL_DestroyTexture(texture);
    }

    BulletComponent(int srcX, int srcY, int xpos, int ypos, int tsize, int tscale, std::string id) {
        texture = Game::assets->GetTexture(id);

        srcRect.x = srcX;
        srcRect.y = srcY;
        srcRect.w = srcRect.h = tsize;
        position.x = static_cast<float>(xpos);
        position.y = static_cast<float>(ypos);
        destRect.w = destRect.h = tsize * tscale;
    }

    void update() override {
        destRect.x = static_cast<int>(position.x - Game::camera.x);
        destRect.y = static_cast<int>(position.y - Game::camera.y);
    }
    void draw() override {
        TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
    }
};