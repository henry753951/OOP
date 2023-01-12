#pragma once
#include <iostream>
#include <vector>

#include "Components.h"
#include "ECS/ECS.h"

class RayTrace {
   public:
    static bool checkThrough(const std::vector<Entity*> entitys, const int x, const int y, const int x2, const int y2) {
        double a_ = (y2 - y) / (x2 - x);
        double b_ = y - a_ * x;
        int a = static_cast<int>(a_);
        int b = static_cast<int>(b_);

        // for (auto& c : entitys) {
        //     auto Collider = (c->getComponent<ColliderComponent>().destR);
        //     auto c1 = ((a * Collider.x + b - Collider.y) < 0);
        //     auto c2 = ((a * (Collider.x + Collider.w) + b - Collider.y) < 0);
        //     auto c3 = ((a * Collider.x + b - (Collider.y + Collider.h)) < 0);
        //     auto c4 = ((a * (Collider.x + Collider.w) + b - (Collider.y + Collider.h)) < 0);
        //     if (c1 && c2 && c3 && c4 ){
        //         return false;
        //     }
        //     // if (((a * Collider.x + b - Collider.y) > 0) && ((a * (Collider.x + Collider.w) + b - Collider.y) > 0) && ((a * Collider.x + b - (Collider.y + Collider.h)) > 0) && ((a * (Collider.x + Collider.w) + b - (Collider.y + Collider.h)) > 0)) {
        //     //     return false;
        //     // }
        // }
        // return true;
        return false;
    }
};
