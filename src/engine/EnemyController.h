#pragma once
#include <sstream>

#include "../BulletComponent.h"
#include "../header/Game.h"
#include "Components.h"
#include "ECS/ECS.h"
#include "RayTrace.h"
#include "SpriteComponent.h"
#include "TextureManager.h"
#include "TransformComponent.h"
#include "UILabel.h"
class BulletComponent;

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
    int Ftimer = 20;

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
    bool visable;

    EnemyController(bool DoA, int hp, int m, float s) {
        DeadorAlive = DoA;
        healthPoint = hp;
        nowMode = m;
        speed = s;
    }
    void fire(int x, int y, int f) {
        Mix_PlayChannel(f, Game::assets->GetSound("fire"), 0);
        int playerPositionX = *(&entity->getComponent<TransformComponent>().position.x) + (*(&entity->getComponent<SpriteComponent>().destRect.w) / 2);
        int playerPositionY = *(&entity->getComponent<TransformComponent>().position.y) + (*(&entity->getComponent<SpriteComponent>().destRect.h) / 2);

        double distanceX = x + (*(&entity->getComponent<SpriteComponent>().destRect.w) / 2) - playerPositionX;
        double distanceY = y + (*(&entity->getComponent<SpriteComponent>().destRect.h) / 2) - playerPositionY;
        double vecX = distanceX / sqrt(distanceX * distanceX + distanceY * distanceY);
        double vecY = distanceY / sqrt(distanceX * distanceX + distanceY * distanceY);

        auto &bullet(manager.addEntity());
        bullet.addComponent<BulletComponent>(playerPositionX, playerPositionY, vecX, vecY, "player");
        bullet.addGroup(Game::groupBullets);
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
            // auto &labels(manager.getGroup(Game::groupLabels));

            // std::stringstream str;
            // str << transform->position.x << " , " << transform->position.y;
            // labels[3]->getComponent<UILabel>().SetLabelText(str.str(), "Cubic");
            // std::stringstream str_;
            // str_ << nowx << " , " << nowy;
            // labels[4]->getComponent<UILabel>().SetLabelText(str_.str(), "Cubic");
            if (RayTrace::checkBlockThrough(colliders, static_cast<int>((transform->position.x + sprite->destRect.w / 2)), static_cast<int>((transform->position.y + sprite->destRect.h / 2)), static_cast<int>(nowx + sprite->destRect.w / 2), static_cast<int>(nowy + sprite->destRect.h / 2))) {
                transform->velocity.x = 0;
                transform->velocity.y = 0;
                sprite->visable = false;
            } else {
                sprite->visable = true;
                sprite->angle = -10 + (atan2(distanceY, distanceX) * 180.0000) / M_PI;
                // FIRE
                Ftimer--;
                if (Ftimer < 0) {
                    fire(nowx, nowy, Ftimer % 5);
                    Ftimer = 20;
                }

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