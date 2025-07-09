#pragma once

#include "IComponent.h"
#include "Vector2.h"

#include <vector>
#include <string>

struct Engine;
struct Game;

struct Entity
{
	Entity() = default;
	Entity(const std::string& name, Entity* parent, const Vector2& position, const Vector2& size) 
		: name(name), position(position), size(size), parent(parent) {};

	void Update(Engine& engine, Game& game);

	void AddChild(Entity* newChild) { children.push_back(newChild); }
	void AddComponent(IComponent* newComponent);


	std::string name = "";
	Vector2 position{};
	Vector2 size{};

	Entity* parent = nullptr;
	std::vector<Entity*> children;
	std::vector<IComponent*> components;
};
