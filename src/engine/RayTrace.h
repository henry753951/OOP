#pragma once
#include <iostream>
#include <sstream>
#include <vector>

#include "../header/Game.h"
#include "Components.h"
#include "ECS/ECS.h"
#include "UILabel.h"

extern Manager manager;

static bool isLineIntersectRectangle(float linePointX1,
                                     float linePointY1,
                                     float linePointX2,
                                     float linePointY2,
                                     float rectangleLeftTopX,
                                     float rectangleLeftTopY,
                                     float rectangleRightBottomX,
                                     float rectangleRightBottomY) {
    float lineHeight = linePointY1 - linePointY2;
    float lineWidth = linePointX2 - linePointX1;
    float c = linePointX1 * linePointY2 - linePointX2 * linePointY1;
    if ((lineHeight * rectangleLeftTopX + lineWidth * rectangleLeftTopY + c >= 0 &&
         lineHeight * rectangleRightBottomX + lineWidth * rectangleRightBottomY + c <= 0) ||
        (lineHeight * rectangleLeftTopX + lineWidth * rectangleLeftTopY + c <= 0 && lineHeight * rectangleRightBottomX + lineWidth * rectangleRightBottomY + c >= 0) ||
        (lineHeight * rectangleLeftTopX + lineWidth * rectangleRightBottomY + c >= 0 && lineHeight * rectangleRightBottomX + lineWidth * rectangleLeftTopY + c <= 0) ||
        (lineHeight * rectangleLeftTopX + lineWidth * rectangleRightBottomY + c <= 0 && lineHeight * rectangleRightBottomX + lineWidth * rectangleLeftTopY + c >= 0)) {
        if (rectangleLeftTopX > rectangleRightBottomX) {
            float temp = rectangleLeftTopX;
            rectangleLeftTopX = rectangleRightBottomX;
            rectangleRightBottomX = temp;
        }
        if (rectangleLeftTopY < rectangleRightBottomY) {
            float temp1 = rectangleLeftTopY;
            rectangleLeftTopY = rectangleRightBottomY;
            rectangleRightBottomY = temp1;
        }
        if ((linePointX1 < rectangleLeftTopX && linePointX2 < rectangleLeftTopX) ||
            (linePointX1 > rectangleRightBottomX && linePointX2 > rectangleRightBottomX) ||
            (linePointY1 > rectangleLeftTopY && linePointY2 > rectangleLeftTopY) ||
            (linePointY1 < rectangleRightBottomY && linePointY2 < rectangleRightBottomY)) {
            return false;
        } else {
            return true;
        }
    } else {
        return false;
    }
}

class RayTrace {
   public:
    static bool checkBlockThrough(std::vector<Entity*> entitys, int x, int y, int x2, int y2) {
        double a_ = static_cast<double>(y2 - y) / static_cast<double>(x2 - x);
        double b_ = static_cast<double>(y) - a_ * static_cast<double>(x);
        int a = static_cast<int>(a_);
        int b = static_cast<int>(b_);
        bool through = false;
        for (auto& c : entitys) {
            auto Collider = (c->getComponent<ColliderComponent>().collider);

            int p1X = Collider.x;
            int p1Y = Collider.y + Collider.h;
            int p2X = Collider.x + Collider.w;
            int p2Y = Collider.y;
            if (isLineIntersectRectangle(x, y, x2, y2, p1X, p1Y, p2X, p2Y)) {
                return true;
            }

            //  玩家在敵人右上角
            //  if (x < x2 && y > y2) {
            //      if (((Collider.x > x && Collider.y < y) && (Collider.x < x2 && Collider.y > y2))) {
            //          return false;
            //      }
            //      if (((Collider.x + Collider.w > x && Collider.y < y) && (Collider.x + Collider.w < x2 && Collider.y < y2))) {
            //          return false;
            //      }
            //      if (((Collider.x > x && Collider.y + Collider.h < y) && (Collider.x < x2 && Collider.y + Collider.h < y2))) {
            //          return false;
            //      }
            //      if (((Collider.x + Collider.w > x && Collider.y + Collider.h < y) && (Collider.x + Collider.w < x2 && Collider.y + Collider.h < y2))) {
            //          return false;
            //      }
            //      // 玩家在敵人左下角
            //  } else if (x > x2 && y < y2) {
            //      if (((Collider.x < x && Collider.y > y) && (Collider.x > x2 && Collider.y < y2))) {
            //          return false;
            //      }
            //      if (((Collider.x + Collider.w < x && Collider.y > y) && (Collider.x + Collider.w > x2 && Collider.y < y2))) {
            //          return false;
            //      }
            //      if (((Collider.x < x && Collider.y + Collider.h > y) && (Collider.x > x2 && Collider.y + Collider.h < y2))) {
            //          return false;
            //      }
            //      if (((Collider.x + Collider.w < x && Collider.y + Collider.h > y) && (Collider.x + Collider.w > x2 && Collider.y + Collider.h < y2))) {
            //          return false;
            //      }
            //      // 玩家在敵人左上角
            //  } else if (x > x2 && y > y2) {
            //      if (((Collider.x < x && Collider.y < y) && (Collider.x > x2 && Collider.y > y2))) {
            //          return false;
            //      }
            //      if (((Collider.x + Collider.w < x && Collider.y < y) && (Collider.x + Collider.w > x2 && Collider.y > y2))) {
            //          return false;
            //      }
            //      if (((Collider.x < x && Collider.y + Collider.h < y) && (Collider.x > x2 && Collider.y + Collider.h > y2))) {
            //          return false;
            //      }
            //      if (((Collider.x + Collider.w < x && Collider.y + Collider.h < y) && (Collider.x + Collider.w > x2 && Collider.y + Collider.h > y2))) {
            //          return false;
            //      }
            //      // 玩家在敵人右下角
            //  } else if (x < x2 && y < y2) {
            //      if (((Collider.x > x && Collider.y > y) && (Collider.x < x2 && Collider.y < y2))) {
            //          return false;
            //      }
            //      if (((Collider.x + Collider.w > x && Collider.y > y) && (Collider.x + Collider.w < x2 && Collider.y < y2))) {
            //          return false;
            //      }
            //      if (((Collider.x > x && Collider.y + Collider.h > y) && (Collider.x < x2 && Collider.y + Collider.h < y2))) {
            //          return false;
            //      }
            //      if (((Collider.x + Collider.w > x && Collider.y + Collider.h > y) && (Collider.x + Collider.w < x2 && Collider.y + Collider.h < y2))) {
            //          return false;
            //      }
            //  }
        }
        return through;
    }
};
