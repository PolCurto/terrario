#include "Engine.h"
#include "Entity.h"
#include "Game.h"

#include <SDL3/SDL.h>
#include <array>
#include <iostream>

#include <SDL3_image/SDL_image.h>

//TODO: This can be a SoA?
struct Tile
{
    int type = 0;
    SDL_FRect pos{};
};


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

    // Init game
    Game game(engine);

    // Main loop
    bool running = true;
    SDL_Event event;

    engine.timer.Tick();

    SDL_Texture* tiles_texture = engine.renderer.LoadTexture("Textures/tiles.png");

    engine.timer.Tick();
    std::cout << "World gen time: " << engine.timer.delta_time << std::endl;

    SDL_FRect algo{};
    algo.x = 32.0f;
    algo.y = 0.0f;
    algo.w = 32.0f;
    algo.h = 32.0f;

    while (running) 
    {
        // Timer
        engine.timer.Tick();

        // Inputs
        engine.inputs.Update();
        
        // Game Update
        engine.renderer.PreRender();

        game.Update(engine);

        // Render
        SDL_SetRenderDrawColor(engine.renderer.sdl_renderer, 255, 255, 255, 255);
        engine.renderer.RenderDebugText("FPS: " + std::to_string(1000.0f / engine.timer.delta_time) ,5.0f, 5.0f);
        engine.renderer.RenderDebugText("ms: " + std::to_string(engine.timer.delta_time), 200.0f, 5.0f);
        engine.renderer.RenderDebugText("time elapsed: " + std::to_string(engine.timer.elapsed_time / 1000.0f), 400.0f, 5.0f);
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