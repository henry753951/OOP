#pragma once
#include "../header/Game.h"
#include "Components.h"
#include "ECS/ECS.h"
#include "RayTrace.h"
#include "SpriteComponent.h"
#include "TextureManager.h"
#include "TransformComponent.h"

extern Manager manager;
using std::cin;
using std::cout;
using std::endl;
using std::vector;

class EnemyController : public Component {
   private:
    vector<Entity *> players;
    vector<Entity *> colliders;
    float distanceX, distanceY;

   public:
    SDL_Texture *texture;
    TransformComponent *transform;
    SpriteComponent *sprite;
    ColliderComponent *collider;
    SDL_Rect srcRect, destRect;

    bool DeadorAlive;
    int healthPoint;
    int nowMode;
    float speed;
    float nowx, nowy;
    int offset;
    bool visable = true;

    EnemyController(bool DoA, int hp, int m, float s) {
        DeadorAlive = DoA;
        healthPoint = hp;
        nowMode = m;
        speed = s;
    }

    void init() override {
        colliders = manager.getGroup(Game::groupColliders);
        players = manager.getGroup(Game::groupPlayers);
        transform = &entity->getComponent<TransformComponent>();
        sprite = &entity->getComponent<SpriteComponent>();
        collider = &entity->getComponent<ColliderComponent>();
        texture = Game::assets->GetTexture("blood");
        srcRect.x = srcRect.y = 0;
        srcRect.w = srcRect.h = 256;
        destRect.w = destRect.h = 0;
    }

    void damaged(float damage) {
        healthPoint -= damage;
    }

    void update() override {
        if (healthPoint <= 0 && DeadorAlive == true) {
            DeadorAlive = false;
            transform->velocity.x = 0;
            transform->velocity.y = 0;
            destRect.w = destRect.h = 256 * 0.25;
            sprite->~SpriteComponent();
        }

        if (DeadorAlive == true) {
            for (auto &p : players) {
                nowx = (p->getComponent<TransformComponent>().position.x);
                nowy = (p->getComponent<TransformComponent>().position.y);
                distanceX = nowx - transform->position.x;
                distanceY = nowy - transform->position.y;
                // cout << distanceX << " ";
                // cout << distanceY << endl;
            }
            // 若不再玩家視線 則return visable = false
            if (!RayTrace::checkThrough(colliders, static_cast<int>(transform->position.x), static_cast<int>(transform->position.y), (nowx), (nowy))) {
                transform->velocity.x = 0;
                transform->velocity.y = 0;
                std::cout << "Blocked" << std::endl;
            } else {
                std::cout << "no Blocked" << std::endl;
                sprite->angle = -10 + (atan2(distanceY, distanceX) * 180.0000) / M_PI;

                if (transform->velocity.y == 0 && transform->velocity.x == 0) {
                    sprite->Play("pistol_idle");
                } else {
                    sprite->Play("pistol_walk");
                }

                if (nowMode == 0) {
                    transform->velocity.x = 0;
                    transform->velocity.y = 0;
                } else if (nowMode == 1) {
                    if (sqrt(pow(distanceX, 2) + pow(distanceY, 2)) <= 80) {
                        transform->velocity.x = 0;
                        transform->velocity.y = 0;
                    } else {
                        transform->velocity.x = speed * (distanceX / sqrt(pow(distanceX, 2) + pow(distanceY, 2)));
                        transform->velocity.y = speed * (distanceY / sqrt(pow(distanceX, 2) + pow(distanceY, 2)));
                    }
                }
            }
        }

        destRect.x = static_cast<int>(transform->position.x - Game::camera.x);
        destRect.y = static_cast<int>(transform->position.y - Game::camera.y);
    }

    void draw() override {
        TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
    }
};