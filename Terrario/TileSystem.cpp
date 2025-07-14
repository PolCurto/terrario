#include "TileSystem.h"

#include "Engine.h"
#include "Scene.h"

#include "Entity.h"
#include "RandomGen.h"
#include "TreeComponent.h"

#include "SDL3/SDL_rect.h"

void TileSystem::CreateTilesArray(Engine& engine, Scene& active_scene)
{
    DebugLog("Size of Tile: " + std::to_string(sizeof(Tile)));

    tilemap = new Tile[TILEMAP_SIZE];

    // Terrain pass
    for (int x = 0; x < TILEMAP_WIDTH; ++x)
    {
        for (int y = 0; y < TILEMAP_HEIGHT; ++y)
        {
            if (y - TILEMAP_HEIGHT / 2 > 0 && y - TILEMAP_HEIGHT / 2 <= 10)
            {
                tilemap[TILEMAP_WIDTH * y + x].type = TileType::Dirt;
            }
            else if (y - TILEMAP_HEIGHT / 2 > 10)
            {
                tilemap[TILEMAP_WIDTH * y + x].type = TileType::Rock;
            }
        }
    }

    std::vector<IntVector2> ores_pos;

    // Second pass
    int ores_count = 0;
    int trees = 0;
    for (int x = 0; x < TILEMAP_WIDTH; ++x)
    {
        for (int y = 0; y < TILEMAP_HEIGHT; ++y)
        {
            // Trees
            if (x > 0 && x < TILEMAP_WIDTH - 1 && y < TILEMAP_HEIGHT - 1 && tilemap[TILEMAP_WIDTH * y + x].type == TileType::Empty &&
                tilemap[TILEMAP_WIDTH * y + (x+1)].type == TileType::Empty && tilemap[TILEMAP_WIDTH * y + (x-1)].type == TileType::Empty &&
                tilemap[TILEMAP_WIDTH * (y+1) + x].type == TileType::Dirt && engine.random.RandomFloat() < 10.0f)
            {
                ++trees;
                tilemap[TILEMAP_WIDTH * y + x].type = TileType::Trunk;
                tilemap[TILEMAP_WIDTH * y + x].active = true;

                Entity* new_tree = new Entity();
                TreeComponent* tree_comp = new TreeComponent({ x, y });
                tree_comp->entity = new_tree;
                new_tree->AddComponent(tree_comp);
                tree_comp->max_growth = engine.random.RandomIntRange(5, 15);
                active_scene.AddEntity(new_tree);
            }

            // Ores
            if (y - TILEMAP_HEIGHT / 2 > 15 && tilemap[TILEMAP_WIDTH * y + (x + 1)].type == TileType::Rock && engine.random.RandomFloat() < 1.05f)
            {
                ++ores_count;
                tilemap[TILEMAP_WIDTH * y + x].type = TileType::Copper;
                ores_pos.push_back({x, y});
            }
            if (y - TILEMAP_HEIGHT / 2 > 25 && tilemap[TILEMAP_WIDTH * y + (x + 1)].type == TileType::Rock && engine.random.RandomFloat() < 1.05f)
            {
                ++ores_count;
                tilemap[TILEMAP_WIDTH * y + x].type = TileType::Silver;
                ores_pos.push_back({ x, y });
            }
            if (y - TILEMAP_HEIGHT / 2 > 35 && tilemap[TILEMAP_WIDTH * y + (x + 1)].type == TileType::Rock && engine.random.RandomFloat() < 1.05f)
            {
                ++ores_count;
                tilemap[TILEMAP_WIDTH * y + x].type = TileType::Gold;
                ores_pos.push_back({ x, y });
            }
        }
    }

    DebugLog("Ores generated: " + std::to_string(ores_count));

    // Ore propagation
    for (const IntVector2& pos : ores_pos)
    {
        int expansion = std::floor(engine.random.RandomIntRange(5, 30));
        TileType current_type = tilemap[TILEMAP_WIDTH * pos.y + pos.x].type;

        for (int i = 0; i < expansion; ++i)
        {
            IntVector2 current_pos = pos;

            while (true)
            {
                if (engine.random.RandomFloat() < 50.0f) ++current_pos.x;
                else ++current_pos.y;

                if (current_pos.x < 0 || current_pos.x >= TILEMAP_WIDTH || current_pos.y < 0 || current_pos.y >= TILEMAP_HEIGHT) break;

                if (tilemap[TILEMAP_WIDTH * current_pos.y + current_pos.x].type == TileType::Rock)
                {
                    tilemap[TILEMAP_WIDTH * current_pos.y + current_pos.x].type = current_type;
                    break;
                }
            }
        }
    }

    DebugLog("Ores generated: " + std::to_string(ores_count));
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
    //for (IntVector2 tile_pos : always_update_tiles)
    //{
    //   Tile& current_tile = tilemap[TILEMAP_WIDTH * tile_pos.y + tile_pos.x];
    //   if (!current_tile.active) continue;
    //
    //   switch (current_tile.type)
    //   {
    //   case TileType::Tree: // Update Trees
    //       current_tile.elapsed_time += engine.timer.delta_time / 1000.0f;
    //
    //       if (current_tile.elapsed_time > 5.0f)
    //       {
    //           current_tile.active = false;
    //           if (tile_pos.y - 1 > 0 && tilemap[TILEMAP_WIDTH * (tile_pos.y - 1) + tile_pos.x].type == TileType::Empty)
    //           {
    //               tilemap[TILEMAP_WIDTH * (tile_pos.y - 1) + tile_pos.x].type = TileType::Tree;
    //               tilemap[TILEMAP_WIDTH * (tile_pos.y - 1) + tile_pos.x].active = true;
    //               new_tiles.push_back({ tile_pos.x, tile_pos.y - 1 });
    //           }
    //       }
    //       break;
    //   }
    //}
    //
    //always_update_tiles.insert(always_update_tiles.end(), new_tiles.begin(), new_tiles.end());


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

    x_upper_bound = std::clamp(x_upper_bound, 0, TILEMAP_WIDTH - 1);
    x_lower_bound = std::clamp(x_lower_bound, 0, TILEMAP_WIDTH - 1);

    y_upper_bound = std::clamp(y_upper_bound, 0, TILEMAP_HEIGHT - 1);
    y_lower_bound = std::clamp(y_lower_bound, 0, TILEMAP_HEIGHT - 1);

    // TODO: Probably world_pos not needed, it can be calculated in place with two multiplications. When doing entities for trees, crops, etc, they will have the elapsed_time also.

    // Iterate only through visible tiles
    for (int x = x_lower_bound; x < x_upper_bound; ++x)
    {
        for (int y = y_lower_bound; y < y_upper_bound; ++y)
        {
            ++tilesRendered;
            const float world_x = static_cast<float>(x * TILE_SIZE - TILEMAP_WIDTH * (TILE_SIZE * 0.5f));
            const float world_y = static_cast<float>(y * TILE_SIZE - TILEMAP_HEIGHT * (TILE_SIZE * 0.5f));

            switch (tilemap[TILEMAP_WIDTH * y + x].type)
            {
            case TileType::Dirt: 
                if (y - 1 > 0 && tilemap[TILEMAP_WIDTH * (y - 1) + x].type != TileType::Dirt)
                    engine.renderer.RenderTexture(tiles_texture, { 64.0f, 0.0f, 32.0f, 32.0f }, { world_x, world_y, TILE_SIZE, TILE_SIZE }, 1.0f);
                else
                    engine.renderer.RenderTexture(tiles_texture, { 32.0f, 0.0f, 32.0f, 32.0f }, { world_x, world_y, TILE_SIZE, TILE_SIZE }, 1.0f);
                break;

            case TileType::Rock:
                engine.renderer.RenderTexture(tiles_texture, { 96.0f, 0.0f, 32.0f, 32.0f }, { world_x, world_y, TILE_SIZE, TILE_SIZE }, 1.0f);
                break;

                // Ores
            case TileType::Copper:
                engine.renderer.RenderTexture(tiles_texture, { 416.0f, 0.0f, 32.0f, 32.0f }, { world_x, world_y, TILE_SIZE, TILE_SIZE }, 1.0f);
                break;
            case TileType::Silver:
                engine.renderer.RenderTexture(tiles_texture, { 448.0f, 0.0f, 32.0f, 32.0f }, { world_x, world_y, TILE_SIZE, TILE_SIZE }, 1.0f);
                break;
            case TileType::Gold:
                engine.renderer.RenderTexture(tiles_texture, { 480.0f, 0.0f, 32.0f, 32.0f }, { world_x, world_y, TILE_SIZE, TILE_SIZE }, 1.0f);
                break;

            case TileType::Trunk:
                engine.renderer.RenderTexture(tiles_texture, { 352.0f, 0.0f, 32.0f, 32.0f }, { world_x, world_y, TILE_SIZE, TILE_SIZE }, 1.0f);
                break;
            case TileType::Leaves:
                engine.renderer.RenderTexture(tiles_texture, { 382.0f, 0.0f, 32.0f, 32.0f }, { world_x, world_y , TILE_SIZE, TILE_SIZE }, 1.0f);
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
            if (tilemap[TILEMAP_WIDTH * y + x].type != TileType::Empty &&
                tilemap[TILEMAP_WIDTH * y + x].type != TileType::Trunk &&
                tilemap[TILEMAP_WIDTH * y + x].type != TileType::Leaves)
            {
                return true;
            }
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

void TileSystem::PlaceTile(float x, float y, const Engine& engine, TileType type)
{
    int ix = static_cast<int>(x);
    int iy = static_cast<int>(y);
    ScreenToTilePos(&ix, &iy, engine);

    tilemap[TILEMAP_WIDTH * iy + ix].type = type;
}