#pragma once

#include "IComponent.h"
#include "ItemSystem.h"

struct Entity;

struct ItemComponent : IComponent
{
	bool Init() override { return true; }
	void Update(Engine& engine, Game& game) override;
	bool Close() override { return true; }

	Entity* entity = nullptr;
	ItemId item_id = ItemId::DirtTile;
};