#pragma once

struct Vector2;
struct Engine;
struct SDL_Texture;

constexpr int worldWidth = 8400;
constexpr int worldHeight = 2400;
constexpr int worldSize = worldWidth * worldHeight;

struct Tilemap
{
	int* type = nullptr;
	Vector2* pos = nullptr;
};

struct TileSystem
{
	void CreateTilesArray();
	void DeleteTilesArray();
	void Update(Engine& engine);
	
	Tilemap tilemap{};
	SDL_Texture* tiles_texture = nullptr;
};