#include "WindowManager.h"
#include "Camera.h"
#include <iostream>
#include <vector>
#include <algorithm>

WindowManager::WindowManager(int width, int height, int gridSize, std::vector<std::vector<bool>> map) : 
screenWidth(width), screenHeight(height), gridSize(gridSize), 
window(nullptr), renderer(nullptr), gridMap(map) {
    
    // print the grid map
        std::cout<<"Grid Map Size: " << gridMap.size() << ", " << gridMap[0].size() <<std::endl;
        std::cout<<"Grid Size: " << gridSize << std::endl; 
        std::cout<<"width: " << screenWidth << std::endl; 
        std::cout<<"height: " << screenHeight << std::endl;
        std::cout<<"#cells X: " << (double)screenWidth / gridSize << std::endl; 
        std::cout<<"#cells Y: " << (double)screenHeight / gridSize << std::endl; 

}

WindowManager::~WindowManager() {
    close();
}

bool WindowManager::init() {

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void WindowManager::render(const Camera& camera) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    drawGrid();

    double cellWidth = (double)screenWidth / gridSize;
    double cellHeight = (double)screenHeight / gridSize;
    int cameraX = camera.getX();
    int cameraY = camera.getY();

    // Calculate visible range of cells based on camera position
    int startX = cameraX / cellWidth;
    int startY = cameraY / cellHeight;
    int endX = std::min<int>(static_cast<int>(gridMap[0].size()), static_cast<int>((cameraX + screenWidth) / cellWidth) + 1);
    int endY = std::min<int>(static_cast<int>(gridMap.size()), static_cast<int>((cameraY + screenHeight) / cellHeight) + 1);

    // Render visible portion of the map
    for (int y = startY; y < endY; ++y) {
        for (int x = startX; x < endX; ++x) {
            // Calculate cell position
            SDL_Rect cellRect = { static_cast<int>((x - startX) * cellWidth), static_cast<int>((y - startY) * cellHeight), static_cast<int>(cellWidth), static_cast<int>(cellHeight) };

            if (gridMap[y][x]) {
                SDL_SetRenderDrawColor(renderer, 0, 100, 0, 255);
            }
            else {
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
            }

            // Render cell
            SDL_RenderFillRect(renderer, &cellRect);
        }
    }

    SDL_RenderPresent(renderer);
}




void WindowManager::drawGrid(){

    int grid_x = screenWidth / gridSize;
    int grid_y = screenHeight / gridSize;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    for (int x = 0; x < screenWidth; x += grid_x) {
        SDL_RenderDrawLine(renderer, x, 0, x, screenHeight);
    }
    for (int y = 0; y < screenHeight; y += grid_y) {
        SDL_RenderDrawLine(renderer, 0, y, screenWidth, y);
    }
}

void WindowManager::close() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int WindowManager::getScreenWidth() const { return screenWidth; }
int WindowManager::getScreenHeight() const { return screenHeight; }
SDL_Renderer* WindowManager::getRenderer() const { return renderer; }
