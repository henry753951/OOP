#pragma once
#include <string>
struct Animation {
    int index;
    int frames;
    int speed;
    std::string key;
    int width;
    int height;
    Animation() {}
    Animation(std::string k, int w, int h, int i, int f, int s) {
        key = k;
        width = w;
        height = h;
        index = i;
        frames = f;
        speed = s;
    }
};