#pragma once

#include "../header/Game.h"
#include "Components.h"
#include "ECS/ECS.h"
#include "SpriteComponent.h"
#include "TransformComponent.h"
#include "TextureManager.h"

extern Manager manager;
using std::cin;
using std::cout;
using std::endl;
using std::vector;

class PlayerStatComponent : public Component
{
public:

    bool DeadorAlive;
    int healthPoint;

    PlayerStatComponent(int hp)
    {
        DeadorAlive = true;
        healthPoint = hp;
    }

    void init() override
    {

    }

    void damaged(float damage)
    {
        healthPoint -= damage;
    }

    void update() override
    {

    }
};