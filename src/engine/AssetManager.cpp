#include "AssetManager.h"

AssetManager::AssetManager(Manager* man) : manager(man) {}

AssetManager::~AssetManager() {}

SDL_Texture* AssetManager::AddTexture(std::string id, const char* path) {
    textures.emplace(id, TextureManager::LoadTexture(path));
    return textures[id];
}

SDL_Texture* AssetManager::GetTexture(std::string id) {
    return textures[id];
}

void AssetManager::AddFont(std::string id, std::string path, int fontSize) {
    fonts.emplace(id, TTF_OpenFont(path.c_str(), fontSize));
}
TTF_Font* AssetManager::GetFont(std::string id) {
    return fonts[id];
}

void AssetManager::AddSound(std::string id, std::string path) {
    sounds.emplace(id, Mix_LoadWAV(path.c_str()));
}

Mix_Chunk* AssetManager::GetSound(std::string id) {
    return sounds[id];
}