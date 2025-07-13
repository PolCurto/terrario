#include "Scene.h"

#include "Engine.h"
#include "Game.h"

bool Scene::Load()
{
	return true;
}

bool Scene::Unload()
{
	return true;
}

void Scene::Update(Engine& engine, Game& game)
{
	for (Entity* ent : entities)
	{
		ent->Update(engine, game);
	}
}

void Scene::AddEntity(Entity* new_entity)
{
	entities.push_back(new_entity);
}