#pragma once

#include <string>
#include <optional>
#include <functional>

struct TileSystem;
struct IntVector2;

enum class ItemId
{
	WoodenSword = 0,
	WoodenPickaxe,
	WoodenAxe,
	DirtTile,
	WoodTile,
	RockTile,

	Empty
};

struct Item
{
	ItemId id;
	int amount;
};

struct UsableComponent
{
	UsableComponent(std::function<void(Item& item)> func) : function(func) {};
	std::function<void(Item& item)> function;
};

// Component for damaging creatures
struct AttackComponent
{
	int damage;
};

// Component for breaking tiles
struct BreakComponent
{
	int break_speed;
};

struct PlaceableComponent
{
	PlaceableComponent(uint8_t tile) : tile_type(tile) {};
	uint8_t tile_type;
};

struct ItemData
{
	std::string name;
	std::optional<UsableComponent> usable_component;
	std::optional<AttackComponent> attack_component;
	std::optional<BreakComponent> break_component;
	std::optional<PlaceableComponent> placeable_component;
};

struct ItemSystem
{
	void InitItemRegistry();
	void OnLeftClick(Item& item, TileSystem& tile_system, const IntVector2& mouse_pos);
	void OnRightClick(Item& item, TileSystem& tile_system, const IntVector2& mouse_pos);

	std::unordered_map<ItemId, ItemData> items_registry;
};