#include "Engine.h"
#include "Entity.h"
#include "Game.h"

#include <SDL3/SDL.h>
#include <array>
#include <iostream>

#include <SDL3_image/SDL_image.h>


int main()
{
    // Init engine modules
    Engine engine;
    if (!engine.window.Create() || !engine.renderer.Create(engine.window.sdl_window) || !engine.inputs.Create())
    {
        std::cerr << "Error on creating SDL" << std::endl;
        SDL_Quit();
        return 0;
    }

    engine.random.Create();

    // Init game
    engine.timer.Tick(engine.inputs);

    Game game(engine);

    engine.timer.Tick(engine.inputs);
    std::cout << "World gen time: " << engine.timer.delta_time << std::endl;

    // Main loop
    bool running = true;

    while (running) 
    {
        // Timer
        engine.timer.Tick(engine.inputs);

        // Inputs
        if (!engine.inputs.Update(engine.window)) running = false;
        
        // Game Update
        engine.renderer.PreRender();
        SDL_SetRenderDrawColor(engine.renderer.sdl_renderer, 255, 255, 255, 255);

        game.Update(engine);

        // Render
        engine.renderer.RenderDebugText("FPS: " + std::to_string(1000.0f / engine.timer.delta_time), { 5.0f, 5.0f });
        engine.renderer.RenderDebugText("ms: " + std::to_string(engine.timer.delta_time), { 165.0f, 5.0f });
        engine.renderer.RenderDebugText("time elapsed: " + std::to_string(engine.timer.elapsed_time / 1000.0f), { 290.0f, 5.0f });
        engine.renderer.RenderDebugText("F1 - Toggle Debug Mode", { 1400.0f, 5.0f });
        engine.renderer.RenderDebugText("F2 - Free camera", { 1600.0f, 5.0f });
        engine.renderer.RenderDebugText("F3 - Speed up time", { 1750.0f, 5.0f });

        engine.renderer.Render();

    }

    engine.inputs.Destroy();
    engine.renderer.Destroy();
    engine.window.Destroy();

    // Quit SDL3
    SDL_Quit();

	return 0;
}