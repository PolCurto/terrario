#pragma once

#include "IComponent.h"
#include "Entity.h"
#include "ItemSystem.h"

#include <array>

struct Game;

struct CharacterController : IComponent
{
	bool Init() override;
	void Update(Engine&	engine, Game& game) override;
	bool Close() override;

	void SetEntity(Entity* parent) { entity = parent; }
	void AddItem(ItemId item_id);

	Entity* entity = nullptr;

	float current_speed = 150.0f;
	Vector2 direction{};
	Vector2 speed{};

	bool debug_mode = false;

	int inventory_index = 0;
	std::array<Item, 5> inventory;
};