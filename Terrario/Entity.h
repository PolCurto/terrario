#pragma once

#include "IComponent.h"
#include "Vector2.h"

#include <vector>
#include <string>

struct Engine;

struct Entity
{
	void Update(Engine& engine);

	void AddChild(Entity* newChild) { children.push_back(newChild); }
	void AddComponent(IComponent* newComponent);


	std::string name = "";
	Vector2 position;

	Entity* parent;
	std::vector<Entity*> children;
	std::vector<IComponent*> components;
};
