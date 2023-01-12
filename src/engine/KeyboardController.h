#pragma once

#include <math.h>

#include "../BulletComponent.h"
#include "../header/Game.h"
#include "Components.h"
#include "ECS/ECS.h"
#include "SpriteComponent.h"
#include "TransformComponent.h"
using std::cin;
using std::cout;
using std::endl;
extern Manager manager;

class KeyboardController : public Component {
   public:
    TransformComponent *transform;
    SpriteComponent *sprite;
    int timer = 0;
    int timer2 = 0;
    int clip = 15;
    bool TakingHostage = false;

    void init() override {
        transform = &entity->getComponent<TransformComponent>();
        sprite = &entity->getComponent<SpriteComponent>();
    }

    void update() override {
        int mousePosX = 0;
        int mousePosY = 0;
        SDL_GetMouseState(&mousePosX, &mousePosY);

        if (Game::event.type == SDL_MOUSEBUTTONDOWN) {
            switch (Game::event.button.button) {
                case SDL_BUTTON_LEFT:
                    if(clip > 0 && SDL_GetTicks() - timer2 >= 900){
                        fire(mousePosX, mousePosY);
                        sprite->Play("pistol_fire");
                        timer = SDL_GetTicks();
                    }
                    break;
                case SDL_BUTTON_RIGHT:
                    break;
                default:
                    break;
            }
        }
        if(SDL_GetTicks() - timer >= 90 && SDL_GetTicks() - timer2 >= 900){
            if (transform->velocity.y == 0 && transform->velocity.x == 0) {
                sprite->Play("pistol_idle");
            } else {
                sprite->Play("pistol_walk");
            }
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
                case SDLK_r:
                    if(clip < 15){
                        sprite->Play("pistol_reload");
                        timer2 = SDL_GetTicks();
                        clip = 15;
                    }
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

    void fire(int x, int y) {
        clip--;
        double playerPositionX = *(&entity->getComponent<TransformComponent>().position.x) + (*(&entity->getComponent<SpriteComponent>().destRect.w) / 2);
        double playerPositionY = *(&entity->getComponent<TransformComponent>().position.y) + (*(&entity->getComponent<SpriteComponent>().destRect.h) / 2);

        double distanceX = x + Game::camera.x - playerPositionX;
        double distanceY = y + Game::camera.y - playerPositionY;
        double vecX = distanceX / sqrt(distanceX * distanceX + distanceY * distanceY);
        double vecY = distanceY / sqrt(distanceX * distanceX + distanceY * distanceY);

        auto &bullet(manager.addEntity());
        bullet.addComponent<BulletComponent>(playerPositionX, playerPositionY, vecX, vecY);
        bullet.addGroup(Game::groupBullets);
    }
};