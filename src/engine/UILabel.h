#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <string>

#include "../header/Game.h"
#include "AssetManager.h"
#include "ECS/ECS.h"

class UILabel : public Component {
   public:
    UILabel(int xpos, int ypos, std::string text, std::string font, SDL_Color& colour) : labelText(text), labelFont(font), textColour(colour) {
        position.x = xpos;
        position.y = ypos;
        SetLabelText(labelText, labelFont);
    }
    ~UILabel() {}

    void SetLabelText(std::string text, std::string font) {
        SDL_Surface* surf = TTF_RenderText_Blended(Game::assets->GetFont(font), text.c_str(), textColour);
        labelTexture = SDL_CreateTextureFromSurface(Game::_renderer, surf);
        SDL_FreeSurface(surf);

        SDL_QueryTexture(labelTexture, nullptr, nullptr, &position.w, &position.h);
    }

    void draw() override {
        SDL_RenderCopy(Game::_renderer, labelTexture, nullptr, &position);
    }

   private:
    SDL_Rect position;
    std::string labelText;
    std::string labelFont;
    SDL_Color textColour;
    SDL_Texture* labelTexture;
};