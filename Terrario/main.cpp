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

    uint64_t lastTick = 0;
    uint64_t freq = SDL_GetPerformanceFrequency();;
    float preciseTimer = 0;

    while (running) {

        float deltaTime = (float)(SDL_GetTicksNS() - lastTick) / 1000000.0f;
        preciseTimer += deltaTime;
        lastTick = SDL_GetTicksNS();

        test.Update(engine);
        engine.window.RenderDebugText("FPS: " + std::to_string(1000.0f / deltaTime) ,5.0f, 5.0f);
        engine.window.RenderDebugText("ms: " + std::to_string(deltaTime), 200.0f, 5.0f);
        engine.window.RenderDebugText("time elapsed: " + std::to_string(preciseTimer / 1000.0f), 400.0f, 5.0f);
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