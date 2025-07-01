#include "Entity.h"

void Entity::Update(const Engine& engine)
{
	for (IComponent* component : components)
	{
		component->Update(engine);
	}
}

void Entity::AddComponent(IComponent* newComponent)
{
	components.push_back(newComponent);
}