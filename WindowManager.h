#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <SDL.h>
#include <iostream>
#include <vector>

class WindowManager {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    int screenWidth;
    int screenHeight;
    int gridSize;
    std::vector<std::vector<int>> gridMap;

public:
    WindowManager(int width, int height, int gridSize, std::vector<std::vector<int>> map);
    ~WindowManager();

    bool init();
    void render();
    void close();
    void drawGrid();
    int getScreenWidth() const;
    int getScreenHeight() const;
    SDL_Renderer* getRenderer() const;
};

#endif // WINDOWMANAGER_H
