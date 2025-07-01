#pragma once

#include "IComponent.h"

#include <vector>

struct Engine;

struct Entity
{
	void Update(const Engine& Engine);

	void AddComponent(IComponent* newComponent);

	std::vector<IComponent*> components;
};
