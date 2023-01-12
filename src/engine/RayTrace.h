#pragma once
#include <iostream>
#include <vector>

#include "Components.h"
#include "ECS/ECS.h"

class RayTrace {
   public:
    static bool checkThrough(std::vector<Entity*> entitys, int x, int y, int x2, int y2) {
        std::cout << x << ',' << y << ':' << x2 << ',' << y2 << std::endl;
        double a_ = static_cast<double>(y2 - y) / static_cast<double>(x2 - x);
        double b_ = static_cast<double>(y) - a_ * static_cast<double>(x);
        int a = static_cast<int>(a_);
        int b = static_cast<int>(b_);
        bool through = true;
        for (auto& c : entitys) {
            auto Collider = (c->getComponent<ColliderComponent>().srcR);
            if (((a * Collider.x + b - Collider.y) < 0) && ((a * (Collider.x + Collider.w) + b - Collider.y) < 0) && ((a * Collider.x + b - (Collider.y + Collider.h)) < 0) && ((a * (Collider.x + Collider.w) + b - (Collider.y + Collider.h)) < 0)) {
            } else if (((a * Collider.x + b - Collider.y) > 0) && ((a * (Collider.x + Collider.w) + b - Collider.y) > 0) && ((a * Collider.x + b - (Collider.y + Collider.h)) > 0) && ((a * (Collider.x + Collider.w) + b - (Collider.y + Collider.h)) > 0)) {
            } else {
                if (x > x2 && y > y2) {
                    // 檢查單點 warn
                    std::cout << "A>X>B" << std::endl;
                    if (x2 < Collider.x && Collider.x < x && y2 < Collider.y && Collider.y < y) {
                        through = false;
                    }
                } else {
                    std::cout << "A<X<B" << std::endl;
                    if (x < Collider.x && Collider.x < x2 && y < Collider.y && Collider.y < y2) {
                        through = false;
                    }
                }
            }
        }
        return through;
    }
};
