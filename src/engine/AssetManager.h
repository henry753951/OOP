#pragma once
#include <SDL2/SDL_mixer.h>
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
    SDL_Texture* AddTexture(std::string id, const char* path);
    SDL_Texture* GetTexture(std::string id);

    void AddFont(std::string id, std::string path, int fontSize);
    TTF_Font* GetFont(std::string id);

    void AddSound(std::string id, std::string path);
    Mix_Chunk* GetSound(std::string id);

   private:
    Manager* manager;
    std::map<std::string, SDL_Texture*> textures;
    std::map<std::string, TTF_Font*> fonts;
    std::map<std::string, Mix_Chunk*> sounds;
};