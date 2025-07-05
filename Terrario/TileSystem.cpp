#include "TileSystem.h"

#include "Engine.h"
#include "Globals.h"

#include "SDL3/SDL_rect.h"

void TileSystem::CreateTilesArray()
{
    tilemap = new Tile[TILEMAP_SIZE];

    for (int x = 0; x < TILEMAP_WIDTH; ++x)
    {
        for (int y = 0; y < TILEMAP_HEIGHT; ++y)
        {
            tilemap[TILEMAP_WIDTH * y + x].pos = { static_cast<float>(x * 16 - TILEMAP_WIDTH * 8), static_cast<float>(y * 16 - TILEMAP_HEIGHT * 8) };

            if (y - TILEMAP_HEIGHT / 2 > 0)
            {
                tilemap[TILEMAP_WIDTH * y + x].type = 1;
            }
            else
            {
                tilemap[TILEMAP_WIDTH * y + x].type = 0;
            }
        }
    }
}

void TileSystem::DeleteTilesArray()
{
    delete[] tilemap;
}

void TileSystem::Update(Engine& engine)
{

    // To update the tiles we need chunks

    // Tiles render
    int x_upper_bound = engine.renderer.GetCameraPos().x + Globals::WINDOW_WIDTH / 2;
    int x_lower_bound = engine.renderer.GetCameraPos().x - Globals::WINDOW_WIDTH / 2;
    
    int y_upper_bound = engine.renderer.GetCameraPos().y + Globals::WINDOW_HEIGHT / 2;
    int y_lower_bound = engine.renderer.GetCameraPos().y - Globals::WINDOW_HEIGHT / 2;

    int tilesRendered = 0;
    
    WorldToTilePos(&x_upper_bound, &y_upper_bound);
    WorldToTilePos(&x_lower_bound, &y_lower_bound);

    // + 1 to avoid not rendering in border (float to int type o sht)
    ++x_upper_bound;
    ++y_upper_bound;

    // Iterate only through visible tiles (from ~20M to ~8K)
    for (int x = x_lower_bound; x < x_upper_bound; ++x)
    {
        for (int y = y_lower_bound; y < y_upper_bound; ++y)
        {
            ++tilesRendered;
            switch (tilemap[y * TILEMAP_WIDTH + x].type)
            {
            case 1: // Ground
                engine.renderer.RenderTexture(tiles_texture, { 32.0f, 0.0f, 32.0f, 32.0f }, { tilemap[y * TILEMAP_WIDTH + x].pos.x, tilemap[y * TILEMAP_WIDTH + x].pos.y, 16.0f, 16.0f }, 1.0f);
                break;
            default: 
                --tilesRendered;
                break;
            }
        }
    }

    engine.renderer.RenderDebugText("Tiles rendered: " + std::to_string(tilesRendered), 700.0f, 5.0f);
}