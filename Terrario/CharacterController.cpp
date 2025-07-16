#include "CharacterController.h"

#include "Engine.h"
#include "Globals.h"
#include "Game.h"
#include "Raycast.h"

#include <SDL3/SDL_scancode.h>
#include <SDL3/SDL_Render.h>
#include <iostream>

constexpr float DEFUALT_SPEED = 150.0f;
constexpr float GRAVITY = 1500.0f;

bool CharacterController::Init()
{
	current_speed = DEFUALT_SPEED;

	// ITEMS TESTING
	Item dirt_tile(ItemId::DirtTile, 5);
	inventory[0] = dirt_tile;

	Item pickaxe(ItemId::WoodenPickaxe, 1);
	inventory[1] = pickaxe;

	return true;
}

void CharacterController::Update(Engine& engine, Game& game)
{
	Vector2 desired_position{};
	speed.x = 0;

	bool lmb = false;
	bool rmb = false;

	// Get inputs
	if (engine.inputs.keyboard[SDL_SCANCODE_LSHIFT] == KeyState::Down)
	{
		current_speed = DEFUALT_SPEED * 10;
	}
	else if (engine.inputs.keyboard[SDL_SCANCODE_LSHIFT] == KeyState::Up)
	{
		current_speed = DEFUALT_SPEED;
	}

	if (engine.inputs.keyboard[SDL_SCANCODE_A] == KeyState::Hold)
	{
		speed.x -= current_speed;
	}
	if (engine.inputs.keyboard[SDL_SCANCODE_D] == KeyState::Hold)
	{
		speed.x += current_speed;
	}

	if (engine.inputs.mouse_buttons[0] == KeyState::Hold)
	{
		lmb = true;
	}
	if (engine.inputs.mouse_buttons[2] == KeyState::Down)
	{
		rmb = true;
	}

	if (engine.inputs.keyboard[SDL_SCANCODE_SPACE] == KeyState::Down)
	{
		speed.y = -500.0f;
	}

	if (engine.inputs.keyboard[SDL_SCANCODE_1] == KeyState::Down) inventory_index = 0;
	if (engine.inputs.keyboard[SDL_SCANCODE_2] == KeyState::Down) inventory_index = 1;
	if (engine.inputs.keyboard[SDL_SCANCODE_3] == KeyState::Down) inventory_index = 2;
	if (engine.inputs.keyboard[SDL_SCANCODE_4] == KeyState::Down) inventory_index = 3;
	if (engine.inputs.keyboard[SDL_SCANCODE_5] == KeyState::Down) inventory_index = 4;

	if (engine.inputs.keyboard[SDL_SCANCODE_F1] == KeyState::Down)
	{
		debug_mode = !debug_mode;
	}

	// Check collisions
	desired_position.x = entity->position.x + speed.x * (engine.timer.delta_time / 1000.0f);
	bool collision = game.tile_system.CheckForTiles({desired_position.x, entity->position.y}, entity->size);
	if (!collision) entity->position.x = desired_position.x;

	desired_position.y = entity->position.y + speed.y * (engine.timer.delta_time / 1000.0f);
	collision = game.tile_system.CheckForTiles({ entity->position.x, desired_position.y}, entity->size);
	if (!collision) entity->position.y = desired_position.y;

	// Check grounded
	const Vector2 ray_origin = entity->position + Vector2(0.0f, entity->size.y / 2.0f);
	const Vector2 ray_end = ray_origin + Vector2(0.0f, 1.0f);
	bool is_grounded = (
			Raycast::ThrowTilesRay(ray_origin, ray_end, game.tile_system) ||
			Raycast::ThrowTilesRay(ray_origin + Vector2(entity->size.x / 2.0f, 0.0f), ray_end + Vector2(entity->size.x / 2.0f, 0.0f), game.tile_system) ||
			Raycast::ThrowTilesRay(ray_origin - Vector2(entity->size.x / 2.0f, 0.0f), ray_end - Vector2(entity->size.x / 2.0f, 0.0f), game.tile_system)
		);

	if (debug_mode)
	{
		engine.renderer.RenderRect({ entity->position.x - entity->size.x / 2, entity->position.y - entity->size.y / 2, entity->size.x, entity->size.y }, 0, 255, 0, 255, 1.0f, false);
		uint8_t r = is_grounded ? 255 : 0;
		uint8_t g = is_grounded ? 0 : 255;
		engine.renderer.RenderLine(ray_origin, ray_end, r, g, 0, 255);
		engine.renderer.RenderLine(ray_origin + Vector2(entity->size.x / 2.0f, 0.0f), ray_end + Vector2(entity->size.x / 2.0f, 0.0f), r, g, 0, 255);
		engine.renderer.RenderLine(ray_origin - Vector2(entity->size.x / 2.0f, 0.0f), ray_end - Vector2(entity->size.x / 2.0f, 0.0f), r, g, 0, 255);

		engine.renderer.RenderDebugText("Pos: " + std::to_string(entity->position.x) + " " + std::to_string(entity->position.y), entity->position - engine.renderer.GetCameraPos() + 
		Vector2(Globals::RENDER_TEXTURE_WIDTH / 2.0f, Globals::RENDER_TEXTURE_HEIGHT / 2.0f) - Vector2(100.0f, 50.0f));

		engine.renderer.RenderDebugText("Inventory index: " + std::to_string(inventory_index + 1), {1700.0f, 100.0f});
		engine.renderer.RenderDebugText("1. " + game.item_system.items_registry[inventory[0].id].name + " - " + std::to_string(inventory[0].amount), { 1700.0f, 120.0f});
		engine.renderer.RenderDebugText("2. " + game.item_system.items_registry[inventory[1].id].name + " - " + std::to_string(inventory[1].amount), { 1700.0f, 140.0f });
		engine.renderer.RenderDebugText("3. " + game.item_system.items_registry[inventory[2].id].name + " - " + std::to_string(inventory[2].amount), { 1700.0f, 160.0f });
		engine.renderer.RenderDebugText("4. " + game.item_system.items_registry[inventory[3].id].name + " - " + std::to_string(inventory[3].amount), { 1700.0f, 180.0f });
		engine.renderer.RenderDebugText("5. " + game.item_system.items_registry[inventory[4].id].name + " - " + std::to_string(inventory[4].amount), { 1700.0f, 200.0f });
	}

	if (!is_grounded) speed.y += GRAVITY * (engine.timer.delta_time / 1000.0f);

	if (lmb || rmb)
	{
		IntVector2 mouse;
		mouse.x = static_cast<int>(engine.inputs.mouse_pos.x - engine.window.width / 2.0f);
		mouse.y = static_cast<int>(engine.inputs.mouse_pos.y - engine.window.height / 2.0f);

		TileUtils::ScreenToTilePos(mouse.x, mouse.y, engine);

		// TODO: Other logic will take place on click even if no object, and prioritized, like opening a door or talking to npcs

		if (inventory[inventory_index].id == ItemId::Empty) return;

		if (lmb) game.item_system.OnLeftClick(inventory[inventory_index], game, mouse);
		else game.item_system.OnRightClick(inventory[inventory_index], game.tile_system, mouse);

		if (inventory[inventory_index].amount == 0) inventory[inventory_index].id = ItemId::Empty;
	}
}

bool CharacterController::Close()
{
	return true;
}

void CharacterController::AddItem(ItemId item_id)
{
	// TODO: Search for if item already exist, and add it

	int empty_index = -1;

	for (int i = 0; i < inventory.max_size(); ++i)
	{
		if (inventory[i].id == ItemId::Empty) empty_index = i;
		else if (inventory[i].id == item_id)
		{
			++inventory[i].amount;
			return;
		}
	}

	if (empty_index >= 0) inventory[empty_index] = { item_id, 1 };
}