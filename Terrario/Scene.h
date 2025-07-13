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

	void AddEntity(Entity* new_entity);

	std::vector<Entity*> entities;
};