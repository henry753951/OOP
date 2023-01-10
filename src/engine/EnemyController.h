#pragma once

#include "../header/Game.h"
#include "Components.h"
#include "ECS/ECS.h"
#include "SpriteComponent.h"
#include "TransformComponent.h"

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
    TransformComponent *transform;
    SpriteComponent *sprite;

    bool DeadorAlive;
    int healthPoint;
    int nowMode;
    float speed;

    EnemyController(bool DoA, int hp, int m, float s) {
        DeadorAlive = DoA;
        healthPoint = hp;
        nowMode = m;
        speed = s;
    }

    void init() override
    {
        players = manager.getGroup(Game::groupPlayers);
        transform = &entity->getComponent<TransformComponent>();
        sprite = &entity->getComponent<SpriteComponent>();
        
    }

    void damaged(float damage){
        healthPoint -= damage;
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

        if (transform->velocity.y == 0 && transform->velocity.x == 0) {
            sprite->Play("pistol_idle");
        }
        else
        {
            sprite->Play("pistol_walk");
        }

        if(nowMode == 0  && distanceX == 0 && distanceY == 0){
            transform->velocity.x = 0;
            transform->velocity.y = 0;
        }else if(nowMode == 0){
            transform->velocity.x =  speed * (distanceX / sqrt(pow(distanceX,2)+pow(distanceY,2)));
            transform->velocity.y =  speed * (distanceY / sqrt(pow(distanceX,2)+pow(distanceY,2)));
        }
    }
};