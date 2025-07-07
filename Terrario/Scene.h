#pragma once

#include "Entity.h"

#include <vector>

struct Engine;
struct Game;

struct Scene
{
	bool Load();
	bool Unload();
	void Update(Engine& engine, Game& game);

	std::vector<Entity*> entities;
};