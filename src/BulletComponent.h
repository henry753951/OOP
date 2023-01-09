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
    Vector2D vec;
    Vector2D speed;

    int count = 0;

    BulletComponent() = default;

    ~BulletComponent() {
        this->entity->delGroup(Game::groupBullets);
    }

    BulletComponent(int x, int y, double vecX, double vecY) {
        texture = Game::assets->GetTexture("crosshair");
        srcRect.x = 0;
        srcRect.y = 0;
        srcRect.w = srcRect.h = 200;
        destRect.w = destRect.h = 50 * 1;
        position.x = static_cast<float>(x);
        position.y = static_cast<float>(y);
        vec.x = vecX * 5.0;
        vec.y = vecY * 5.0;
    }

    void update() override {
        count++;
        if (count > 300) {
            delete this;
        }
        position.Add(vec);
        destRect.x = static_cast<int>(position.x - Game::camera.x);
        destRect.y = static_cast<int>(position.y - Game::camera.y);
    }
    void draw() override {
        TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
    }
};