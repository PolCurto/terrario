#pragma once

#include "Vector2.h"

struct Engine;
struct SDL_Texture;

constexpr int TILEMAP_WIDTH = 8400;
constexpr int TILEMAP_HEIGHT = 2400;
constexpr int TILEMAP_SIZE = TILEMAP_WIDTH * TILEMAP_HEIGHT;

struct Tile
{
	int type = 0;
	Vector2 pos{};
};

struct TileSystem
{
	void CreateTilesArray();
	void DeleteTilesArray();
	void Update(Engine& engine);

	inline void WorldToTilePos(int* x, int* y) const
	{
		*x = (*x + TILEMAP_WIDTH * 8) / 16;
		*y = (*y + TILEMAP_HEIGHT * 8) / 16;
	}
	
	Tile* tilemap = nullptr;
	SDL_Texture* tiles_texture = nullptr;

	// TODO: To avoid looping through all tiles, more arrays could be created, as well as chunks
	// Render -> Only visible tiles
	// Update -> Only tiles more or less close to the player, but not neccesarily visible
	// There are some tiles, like trees, which shuld be always updated. For this I could have an array of always_update_tiles and go through it, because not a not should be there
};