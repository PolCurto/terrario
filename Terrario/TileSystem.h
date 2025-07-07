#pragma once

#include "Vector2.h"
#include "IntVector2.h"
#include "Globals.h"
#include "Window.h"

#include <random>
#include <vector>

struct Engine;
struct SDL_Texture;

constexpr int TILEMAP_WIDTH = 8400;
constexpr int TILEMAP_HEIGHT = 2400;
constexpr int TILEMAP_SIZE = TILEMAP_WIDTH * TILEMAP_HEIGHT;

enum class TileType : uint8_t
{
	Empty = 0,
	Dirt,
	Tree
};

// TO CONSIDER: Maybe another struct only for active tiles, which has the elapsed_time?
struct Tile
{
	Vector2 world_pos{};
	float elapsed_time = 0;
	bool active = false;
	TileType type = TileType::Empty;
};

struct TileSystem
{
	TileSystem();

	void CreateTilesArray();
	void DeleteTilesArray();
	void Update(Engine& engine);

	inline void WorldToTilePos(int* x, int* y, const Window& window) const
	{
		float x_ratio = static_cast<float>(Globals::RENDER_TEXTURE_WIDTH) / static_cast<float>(window.width);
		float y_ratio = static_cast<float>(Globals::RENDER_TEXTURE_HEIGHT) / static_cast<float>(window.height);

		float new_x = *x;
		float new_y = *y;

		new_x = ((new_x*x_ratio) + TILEMAP_WIDTH * 8) / 16;
		new_y = ((new_y*y_ratio) + TILEMAP_HEIGHT * 8) / 16;

		*x = std::floor(new_x);
		*y = std::floor(new_y);
	}

	void DestroyTile(int x, int y, const Window& window);
	void PlaceTile(int x, int y, const Window& window);
	
	Tile* tilemap = nullptr;
	SDL_Texture* tiles_texture = nullptr;

	std::vector<IntVector2> always_update_tiles;

	// TODO: To avoid looping through all tiles, more arrays could be created, as well as chunks
	// Render -> Only visible tiles
	// Update -> Only tiles more or less close to the player, but not neccesarily visible
	// There are some tiles, like trees, which shuld be always updated. For this I could have an array of always_update_tiles and go through it, because not a not should be there

	std::mt19937 rng;
	std::uniform_int_distribution<int> int_distribution;
};