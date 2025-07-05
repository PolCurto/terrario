#pragma once

#include "TileSystem.h"

#include <vector>

struct Scene;
struct Engine;

struct Game
{
	Game(Engine& engine);
	~Game();

	void Update(Engine& engine);

	TileSystem tile_system{};
	std::vector<Scene*> scenes{};
	Scene* activeScene = nullptr;
};