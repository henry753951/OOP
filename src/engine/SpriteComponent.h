#pragma once

#include <SDL2/SDL.h>

#include <map>

#include "Animation.h"
#include "AssetManager.h"
#include "Components.h"
#include "TextureManager.h"
#include "TransformComponent.h"

class SpriteComponent : public Component {
   private:
    TransformComponent* transform;
    SDL_Rect srcRect;

    bool animated = false;
    int frames = 0;

   public:
    SDL_Rect destRect;
    double angle;
    int speed = 100;
    int animIndex = 0;
    std::map<std::string, Animation> animations;
    std::string currentAnimName;
    SDL_Texture* texture;
    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

    SpriteComponent() = default;

    SpriteComponent(std::vector<Animation> animationList, bool isAnimated) {
        animated = isAnimated;
        for (auto animation : animationList) {
            animations.emplace(animation.key, animation);
        }
        Play(animationList[0].key);
    }

    ~SpriteComponent() {
    }

    void init() override {
        transform = &entity->getComponent<TransformComponent>();

        srcRect.x = srcRect.y = 0;
        srcRect.w = animations[currentAnimName].width;
        srcRect.h = animations[currentAnimName].height;
    }

    void update() override {
        srcRect.w = animations[currentAnimName].width;
        srcRect.h = animations[currentAnimName].height;

        srcRect.y = animIndex * animations[currentAnimName].height;

        destRect.x = static_cast<int>(transform->position.x - Game::camera.x);
        destRect.y = static_cast<int>(transform->position.y - Game::camera.y);
        destRect.w = animations[currentAnimName].width * transform->scale;
        destRect.h = animations[currentAnimName].height * transform->scale;
        texture = Game::assets->GetTexture(currentAnimName);
        if (animated) {
            srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
        }
    }

    void draw() override {
        TextureManager::Draw(texture, srcRect, destRect, spriteFlip, angle);
    }

    void Play(std::string animName) {
        frames = animations[animName].frames;
        animIndex = animations[animName].index;
        speed = animations[animName].speed;
        currentAnimName = animName;
    }
};