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

class EnemyController : public Component {
   private:
    vector<Entity *> players;

   public:
    TransformComponent *transform;
    SpriteComponent *sprite;
    void init() override {
        players = manager.getGroup(Game::groupPlayers);
        transform = &entity->getComponent<TransformComponent>();
        sprite = &entity->getComponent<SpriteComponent>();
    }

    void update() override {
        if (transform->velocity.y == 0 && transform->velocity.x == 0) {
            sprite->Play("pistol_idle");
        } else {
            sprite->Play("pistol_walk");
        }
        if (Game::event.type == SDL_KEYDOWN) {
            switch (Game::event.key.keysym.sym) {
                case SDLK_w:
                    transform->velocity.y = -1;
                    break;
                case SDLK_a:
                    transform->velocity.x = -1;
                    break;
                case SDLK_d:
                    transform->velocity.x = 1;
                    break;
                case SDLK_s:
                    transform->velocity.y = 1;
                    break;
                case SDLK_LSHIFT:
                    transform->speed = 5;
                    sprite->speed = 150;
                    break;
                default:
                    break;
            }
        }

        if (Game::event.type == SDL_KEYUP) {
            switch (Game::event.key.keysym.sym) {
                case SDLK_w:
                    transform->velocity.y = 0;
                    break;
                case SDLK_a:
                    transform->velocity.x = 0;
                    break;
                case SDLK_d:
                    transform->velocity.x = 0;
                    break;
                case SDLK_s:
                    transform->velocity.y = 0;
                    break;
                case SDLK_LSHIFT:
                    transform->speed = 3;
                    sprite->speed = 100;
                    break;
                case SDLK_ESCAPE:
                    Game::isRunning = false;
                default:
                    break;
            }
        }
    }
};