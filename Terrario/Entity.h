#pragma once

#include "IComponent.h"
#include "Vector2.h"

#include <vector>
#include <string>
#include <unordered_map>
#include <typeindex>

struct Engine;
struct Game;

struct Entity
{
	Entity() = default;
	Entity(const std::string& name, Entity* parent, const Vector2& position, const Vector2& size) 
		: name(name), position(position), size(size), parent(parent) {};

	~Entity();

	void Update(Engine& engine, Game& game);

	void AddChild(Entity* new_child) { children.push_back(new_child); }
	void AddComponent(IComponent* new_component);
	
	template <typename T>
	T* GetComponent() const
	{
		auto it = component_map.find(typeid(T));
		if (it != component_map.end()) return static_cast<T*>(it->second);
		else return nullptr;
	}

	std::string name = "";
	Vector2 position{};
	Vector2 size{};

	Entity* parent = nullptr;
	std::vector<Entity*> children;

	std::vector<IComponent*> components;
	std::unordered_map<std::type_index, IComponent*> component_map;
};
