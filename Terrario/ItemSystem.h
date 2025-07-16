#pragma once

#include <string>
#include <optional>
#include <functional>
#include <SDL3/SDL_rect.h>
#include <cstdint>

enum class TileType : uint8_t;
struct Game;
struct TileSystem;
struct IntVector2;

enum class ItemId
{
	Empty = 0,

	// Swords
	WoodenSword,

	// Pickaxes
	WoodenPickaxe,

	// Axes
	WoodenAxe,

	// Tiles
	DirtTile,
	WoodTile,
	RockTile,

	// Ores
	CopperOre,
	SilverOre,
	GoldenOre
};

struct Item
{
	Item() = default;
	Item(ItemId n_id, int n_amount) : id(n_id), amount(n_amount) {};

	ItemId id;
	int amount;
};

struct UsableComponent
{
	UsableComponent(std::function<void(Item& item)> func) : function(func) {}

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
	BreakComponent(int speed) : break_speed(speed) {}

	int break_speed;
};

struct PlaceableComponent
{
	PlaceableComponent(uint8_t tile) : tile_type(tile) {}

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
	void OnLeftClick(Item& item, Game& game, const IntVector2& mouse_pos);
	void OnRightClick(Item& item, TileSystem& tile_system, const IntVector2& mouse_pos);

	std::unordered_map<ItemId, ItemData> items_registry;
};

namespace ItemUtils
{
	ItemId TileToItemId(const TileType& tile);
	SDL_FRect ItemIdToTextureArea(const ItemId item);
}
