#include "ItemSystem.h"

#include "Game.h"
#include "IntVector2.h"

void ItemSystem::InitItemRegistry()
{
	// TODO: Load items from an external file


	/////////////// SWORDS ///////////////
	// Wood 
	{
		ItemData item_data;
		item_data.name = "Wooden Sword";
		item_data.usable_component = {
			[](Item& item)
			{
				item.amount -= 1;
			}
		};
		items_registry[ItemId::WoodenSword] = item_data;
	}

	// Stone
	// etc.


	/////////////// PICKAXES ///////////////
	// Wood
	{
		ItemData item_data;
		item_data.name = "Wooden Pickaxe";
		item_data.break_component = 1;
		items_registry[ItemId::WoodenPickaxe] = item_data;
	}

	// Stone
	// etc.


	/////////////// AXES ///////////////
	// Wood
	{
		ItemData item_data;
		item_data.name = "Wooden Pickaxe";
		item_data.usable_component = {
			[](Item& item)
			{
				item.amount -= 2;
			}
		};
		items_registry[ItemId::WoodenAxe] = item_data;
	}

	
	/////////////////////// TILES /////////////////////
	// Dirt
	{
		ItemData item_data;
		item_data.name = "Dirt";
		item_data.placeable_component = static_cast<uint8_t>(TileType::Dirt);
		items_registry[ItemId::DirtTile] = item_data;
	}

	// Wood
	{
		ItemData item_data;
		item_data.name = "Wood";
		item_data.placeable_component = static_cast<uint8_t>(TileType::Trunk);
		items_registry[ItemId::WoodTile] = item_data;
	}

	// Rock
	{
		ItemData item_data;
		item_data.name = "Rock";
		item_data.placeable_component = static_cast<uint8_t>(TileType::Rock);
		items_registry[ItemId::RockTile] = item_data;
	}
}

void ItemSystem::OnLeftClick(Item& item, Game& game, const IntVector2& mouse_pos)
{
	ItemData& current_item = items_registry[item.id];

	if (current_item.break_component.has_value())
	{
		// Destroy tiles

		// TODO: It should be repeatedly damaged until it breaks
		game.tile_system.DestroyTile(mouse_pos.x, mouse_pos.y, *game.activeScene);
	}
	if (current_item.attack_component.has_value())
	{
		// Attack
	}
}

void ItemSystem::OnRightClick(Item& item, TileSystem& tile_system, const IntVector2& mouse_pos)
{
	ItemData& current_item = items_registry[item.id];

	if (current_item.usable_component.has_value())
	{
		current_item.usable_component.value().function(item);
	}
	if (current_item.placeable_component.has_value())
	{
		tile_system.PlaceTile(mouse_pos.x, mouse_pos.y, static_cast<TileType>(current_item.placeable_component.value().tile_type));
		item.amount -= 1;
	}
}