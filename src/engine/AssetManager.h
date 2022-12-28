#pragma once
#include <SDL2/SDL_ttf.h>

#include <map>
#include <string>

#include "ECS/ECS.h"
#include "TextureManager.h"
#include "Vector2D.h"

class AssetManager {
   public:
    AssetManager(Manager* man);
    ~AssetManager();

    // gameobjects

    // texture management
    void AddTexture(std::string id, const char* path);
    SDL_Texture* GetTexture(std::string id);

    void AddFont(std::string id, std::string path, int fontSize);
    TTF_Font* GetFont(std::string id);

   private:
    Manager* manager;
    std::map<std::string, SDL_Texture*> textures;
    std::map<std::string, TTF_Font*> fonts;
};