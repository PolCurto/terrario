#include "TileSystem.h"

#include "Engine.h"

#include "SDL3/SDL_rect.h"

TileSystem::TileSystem()
{
    rng = std::mt19937(std::random_device{}());
    int_distribution = std::uniform_int_distribution<int>(1, 100);
}

void TileSystem::CreateTilesArray()
{
    DebugLog("Size of Tile: " + std::to_string(sizeof(Tile)));

    tilemap = new Tile[TILEMAP_SIZE];

    // Terrain pass
    for (int x = 0; x < TILEMAP_WIDTH; ++x)
    {
        for (int y = 0; y < TILEMAP_HEIGHT; ++y)
        {
            tilemap[TILEMAP_WIDTH * y + x].world_pos = { static_cast<float>(x * 16 - TILEMAP_WIDTH * 8), static_cast<float>(y * 16 - TILEMAP_HEIGHT * 8) };

            if (y - TILEMAP_HEIGHT / 2 > 0)
            {
                tilemap[TILEMAP_WIDTH * y + x].type = TileType::Dirt;
            }
        }
    }

    // Trees pass
    int trees = 0;
    for (int x = 0; x < TILEMAP_WIDTH; ++x)
    {
        for (int y = 0; y < TILEMAP_HEIGHT; ++y)
        {
            if (x > 0 && x < TILEMAP_WIDTH - 1 && y < TILEMAP_HEIGHT - 1 && tilemap[TILEMAP_WIDTH * y + x].type == TileType::Empty &&
                tilemap[TILEMAP_WIDTH * y + (x+1)].type == TileType::Empty && tilemap[TILEMAP_WIDTH * y + (x-1)].type == TileType::Empty &&
                tilemap[TILEMAP_WIDTH * (y+1) + x].type == TileType::Dirt && int_distribution(rng) < 10)
            {
                ++trees;
                tilemap[TILEMAP_WIDTH * y + x].type = TileType::Tree;
                tilemap[TILEMAP_WIDTH * y + x].active = true;
                always_update_tiles.push_back({ x, y });
            }
        }
    }

    DebugLog("Trees generated: " + std::to_string(trees));
}

void TileSystem::DeleteTilesArray()
{
    delete[] tilemap;
}

void TileSystem::Update(Engine& engine)
{
    std::vector<IntVector2> new_tiles;

    // Tiles update
    for (IntVector2 tile_pos : always_update_tiles)
    {
       Tile& current_tile = tilemap[TILEMAP_WIDTH * tile_pos.y + tile_pos.x];
       if (!current_tile.active) continue;

       switch (current_tile.type)
       {
       case TileType::Tree: // Update Trees
           current_tile.elapsed_time += engine.timer.delta_time / 1000.0f;

           if (current_tile.elapsed_time > 5.0f)
           {
               current_tile.active = false;
               if (tile_pos.y - 1 > 0 && tilemap[TILEMAP_WIDTH * (tile_pos.y - 1) + tile_pos.x].type == TileType::Empty)
               {
                   tilemap[TILEMAP_WIDTH * (tile_pos.y - 1) + tile_pos.x].type = TileType::Tree;
                   tilemap[TILEMAP_WIDTH * (tile_pos.y - 1) + tile_pos.x].active = true;
                   new_tiles.push_back({ tile_pos.x, tile_pos.y - 1 });
               }
           }
           break;
       }
    }

    always_update_tiles.insert(always_update_tiles.end(), new_tiles.begin(), new_tiles.end());


    // Tiles render
    int x_upper_bound = engine.renderer.GetCameraPos().x + Globals::RENDER_TEXTURE_WIDTH / 2;
    int x_lower_bound = engine.renderer.GetCameraPos().x - Globals::RENDER_TEXTURE_WIDTH / 2;

    int y_upper_bound = engine.renderer.GetCameraPos().y + Globals::RENDER_TEXTURE_HEIGHT / 2;
    int y_lower_bound = engine.renderer.GetCameraPos().y - Globals::RENDER_TEXTURE_HEIGHT / 2;

    int tilesRendered = 0;
    
    x_upper_bound = (x_upper_bound + TILEMAP_WIDTH * 8) / 16;
    x_lower_bound = (x_lower_bound + TILEMAP_WIDTH * 8) / 16;

    y_upper_bound = (y_upper_bound + TILEMAP_HEIGHT * 8) / 16;
    y_lower_bound = (y_lower_bound + TILEMAP_HEIGHT * 8) / 16;

    // + 1 to avoid not rendering in border (float to int type o sht)
    ++x_upper_bound;
    ++y_upper_bound;

    // Iterate only through visible tiles
    for (int x = x_lower_bound; x < x_upper_bound; ++x)
    {
        for (int y = y_lower_bound; y < y_upper_bound; ++y)
        {
            ++tilesRendered;
            const Tile& current_tile = tilemap[TILEMAP_WIDTH * y + x];
            switch (current_tile.type)
            {
            case TileType::Dirt: // Dirt
                if (y - 1 > 0 && tilemap[TILEMAP_WIDTH * (y - 1) + x].type != TileType::Dirt)
                    engine.renderer.RenderTexture(tiles_texture, { 64.0f, 0.0f, 32.0f, 32.0f }, { current_tile.world_pos.x, current_tile.world_pos.y, 16.0f, 16.0f }, 1.0f);
                else
                    engine.renderer.RenderTexture(tiles_texture, { 32.0f, 0.0f, 32.0f, 32.0f }, { current_tile.world_pos.x, current_tile.world_pos.y, 16.0f, 16.0f }, 1.0f);
                break;

            case TileType::Tree: // Tree
                engine.renderer.RenderTexture(tiles_texture, { 352.0f, 0.0f, 32.0f, 32.0f }, { current_tile.world_pos.x, current_tile.world_pos.y, 16.0f, 16.0f }, 1.0f);
                break;

            default: 
                --tilesRendered;
                break;
            }
        }
    }

    engine.renderer.RenderDebugText("Tiles rendered: " + std::to_string(tilesRendered), 700.0f, 5.0f);
}

void TileSystem::DestroyTile(int x, int y, const Window& window)
{
    WorldToTilePos(&x, &y, window);

    tilemap[TILEMAP_WIDTH * y + x].type = TileType::Empty;
}

void TileSystem::PlaceTile(int x, int y, const Window& window)
{
    WorldToTilePos(&x, &y, window);

    tilemap[TILEMAP_WIDTH * y + x].type = TileType::Dirt;
}