#include "ItemSystem.h"
#include "TileSystem.h"

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
		item_data.usable_component = {
			[](Item& item)
			{
				item.amount -= 2;
			}
		};
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
		items_registry[ItemId::DirtTile] = item_data;
	}

	// Rock
	{
		ItemData item_data;
		item_data.name = "Rock";
		item_data.placeable_component = static_cast<uint8_t>(TileType::Rock);
		items_registry[ItemId::DirtTile] = item_data;
	}
}