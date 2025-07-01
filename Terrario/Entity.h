#pragma once

#include "IComponent.h"
#include "Vector2.h"

#include <vector>

struct Engine;

struct Entity
{
	void Update(const Engine& Engine);

	void AddComponent(IComponent* newComponent);


	Vector2 position;
	std::vector<IComponent*> components;
};
