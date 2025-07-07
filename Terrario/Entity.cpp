#include "Entity.h"

#include "Game.h"

void Entity::Update(Engine& engine, Game& game)
{
	for (IComponent* component : components)
	{
		component->Update(engine, game);
	}
}

void Entity::AddComponent(IComponent* newComponent)
{
	components.push_back(newComponent);
}