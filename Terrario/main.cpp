#include "Engine.h"
#include "Entity.h"
#include "Game.h"

#include <SDL3/SDL.h>

int main()
{
    // Init engine modules
    Engine engine;
    if (!engine.window.Create() || !engine.renderer.Create(engine.window.sdl_window) || !engine.inputs.Create())
    {
        SDL_Quit();
        return 0;
    }

    // Init game
    Game game(engine);

    // Main loop
    bool running = true;
    SDL_Event event;

    // TODO: Create a struct that has the window (and other Engine that will arise). This struct will be passed to the Update of a Game class, which has the scenes, which have the entities (and maybe systems)

    uint64_t lastTick = 0;
    float preciseTimer = 0;

    while (running) {

        // Timer
        float deltaTime = (float)(SDL_GetTicksNS() - lastTick) / 1000000.0f;
        preciseTimer += deltaTime;
        lastTick = SDL_GetTicksNS();

        // Inputs
        engine.inputs.Update();
        
        // Game Update
        game.Update(engine);

        // Render
        engine.renderer.RenderDebugText("FPS: " + std::to_string(1000.0f / deltaTime) ,5.0f, 5.0f);
        engine.renderer.RenderDebugText("ms: " + std::to_string(deltaTime), 200.0f, 5.0f);
        engine.renderer.RenderDebugText("time elapsed: " + std::to_string(preciseTimer / 1000.0f), 400.0f, 5.0f);
        engine.renderer.Render();

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }
    }

    engine.inputs.Destroy();
    engine.renderer.Destroy();
    engine.window.Destroy();

    // Quit SDL3
    SDL_Quit();

	return 0;
}