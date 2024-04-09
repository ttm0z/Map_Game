#include "WindowManager.h"
#include <iostream>
#include <vector>

WindowManager::WindowManager(int width, int height, int gridSize, std::vector<std::vector<int>> map) : 
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

void WindowManager::render() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    drawGrid();

    double cellWidth = (double)screenWidth / gridSize;
    double cellHeight = (double)screenHeight / gridSize;
    for (int y = 0; y < gridSize; ++y) {
        for (int x = 0; x < gridSize; ++x) {
            // Calculate cell position
            SDL_Rect cellRect = {(double)x * cellWidth, (double)y * cellHeight, cellWidth, cellHeight};
            // Set color based on value (example: alternate between red and blue)
            if (gridMap[y][x] > 0){
                SDL_SetRenderDrawColor(renderer, 0, 100, 0, 255);
            }
            else SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);    

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
