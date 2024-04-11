#include <stdio.h>
#include <iostream>
#include "WindowManager.h"
#include "WorldGenerator.h"
#include "Camera.h"
#include <SDL.h>

//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;

const Uint8* keystate;

int main( int argc, char* args[] )
{
	WorldGenerator world = WorldGenerator();
    Camera camera = Camera(SCREEN_WIDTH, SCREEN_HEIGHT, 50, 50);
	int grid_size = world.getGridSize();
	std::vector<std::vector<bool>> map = world.getMap();
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
        // Assuming you have access to the WindowManager and Camera objects
        keystate = SDL_GetKeyboardState(NULL);
        if (keystate[SDL_SCANCODE_UP]) {
            camera.move(0, -1);
        } else if (keystate[SDL_SCANCODE_DOWN]) {
            camera.move(0, 1);
        } else if (keystate[SDL_SCANCODE_LEFT]) {
            camera.move(-1, 0);
        } else if (keystate[SDL_SCANCODE_RIGHT]) {
            camera.move(1, 0);
        }
        window.render(camera);
    }

    window.close();
    return 0;
}
