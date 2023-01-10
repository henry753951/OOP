#pragma once
#include "engine/Components.h"
#include "engine/ECS/ECS.h"
#include "engine/TextureManager.h"
#include "engine/Vector2D.h"
#include "header/Game.h"
#include "engine/Collision.h"

extern Manager manager;


class BulletComponent : public Component {
   public:
    SDL_Texture* texture;
    SDL_Rect srcRect, destRect;
    Vector2D position;
    Vector2D vec;
    Vector2D speed;

    int count = 0;

    BulletComponent() = default;

    // void Damaging(Entity* e){
    //     (*e).getComponent<EnemyController>().healthPoint -= 5;
    // }

    ~BulletComponent() {
        this->entity->delGroup(Game::groupBullets);
    }

    BulletComponent(int x, int y, double vecX, double vecY) {
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
        auto& enemys(manager.getGroup(Game::groupEnemys));
        for (auto &e : enemys) {
            if (Collision::AABB(e->getComponent<ColliderComponent>().collider, position)) {
                // b->getComponent<BulletComponent>().Damaging(e);
                std::cout << "hit" << std::endl;
                delete this;
                break;
            }
        }

    }
    void draw() override {
        SDL_SetRenderDrawColor(Game::_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderDrawLine(Game::_renderer, destRect.x, destRect.y, destRect.x + vec.x * 2, destRect.y + vec.y * 2);
        SDL_SetRenderDrawColor(Game::_renderer, 0x00, 0x00, 0x00, 0x00);
    }
};