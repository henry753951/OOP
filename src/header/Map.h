#include <string>

#include "Game.h"

class Map {
   public:
    Map(std::string tID, int ms, int ts);
    ~Map();

    void LoadMap(std::string path, std::string ColliderMapPath, int sizeX, int sizeY);
    void AddTile(int srcX, int srcY, int xpos, int ypos);

   private:
    std::string texID;
    int mapScale;
    int tileSize;
    int scaledSize;
    int rows;
    int cols;
};