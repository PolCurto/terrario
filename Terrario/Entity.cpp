#include "Entity.h"

#include "Game.h"

Entity::~Entity()
{
	for (IComponent* comp : components)
	{
		delete comp;
	}
}

void Entity::Update(Engine& engine, Game& game)
{
	for (IComponent* component : components)
	{
		component->Update(engine, game);
	}
}

void Entity::AddComponent(IComponent* new_component)
{
	components.push_back(new_component);
	component_map[typeid(*new_component)] = new_component;
}