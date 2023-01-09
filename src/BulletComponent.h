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
        std::cout << pow(vecX,2) + pow(vecY,2);
        texture = Game::assets->GetTexture("crosshair");
        srcRect.x = 0;
        srcRect.y = 0;
        srcRect.w = srcRect.h = 200;
        destRect.w = destRect.h = 50 * 1;
        position.x = x;
        position.y = y;
        vec.x = vecX * 50.0f;
        vec.y = vecY * 50.0f;
    }

    void update() override {
        count++;
        if (count > 300) {
            delete this;
        }
        position.Add(vec);
        destRect.x = static_cast<int>(position.x - static_cast<float>(Game::camera.x));
        destRect.y = static_cast<int>(position.y - static_cast<float>(Game::camera.y));
    }
    void draw() override {
        TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
    }
};