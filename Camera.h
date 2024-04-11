#pragma once

class Camera {
public:
    Camera(int screenWidth, int screenHeight, int mapWidth, int mapHeight);

    void move(int dx, int dy);
    int getX() const { return x; }
    int getY() const { return y; }

private:
    int x;
    int y;
    int screenWidth;
    int screenHeight;
    int mapWidth;
    int mapHeight;
};
