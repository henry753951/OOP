#include "header/Map.h"

#include <fstream>
#include <iostream>

#include "engine/Components.h"
#include "engine/ECS/ECS.h"
#include "header/Game.h"
using namespace std;
extern Manager manager;

Map::Map(std::string tID, int ms, int ts) : texID(tID), mapScale(ms), tileSize(ts) {
    scaledSize = ms * ts;
}

Map::~Map() {
}

void Map::LoadMap(std::string path, std::string ColliderMapPath, int sizeX, int sizeY) {
    char c;

    int srcX, srcY;
    Game::assets->AddTexture("terrain", path.c_str());
    for (int y = 0; y < sizeY; y++) {
        for (int x = 0; x < sizeX; x++) {
            srcY = y * tileSize;
            srcX = x * tileSize;
            AddTile(srcX, srcY, x * scaledSize, y * scaledSize);
        }
    }
    // std::fstream mapFile;
    // mapFile.open(ColliderMapPath);
    // for (int y = 0; y < sizeY; y++) {
    //     for (int x = 0; x < sizeX; x++) {
    //         mapFile.get(c);
    //         if (c != '-1') {
    //             auto& tcol(manager.addEntity());
    //             tcol.addComponent<ColliderComponent>("terrain", x * scaledSize, y * scaledSize, 95);
    //             tcol.addGroup(Game::groupColliders);
    //         }
    //         mapFile.ignore();
    //     }
    // }

    // mapFile.close();
}

void Map::AddTile(int srcX, int srcY, int xpos, int ypos) {
    auto& tile(manager.addEntity());
    tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, tileSize, mapScale, texID);
    tile.addGroup(Game::groupMap);
}