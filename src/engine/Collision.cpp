#include "Collision.h"

#include "ColliderComponent.h"

bool Collision::AABB(const SDL_Rect& recA, const SDL_Rect& recB) {
    if (
        recA.x + recA.w >= recB.x &&
        recB.x + recB.w >= recA.x &&
        recA.y + recA.h >= recB.y &&
        recB.y + recB.h >= recA.y) {
        return true;
    }

    return false;
}

bool Collision::AABB(const SDL_Rect& recA, const Vector2D& recB) {
    if (
        recB.x >= recA.x && recB.x <= recA.x + recA.w &&
        recB.y >= recA.y && recB.y <= recA.y + recA.h) {
        return true;
    }

    return false;
}

bool Collision::AABB(const ColliderComponent& colA, const ColliderComponent& colB) {
    if (AABB(colA.collider, colB.collider)) {
        // std::cout << colA.tag << " hit: " << colB.tag << std::endl;
        return true;
    } else {
        return false;
    }
}
