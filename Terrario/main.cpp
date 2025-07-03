#include "Engine.h"
#include "Entity.h"
#include "Game.h"

#include <SDL3/SDL.h>
#include <array>
#include <iostream>

#include <SDL3/Sdl_render.h>


//TODO: This can be a SoA?
struct Tile
{
    int type = 0;
    SDL_FRect rect{};
};


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

    const int mapWidth = 8400;
    const int mapHeight = 2200;
    const int mapSize = mapWidth * mapHeight;
    Tile* tiles = new Tile[mapSize];

    engine.timer.Tick();

    for (int x = 0; x < mapWidth; ++x)
    {
        for (int y = 0; y < mapHeight; ++y)
        {
            tiles[mapWidth * y + x].rect = { (float)x * 16 - mapWidth * 8, (float)y * 16 - mapHeight * 8, 16.0f, 16.0f };

            if (y - mapHeight / 2 > 0)
            {
               tiles[mapWidth * y + x].type = 1;
            }
        }
    }

    engine.timer.Tick();
    std::cout << "World gen time: " << engine.timer.delta_time << std::endl;

    while (running) 
    {
        // Timer
        engine.timer.Tick();

        // Inputs
        engine.inputs.Update();
        
        // Game Update

        uint8_t r = 0;
        uint8_t g = 0;
        uint8_t b = 0;
        for (int x = 0; x < mapWidth; ++x)
        {
            for (int y = 0; y < mapHeight; ++y)
            {
                if (x - mapWidth / 2 > -60 && x - mapWidth / 2 < 60 && y - mapHeight / 2 > -35 && y - mapHeight / 2 < 35)
                {
                    switch (tiles[y * mapWidth + x].type)
                    {
                    case 0:
                    {
                        r = 0;
                        g = 50;
                        b = 200;
                        break;
                    }
                    case 1:
                    {
                        r = 50;
                        g = 200;
                        b = 0;
                    }
                    }

                    //TODO: Pass here the position (probably calculated through the array pos) so no need tyo store so many SDL_FRects
                    engine.renderer.RenderRect(tiles[y * mapWidth + x].rect, r, g, b, 255, 1.0f, false);
                }

            }
        }

        game.Update(engine);


        // Render
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

    delete[] tiles;

    engine.inputs.Destroy();
    engine.renderer.Destroy();
    engine.window.Destroy();

    // Quit SDL3
    SDL_Quit();

	return 0;
}