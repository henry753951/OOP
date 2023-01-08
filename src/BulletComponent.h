#pragma once

#include "engine/ECS/ECS.h"
#include "engine/TextureManager.h"
#include "engine/Vector2D.h"
#include "header/Game.h"

class BulletComponent : public Component
{
public:
    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;
    Vector2D position;
    Vector2D vec;
    int count = 0;

    BulletComponent() = default;

    ~BulletComponent()
    {
        this->entity->delGroup(Game::groupBullets);
    }

    BulletComponent(int x, int y, double vecX, double vecY)
    {
        texture = Game::assets->GetTexture("crosshair");
        srcRect.x = 0;
        srcRect.y = 0;
        srcRect.w = srcRect.h = 200;
        position.x = static_cast<float>(x);
        position.y = static_cast<float>(y);
        vec.x = vecX;
        vec.y = vecY;
    }

    void update() override
    {
        count++;
        std::cout << destRect.x << " " << destRect.y << std::endl;
        if (count > 300)
        {
            delete this;
        }
        if (count < 10)
        {
            position.Add(vec);
        }
        destRect.x = static_cast<int>(position.x - Game::camera.x);
        destRect.y = static_cast<int>(position.y - Game::camera.y);
    }
    void draw() override
    {
        TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
    }
};