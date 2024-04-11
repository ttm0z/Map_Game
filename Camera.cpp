#include "Camera.h"

Camera::Camera(int screenWidth, int screenHeight, int mapWidth, int mapHeight)
    : x(0), y(0), screenWidth(screenWidth), screenHeight(screenHeight), mapWidth(mapWidth), mapHeight(mapHeight) {}

void Camera::move(int dx, int dy) {
    x += dx;
    y += dy;

    // Clamp camera position to stay within map bounds
    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (x > mapWidth - screenWidth) x = mapWidth - screenWidth;
    if (y > mapHeight - screenHeight) y = mapHeight - screenHeight;
}
