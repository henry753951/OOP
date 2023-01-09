#pragma once

#include "../header/Game.h"
#include "Components.h"
#include "ECS/ECS.h"
#include "SpriteComponent.h"
#include "TransformComponent.h"
#include "../EnemyStatComponent.h"

extern Manager manager;
using std::cin;
using std::cout;
using std::endl;
using std::vector;

class EnemyController : public Component
{
private:
    vector<Entity *> players;
    float distanceX, distanceY;

public:
    EnemyStatComponent *stat;
    TransformComponent *transform;
    SpriteComponent *sprite;

    void init() override
    {
        players = manager.getGroup(Game::groupPlayers);
        transform = &entity->getComponent<TransformComponent>();
        stat = &entity->getComponent<EnemyStatComponent>();
        sprite = &entity->getComponent<SpriteComponent>();
    }

    void update() override {
               for (auto &p : players)
        {
            distanceX = (p->getComponent<TransformComponent>().position.x) - transform->position.x;
            distanceY = (p->getComponent<TransformComponent>().position.y) - transform->position.y;
            // cout << distanceX << " ";
            // cout << distanceY << endl;
        }

        sprite->angle = -10 + (atan2(distanceY, distanceX) * 180.0000) / M_PI;
        // cout << sprite->angle << endl;

                       // 面向滑鼠
                       //  if (sprite->destRect.x + 32 < mousePosX) {
                       //      sprite->spriteFlip = SDL_FLIP_NONE;
                       //  } else if (sprite->destRect.x + 32 > mousePosX) {
                       //      sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
                       //  }

                       //  動畫
        if (transform->velocity.y == 0 && transform->velocity.x == 0) {
            sprite->Play("pistol_idle");
        }
        else
        {
            sprite->Play("pistol_walk");
        }

        if(stat->nowMode == 0  && distanceX == 0 && distanceY == 0){
            transform->velocity.x = 0;
            transform->velocity.y = 0;
        }else if(stat->nowMode == 0){
            transform->velocity.x =  stat->speed * (distanceX / sqrt(pow(distanceX,2)+pow(distanceY,2)));
            transform->velocity.y =  stat->speed * (distanceY / sqrt(pow(distanceX,2)+pow(distanceY,2)));
        }

        // if (Game::event.type == SDL_KEYUP) {
        //     switch (Game::event.key.keysym.sym) {
        //         case SDLK_w:
        //             transform->velocity.y = 0;
        //             break;
        //         case SDLK_a:
        //             transform->velocity.x = 0;
        //             break;
        //         case SDLK_d:
        //             transform->velocity.x = 0;
        //             break;
        //         case SDLK_s:
        //             transform->velocity.y = 0;
        //             break;
        //         case SDLK_LSHIFT:
        //             transform->speed = 3;
        //             sprite->speed = 100;
        //             break;
        //         case SDLK_ESCAPE:
        //             Game::isRunning = false;
        //         default:
        //             break;
        //     }
        // }
    }
};