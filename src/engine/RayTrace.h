#pragma once
#include <iostream>
#include <vector>

#include "Components.h"
#include "ECS/ECS.h"

class RayTrace {
   public:
    static bool checkThrough(std::vector<Entity*> entitys, int x, int y, int x2, int y2) {
        double a_ = static_cast<double>(y2 - y) / static_cast<double>(x2 - x);
        double b_ = static_cast<double>(y) - a_ * static_cast<double>(x);
        int a = static_cast<int>(a_);
        int b = static_cast<int>(b_);

        for (auto& c : entitys) {
            auto Collider = (c->getComponent<ColliderComponent>().destR);
            if (((a * Collider.x + b - Collider.y) < 0) && ((a * (Collider.x + Collider.w) + b - Collider.y) < 0) && ((a * Collider.x + b - (Collider.y + Collider.h)) < 0) && ((a * (Collider.x + Collider.w) + b - (Collider.y + Collider.h)) < 0)) {
                return false;
            }
            if (((a * Collider.x + b - Collider.y) > 0) && ((a * (Collider.x + Collider.w) + b - Collider.y) > 0) && ((a * Collider.x + b - (Collider.y + Collider.h)) > 0) && ((a * (Collider.x + Collider.w) + b - (Collider.y + Collider.h)) > 0)) {
                return false;
            }
        }
        return true;
    }
};
