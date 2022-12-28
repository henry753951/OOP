#include <iostream>

#include "header/Game.h"
int main(int argv, char** args) {
    Game* game = new Game();
    game->run();
    return 0;
}