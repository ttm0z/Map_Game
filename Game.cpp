#include <stdio.h>
#include <iostream>
#include "WindowManager.h"
#include "WorldGenerator.h"


//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main( int argc, char* args[] )
{
	WorldGenerator world = WorldGenerator();
	int grid_size = world.getGridSize();
	std::vector<std::vector<int>> map = world.getMap();
	WindowManager window = WindowManager(SCREEN_WIDTH, SCREEN_HEIGHT, grid_size, map);


	if (!window.init()) {
        std::cout << "Failed to initialize WindowManager!" << std::endl;
        return 1;
    }

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        window.render();
    }

    window.close();
    return 0;
}
