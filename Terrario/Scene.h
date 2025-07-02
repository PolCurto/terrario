#pragma once

#include "Entity.h"

#include <vector>

struct Engine;

struct Scene
{
	bool Load();
	bool Unload();
	void Update(Engine& engine);

	std::vector<Entity*> entities;
};