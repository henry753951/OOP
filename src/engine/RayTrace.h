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
        bool through = true;
        for (auto& c : entitys) {
            auto Collider = (c->getComponent<ColliderComponent>().collider);

            // 玩家在敵人右上角
            if (x < x2 && y > y2) {
                if (((Collider.x > x && Collider.y < y) && (Collider.x < x2 && Collider.y > y2))) {
                    return false;
                }
                if (((Collider.x + Collider.w > x && Collider.y < y) && (Collider.x + Collider.w < x2 && Collider.y < y2))) {
                    return false;
                }
                if (((Collider.x > x && Collider.y + Collider.h < y) && (Collider.x < x2 && Collider.y + Collider.h < y2))) {
                    return false;
                }
                if (((Collider.x + Collider.w > x && Collider.y + Collider.h < y) && (Collider.x + Collider.w < x2 && Collider.y + Collider.h < y2))) {
                    return false;
                }
                // 玩家在敵人左下角
            } else if (x > x2 && y < y2) {
                if (((Collider.x < x && Collider.y > y) && (Collider.x > x2 && Collider.y < y2))) {
                    return false;
                }
                if (((Collider.x + Collider.w < x && Collider.y > y) && (Collider.x + Collider.w > x2 && Collider.y < y2))) {
                    return false;
                }
                if (((Collider.x < x && Collider.y + Collider.h > y) && (Collider.x > x2 && Collider.y + Collider.h < y2))) {
                    return false;
                }
                if (((Collider.x + Collider.w < x && Collider.y + Collider.h > y) && (Collider.x + Collider.w > x2 && Collider.y + Collider.h < y2))) {
                    return false;
                }
                // 玩家在敵人左上角
            } else if (x > x2 && y > y2) {
                if (((Collider.x < x && Collider.y < y) && (Collider.x > x2 && Collider.y > y2))) {
                    return false;
                }
                if (((Collider.x + Collider.w < x && Collider.y < y) && (Collider.x + Collider.w > x2 && Collider.y > y2))) {
                    return false;
                }
                if (((Collider.x < x && Collider.y + Collider.h < y) && (Collider.x > x2 && Collider.y + Collider.h > y2))) {
                    return false;
                }
                if (((Collider.x + Collider.w < x && Collider.y + Collider.h < y) && (Collider.x + Collider.w > x2 && Collider.y + Collider.h > y2))) {
                    return false;
                }
                // 玩家在敵人右下角
            } else if (x < x2 && y < y2) {
                if (((Collider.x > x && Collider.y > y) && (Collider.x < x2 && Collider.y < y2))) {
                    return false;
                }
                if (((Collider.x + Collider.w > x && Collider.y > y) && (Collider.x + Collider.w < x2 && Collider.y < y2))) {
                    return false;
                }
                if (((Collider.x > x && Collider.y + Collider.h > y) && (Collider.x < x2 && Collider.y + Collider.h < y2))) {
                    return false;
                }
                if (((Collider.x + Collider.w > x && Collider.y + Collider.h > y) && (Collider.x + Collider.w < x2 && Collider.y + Collider.h < y2))) {
                    return false;
                }
            }
        }
        return through;
    }
};
