#include "Engine.h"
#include "Entity.h"
#include "RendererComponent.h"

#include <SDL3/SDL.h>
#include <iostream>

int main()
{
	std::cout << "Hello World" << std::endl;

    // Initialize SDL3
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 0;
    }

    Engine engine;
    if (!engine.window.Create())
    {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 0;
    }

    // Event loop
    bool running = true;
    SDL_Event event;

    Entity test;
    test.AddComponent(new RendererComponent());

    // TODO: Create a struct that has the window (and other Engine that will arise). This struct will be passes to the Update of a Game class, which has the scenes, which have the entities (and maybe systems)

    while (running) {

        test.Update(engine);
        engine.window.Render();

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }
    }

    engine.window.Destroy();
    SDL_Quit();

	return 0;
}