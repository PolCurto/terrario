#include "Scene.h"

#include "Engine.h"
#include "Game.h"

bool Scene::Load()
{
	return true;
}

bool Scene::Unload()
{
	for (Entity* ent : entities)
	{
		delete ent;
	}
	entities.clear();
	return true;
}

void Scene::Update(Engine& engine, Game& game)
{
	// Add / Remove new entities outside the Update loop
	for (Entity* ent : entities_to_add)
	{
		entities.push_back(ent);
	}
	for (Entity* ent : entities_to_remove)
	{
		entities.erase(std::remove(entities.begin(), entities.end(), ent), entities.end());
		delete ent;
	}
	entities_to_add.clear();
	entities_to_remove.clear();

	for (Entity* ent : entities)
	{
		ent->Update(engine, game);
	}
}

void Scene::AddEntity(Entity* new_entity)
{
	entities_to_add.push_back(new_entity);
}


void Scene::RemoveEntity(Entity* entity)
{
	entities_to_remove.push_back(entity);
}