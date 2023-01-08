#pragma once

#include "engine/ECS/ECS.h"
#include "engine/TextureManager.h"
#include "engine/Vector2D.h"
#include "header/Game.h"

class BulletComponent : public Component {
   public:
    SDL_Texture* texture;
    SDL_Rect destRect;
    Vector2D position;
    Vector2D vec;
    int count=0;

    BulletComponent() = default;

    ~BulletComponent() {

    }

    BulletComponent(int x,int y,double vecX,double vecY) {
        count++;
        if(count>10000){
            std::cout << count << std::endl;
            delete this;
        }
        position.x = static_cast<float>(x);
        position.y = static_cast<float>(y);
        vec.x = vecX;
        vec.y = vecY;
    }

    void update() override {
        position.Add(vec);
        destRect.x = static_cast<int>(position.x - Game::camera.x);
        destRect.y = static_cast<int>(position.y - Game::camera.y);
        SDL_RenderDrawPoint(Game::_renderer,destRect.x,destRect.y);
    }
    void draw() override {
        // TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
        
    }
};