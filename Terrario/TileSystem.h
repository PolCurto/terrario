#pragma once

#include "Vector2.h"
#include "IntVector2.h"
#include "Globals.h"
#include "Window.h"
#include "Engine.h"

#include <random>
#include <vector>

struct SDL_Texture;

constexpr int TILEMAP_WIDTH = 8400;
constexpr int TILEMAP_HEIGHT = 2400;
constexpr int TILEMAP_SIZE = TILEMAP_WIDTH * TILEMAP_HEIGHT;
constexpr int TILE_SIZE = 16;

enum class TileType : uint8_t
{
	Empty = 0,
	Dirt,
	Tree,
	Rock,
	Copper,
	Silver,
	Gold,
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

	bool CheckForTiles(const Vector2& pos, const Vector2& size) const;
	void DestroyTile(float x, float y, const Engine& engine);
	void PlaceTile(float x, float y, const Engine& engine);

	// This assumes x and y are 0,0 in the center of the srceen
	inline void ScreenToTilePos(int* x, int* y, const Engine& engine) const
	{
		float x_ratio = static_cast<float>(Globals::RENDER_TEXTURE_WIDTH) / static_cast<float>(engine.window.width);
		float y_ratio = static_cast<float>(Globals::RENDER_TEXTURE_HEIGHT) / static_cast<float>(engine.window.height);

		float new_x = *x * x_ratio;
		float new_y = *y * y_ratio;

		new_x += engine.renderer.GetCameraPos().x;
		new_y += engine.renderer.GetCameraPos().y;

		new_x = (new_x + TILEMAP_WIDTH * (TILE_SIZE * 0.5f)) / TILE_SIZE;
		new_y = (new_y + TILEMAP_HEIGHT * (TILE_SIZE * 0.5f)) / TILE_SIZE;

		*x = static_cast<int>(std::floor(new_x));
		*y = static_cast<int>(std::floor(new_y));
	}

	inline void WorldToTilePos(int* x, int* y) const
	{
		*x = static_cast<int>((*x + TILEMAP_WIDTH * (TILE_SIZE * 0.5f)) / TILE_SIZE);
		*y = static_cast<int>((*y + TILEMAP_HEIGHT * (TILE_SIZE * 0.5f)) / TILE_SIZE);
	}
	inline void WorldToTilePos(float* x, float* y) const
	{
		*x = (*x + TILEMAP_WIDTH * (TILE_SIZE * 0.5f)) / TILE_SIZE;
		*y = (*y + TILEMAP_HEIGHT * (TILE_SIZE * 0.5f)) / TILE_SIZE;
	}

	inline bool IsTile(int x, int y) const
	{
		// Check bounds
		if (x < 0 || x >= TILEMAP_WIDTH || y < 0 || y >= TILEMAP_HEIGHT) return false;

		if (tilemap[TILEMAP_WIDTH * y + x].type != TileType::Empty) return true;
		else return false;
	}
	
	Tile* tilemap = nullptr;
	SDL_Texture* tiles_texture = nullptr;

	std::vector<IntVector2> always_update_tiles;

	// TODO: To avoid looping through all tiles, more arrays could be created, as well as chunks
	// Render -> Only visible tiles
	// Update -> Only tiles more or less close to the player, but not neccesarily visible
	// There are some tiles, like trees, which shuld be always updated. For this I could have an array of always_update_tiles and go through it, because not a lot should be there

	// Trees prob should be entities, which have its tiles as params, but things like elapsed time goes into the entity to reduce tile size. Also with things like crops, furniture, etc.

	std::mt19937 rng;
	std::uniform_real_distribution<float> dist;
};