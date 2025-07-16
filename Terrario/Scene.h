#pragma once

#include "Entity.h"

#include <vector>

struct Entity;
struct Engine;
struct Game;

struct Scene
{
	bool Load();
	bool Unload();
	void Update(Engine& engine, Game& game);

	void AddEntity(Entity* new_entity);
	void RemoveEntity(Entity* entity);

	std::vector<Entity*> entities{};
	std::vector<Entity*> entities_to_add{};
	std::vector<Entity*> entities_to_remove{};

	Entity* player = nullptr;
};