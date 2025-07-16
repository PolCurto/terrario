#include "TreeComponent.h"

#include "Engine.h"
#include "Game.h"
#include "TileSystem.h"

TreeComponent::TreeComponent(const IntVector2& first_tile)
{
	tiles.push_back(first_tile);
}

void TreeComponent::Update(Engine& engine, Game& game)
{
    if (!is_growing) return;
    time_elapsed += (engine.timer.delta_time / 1000.0f);

    if (time_elapsed > growth_ratio)
    {
        // Reset timers
        growth_ratio = engine.random.RandomFloatRange(5.0f, 30.0f);
        time_elapsed = 0.0f;

        const IntVector2 curr_pos = tiles.back();
        if (curr_pos.y - 1 > 0 && game.tile_system.IsTile(curr_pos.x, tiles.back().y))
        {
            // Grow
            game.tile_system.SetTile(curr_pos.x, curr_pos.y - 1, TileType::Trunk);
            tiles.push_back({ curr_pos.x, curr_pos.y - 1 });
            ++curr_growth;
            if (curr_growth >= max_growth)
            {
                // Spawn leaves
                is_growing = false;

                // TODO: More tree types in different biomes, the radius can be changed for that purpose. Also different passes for pines
                int canopy_radius = engine.random.RandomIntRange(2, 4);
                IntVector2 top = curr_pos - IntVector2(0, canopy_radius);

                for (int dy = -canopy_radius; dy <= canopy_radius; ++dy) 
                {
                    const float fdy = static_cast<float>(dy);
                    for (int dx = -canopy_radius; dx <= canopy_radius; ++dx) 
                    {
                        const float fdx = static_cast<float>(dx);
                        const float dist = std::sqrtf(dx * dx + fdy * fdy);
                        const float variation = engine.random.RandomFloatRange(-0.5f, 0.5f);

                        if (dist <= canopy_radius + variation) 
                        {
                            const int x = top.x + dx;
                            const int y = top.y + dy;

                            if (!game.tile_system.IsTile(x, y) && x >= 0 && x < TILEMAP_WIDTH && y >= 0 && y < TILEMAP_HEIGHT) 
                            {
                                game.tile_system.SetTile(x, y, TileType::Leaves);
                            }
                        }
                    }
                }
            }
        }
        else
        {
            is_growing = false;
        }
    }
    
}