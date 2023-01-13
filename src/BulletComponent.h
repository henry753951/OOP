#pragma once
#include "engine/Collision.h"
#include "engine/Components.h"
#include "engine/ECS/ECS.h"
#include "engine/EnemyController.h"
#include "engine/PlayerStatComponent.h"
#include "engine/TextureManager.h"
#include "engine/Vector2D.h"
#include "header/Game.h"

extern Manager manager;

class BulletComponent : public Component {
   public:
    SDL_Texture* texture;
    SDL_Rect srcRect, destRect;
    Vector2D position;
    Vector2D vec;
    Vector2D speed;
    std::string target;
    int count = 0;

    BulletComponent() = default;

    // void Damaging(Entity* e){
    //     (*e).getComponent<EnemyController>().healthPoint -= 5;
    // }

    ~BulletComponent() {
        this->entity->delGroup(Game::groupBullets);
    }

    BulletComponent(int x, int y, double vecX, double vecY, std::string target_ = "enemy") {
        texture = Game::assets->GetTexture("crosshair");
        srcRect.x = 0;
        srcRect.y = 0;
        srcRect.w = srcRect.h = 200;
        destRect.w = destRect.h = 50 * 1;
        position.x = x;
        position.y = y;
        vec.x = vecX * 50.0f;
        vec.y = vecY * 50.0f;
        target = target_;
    }

    void update() override {
        count++;
        if (count > 300) {
            delete this;
        }
        position.Add(vec);
        destRect.x = static_cast<int>(position.x - static_cast<float>(Game::camera.x));
        destRect.y = static_cast<int>(position.y - static_cast<float>(Game::camera.y));
        if (target == "enemy") {
            auto& enemys(manager.getGroup(Game::groupEnemys));
            for (auto& e : enemys) {
                if (Collision::AABB(e->getComponent<ColliderComponent>().collider, position) && e->getComponent<EnemyController>().DeadorAlive == true) {
                    e->getComponent<EnemyController>().damaged(100);
                    std::cout << "hit" << std::endl;
                    delete this;
                    break;
                }
            }
        } else if (target == "player") {
            auto& players(manager.getGroup(Game::groupPlayers));
            for (auto& p : players) {
                if (Collision::AABB(p->getComponent<ColliderComponent>().collider, position) && p->getComponent<PlayerStatComponent>().DeadorAlive == true) {
                    p->getComponent<PlayerStatComponent>().damaged(1);
                    std::cout << "hit" << std::endl;
                    delete this;
                    break;
                }
            }
        }
    }
    void draw() override {
        SDL_SetRenderDrawColor(Game::_renderer, 100, 100, 3, 0xFF);
        SDL_RenderDrawLine(Game::_renderer, destRect.x, destRect.y, destRect.x + vec.x * 2, destRect.y + vec.y * 2);
        SDL_SetRenderDrawColor(Game::_renderer, 0x00, 0x00, 0x00, 0x00);
    }
};