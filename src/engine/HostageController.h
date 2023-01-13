#pragma once

#include "../header/Game.h"
#include "Components.h"
#include "ECS/ECS.h"
#include "TransformComponent.h"
#include "TextureManager.h"

extern Manager manager;
using std::cin;
using std::cout;
using std::endl;
using std::vector;

class HostageController : public Component
{
private:
    vector<Entity *> players;
    float distance,distanceX, distanceY;

public:
    SDL_Texture *texture;
    TransformComponent *transform;
    ColliderComponent *collider;
    SDL_Rect srcRect, destRect;

    bool DeadorAlive;
    int healthPoint;
    int nowMode;
    float speed;
    float nowx, nowy;
    int offset;

    HostageController(bool DoA, int hp, int m, float s)
    {
        DeadorAlive = DoA;
        healthPoint = hp;
        nowMode = m;
        speed = s;
    }

    void init() override
    {
        players = manager.getGroup(Game::groupPlayers);
        transform = &entity->getComponent<TransformComponent>();
        collider = &entity->getComponent<ColliderComponent>();
        texture = Game::assets->GetTexture("hostage");
        srcRect.x = srcRect.y = 0;
        srcRect.w = 1281;
        srcRect.h = 1535;
        destRect.w = 1281 * 0.05;
        destRect.h = 1535 * 0.05;
        // nowMode = 0;
    }

    void damaged(float damage)
    {
        healthPoint -= damage;
    }

    void update() override
    {
        if(srcRect.y <1500){
            
        }
        if (healthPoint <= 0 && DeadorAlive == true)
        {
            DeadorAlive = false;
            transform->velocity.x = 0;
            transform->velocity.y = 0;
            destRect.w = destRect.h = 256 * 0.25;
        }

        if (DeadorAlive == true)
        {
            for (auto &p : players)
            {
                nowx = (p->getComponent<TransformComponent>().position.x);
                nowy = (p->getComponent<TransformComponent>().position.y);
                distanceX = nowx - transform->position.x;
                distanceY = nowy - transform->position.y;
                // cout << distanceX << " ";
                // cout << distanceY << endl;
            }

            distance = sqrt(pow(distanceX, 2) + pow(distanceY, 2));

            if (nowMode == 0 || distance <= 30)
            {
                transform->velocity.x = 0;
                transform->velocity.y = 0;
            }
            else if (nowMode == 1)
            {
                transform->velocity.x = speed * (distanceX / distance);
                transform->velocity.y = speed * (distanceY / distance);
            }
        }
        destRect.x = static_cast<int>(transform->position.x - Game::camera.x);
        destRect.y = static_cast<int>(transform->position.y - Game::camera.y);

        if (Game::event.type == SDL_KEYDOWN && Game::event.key.keysym.sym == SDLK_f && distance <= 100) {
            if(nowMode == 0)
                nowMode = 1;
            else
                nowMode = 0;
        }
    }

    void draw() override
    {
        TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
    }
};