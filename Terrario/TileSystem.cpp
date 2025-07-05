#include "TileSystem.h"

#include "Engine.h"

#include "SDL3/SDL_rect.h"

void TileSystem::CreateTilesArray()
{
    tilemap.type = new int[worldSize];
    tilemap.pos = new Vector2[worldSize];

    for (int x = 0; x < worldWidth; ++x)
    {
        for (int y = 0; y < worldHeight; ++y)
        {
            tilemap.pos[worldWidth * y + x] = { static_cast<float>(x * 16 - worldWidth * 8), static_cast<float>(y * 16 - worldHeight * 8) };

            if (y - worldHeight / 2 > 0)
            {
                tilemap.type[worldWidth * y + x] = 1;
            }
            else
            {
                tilemap.type[worldWidth * y + x] = 0;
            }
        }
    }
}

void TileSystem::DeleteTilesArray()
{
    delete[] tilemap.pos;
    delete[] tilemap.type;
}

void TileSystem::Update(Engine& engine)
{
    int x_bounds =  engine.renderer.GetCameraPos().x;
    int y_bounds =  engine.renderer.GetCameraPos().y;

    //int x_upper_bound = engine.renderer.GetCameraPos().x + Globals::WINDOW_WIDTH / 2;
    //int x_lower_bound = engine.renderer.GetCameraPos().x - Globals::WINDOW_WIDTH / 2;
    //
    //int y_upper_bound = engine.renderer.GetCameraPos().y + Globals::WINDOW_HEIGHT / 2;
    //int y_lower_bound = engine.renderer.GetCameraPos().y - Globals::WINDOW_HEIGHT / 2;

    for (int x = 0; x < worldWidth; ++x)
    {
        for (int y = 0; y < worldHeight; ++y)
        {
            if (x - worldWidth / 2 -  x_bounds > -60 && x - worldWidth / 2 - x_bounds < 60 && y - worldHeight / 2 - y_bounds > -34 && y - worldHeight / 2 - y_bounds < 34)
            {
                switch (tilemap.type[y * worldWidth + x])
                {
                case 0:
                    engine.renderer.RenderTexture(tiles_texture, { 0, 32.0f, 32.0f, 32.0f }, { tilemap.pos[y * worldWidth + x].x, tilemap.pos[y * worldWidth + x].y, 16.0f, 16.0f }, 1.0f);
                    break;
                case 1:
                    engine.renderer.RenderTexture(tiles_texture, { 32.0f, 0.0f, 32.0f, 32.0f }, { tilemap.pos[y * worldWidth + x].x, tilemap.pos[y * worldWidth + x].y, 16.0f, 16.0f }, 1.0f);
                    break;
                }
            }

        }
    }
}