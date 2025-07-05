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

    // TODO: Move all the tiles and texture logics from main. Right now is here for fast testing of how things work

    const int mapWidth = 8400;
    const int mapHeight = 2400;
    const int mapSize = mapWidth * mapHeight;
    Tile* tiles = new Tile[mapSize];

    engine.timer.Tick();

    for (int x = 0; x < mapWidth; ++x)
    {
        for (int y = 0; y < mapHeight; ++y)
        {
            tiles[mapWidth * y + x].pos = { (float)x * 16 - mapWidth * 8, (float)y * 16 - mapHeight * 8, 16.0f, 16.0f };

            if (y - mapHeight / 2 > 0)
            {
               tiles[mapWidth * y + x].type = 1;
            }
        }
    }

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

        uint8_t r = 0;
        uint8_t g = 0;
        uint8_t b = 0;
        for (int x = 0; x < mapWidth; ++x)
        {
            for (int y = 0; y < mapHeight; ++y)
            {
                if (x - mapWidth / 2 > -60 && x - mapWidth / 2 < 60 && y - mapHeight / 2 > -34 && y - mapHeight / 2 < 34)
                {
                    switch (tiles[y * mapWidth + x].type)
                    {
                    case 0:
                        engine.renderer.RenderRect(tiles[y * mapWidth + x].pos, 0, 50, 200, 255, 1.0f, false);
                        //engine.renderer.RenderTexture(tiles_texture, { 0, 32.0f, 32.0f, 32.0f }, { tiles[y * mapWidth + x].pos.x, tiles[y * mapWidth + x].pos.y, 16.0f, 16.0f }, 1.0f);
                        break;
                    case 1:
                        //engine.renderer.RenderRect(tiles[y * mapWidth + x].pos, 50, 200, 0, 255, 1.0f, true);
                        engine.renderer.RenderTexture(tiles_texture, algo, tiles[y * mapWidth + x].pos, 1.0f);

                        break;
                    }
                    
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