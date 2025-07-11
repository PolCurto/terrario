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
            tilemap[TILEMAP_WIDTH * y + x].world_pos = { static_cast<float>(x * TILE_SIZE - TILEMAP_WIDTH * (TILE_SIZE * 0.5f)), static_cast<float>(y * TILE_SIZE - TILEMAP_HEIGHT * (TILE_SIZE * 0.5f)) };

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
    int x_upper_bound = static_cast<int>(engine.renderer.GetCameraPos().x + Globals::RENDER_TEXTURE_WIDTH / 2.0f);
    int x_lower_bound = static_cast<int>(engine.renderer.GetCameraPos().x - Globals::RENDER_TEXTURE_WIDTH / 2.0f);

    int y_upper_bound = static_cast<int>(engine.renderer.GetCameraPos().y + Globals::RENDER_TEXTURE_HEIGHT / 2.0f);
    int y_lower_bound = static_cast<int>(engine.renderer.GetCameraPos().y - Globals::RENDER_TEXTURE_HEIGHT / 2.0f);

    int tilesRendered = 0;
    
    WorldToTilePos(&x_upper_bound, &y_upper_bound);
    WorldToTilePos(&x_lower_bound, &y_lower_bound);

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
                    engine.renderer.RenderTexture(tiles_texture, { 64.0f, 0.0f, 32.0f, 32.0f }, { current_tile.world_pos.x, current_tile.world_pos.y, TILE_SIZE, TILE_SIZE }, 1.0f);
                else
                    engine.renderer.RenderTexture(tiles_texture, { 32.0f, 0.0f, 32.0f, 32.0f }, { current_tile.world_pos.x, current_tile.world_pos.y, TILE_SIZE, TILE_SIZE }, 1.0f);
                break;

            case TileType::Tree: // Tree
                engine.renderer.RenderTexture(tiles_texture, { 352.0f, 0.0f, 32.0f, 32.0f }, { current_tile.world_pos.x, current_tile.world_pos.y, TILE_SIZE, TILE_SIZE }, 1.0f);
                break;

            default: 
                --tilesRendered;
                break;
            }
        }
    }

    engine.renderer.RenderDebugText("Tiles rendered: " + std::to_string(tilesRendered), { 500.0f, 5.0f });
}

bool TileSystem::CheckForTiles(const Vector2& pos, const Vector2& size) const
{
    Vector2 tiles_pos = pos;
    WorldToTilePos(&tiles_pos.x, &tiles_pos.y);

    if (tiles_pos.x < 0 || tiles_pos.x >= TILEMAP_WIDTH || tiles_pos.y < 0 || tiles_pos.y >= TILEMAP_HEIGHT) return false;

    IntVector2 top_left = { 
        static_cast<int>(std::floorf(tiles_pos.x - size.x / TILE_SIZE * 0.5f)), 
        static_cast<int>(std::floorf(tiles_pos.y - size.y / TILE_SIZE * 0.5f))
    };

    IntVector2 bottom_right = { 
        static_cast<int>(std::ceilf(tiles_pos.x + size.x / TILE_SIZE * 0.5f)),
        static_cast<int>(std::ceilf(tiles_pos.y + size.y / TILE_SIZE * 0.5f))
    };


    for (int x = top_left.x; x < bottom_right.x; ++x)
    {
        for (int y = top_left.y; y < bottom_right.y; ++y)
        {
            if (tilemap[TILEMAP_WIDTH * y + x].type == TileType::Dirt) return true;
        }
    }

    return false;
}

void TileSystem::DestroyTile(float x, float y, const Engine& engine)
{
    int ix = static_cast<int>(x);
    int iy = static_cast<int>(y);
    ScreenToTilePos(&ix, &iy, engine);

    tilemap[TILEMAP_WIDTH * iy + ix].type = TileType::Empty;
}

void TileSystem::PlaceTile(float x, float y, const Engine& engine)
{
    int ix = static_cast<int>(x);
    int iy = static_cast<int>(y);
    ScreenToTilePos(&ix, &iy, engine);

    tilemap[TILEMAP_WIDTH * iy + ix].type = TileType::Dirt;
}