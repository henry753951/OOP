#pragma once

#include <bits/stdc++.h>
#include "ECS/ECS.h"
#include "TextureManager.h"
#include "Vector2D.h"
#include "../header/Game.h"


extern Manager manager;
class UIComponent : public Component {
   public:
    SDL_Texture* texture;
    SDL_Rect srcRect, destRect;
    Vector2D position;
    UIComponent() = default;
    bool visible = true;

    ~UIComponent() {
        SDL_DestroyTexture(texture);
    }

    UIComponent(std::string n, int srcX, int srcY, int xpos, int ypos, int htsize, int wtsize, float tscale) {
        texture = Game::assets->GetTexture(n);

        srcRect.x = srcX;
        srcRect.y = srcY;
        srcRect.w = wtsize;
        srcRect.h = htsize;
        position.x = static_cast<float>(xpos);
        position.y = static_cast<float>(ypos);
        destRect.w = wtsize * tscale;
        destRect.h = htsize * tscale;
        destRect.x = static_cast<int>(xpos);
        destRect.y= static_cast<int>(ypos);
    }

    void update() override {
        
    }
    void draw() override {
        if(visible)
            TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
    }
};