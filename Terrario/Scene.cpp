#include "Scene.h"

#include "Engine.h"

bool Scene::Load()
{
	return true;
}

bool Scene::Unload()
{
	return true;
}

void Scene::Update(Engine& engine)
{
	for (Entity* ent : entities)
	{
		ent->Update(engine);
	}
}