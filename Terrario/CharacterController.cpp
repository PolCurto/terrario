#include "CharacterController.h"

#include "Engine.h"
#include "Globals.h"
#include "Game.h"

#include <SDL3/SDL_scancode.h>
#include <SDL3/SDL_Render.h>
#include <iostream>

constexpr float DEFUALT_SPEED = 150.0f;

bool CharacterController::Init()
{
	current_speed = DEFUALT_SPEED;
	return true;
}

void CharacterController::Update(Engine& engine, Game& game)
{
	direction.x = 0;
	direction.y = 0;

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
		direction.x -= 1;
	}
	if (engine.inputs.keyboard[SDL_SCANCODE_D] == KeyState::Hold)
	{
		direction.x += 1;
	}

	if (engine.inputs.keyboard[SDL_SCANCODE_F1] == KeyState::Down)
	{
		debug_mode = !debug_mode;
	}

	Vector2 desired_position = entity->position + direction * current_speed * (engine.timer.delta_time / 1000.0f);

	// Check collisions
	bool collision = game.tile_system.CheckForTiles(desired_position, entity->size);
	if (!collision) entity->position = desired_position;
	if (debug_mode) engine.renderer.RenderRect({ entity->position.x - entity->size.x / 2, entity->position.y - entity->size.y / 2, entity->size.x, entity->size.y }, 0, 255, 0, 255, 1.0f, false);

	// TODO: All this will be replaced and depending on the item at hand, this is for testing
	Vector2 mouse;

	mouse.x = engine.inputs.mouse_pos.x - engine.window.width / 2.0f;
	mouse.y = engine.inputs.mouse_pos.y - engine.window.height / 2.0f;

	if (engine.inputs.mouse_buttons[MouseButtons::Left] == KeyState::Down)
	{
		game.tile_system.DestroyTile(mouse.x, mouse.y, engine);
	}
	else if (engine.inputs.mouse_buttons[MouseButtons::Right] == KeyState::Down)
	{
		game.tile_system.PlaceTile(mouse.x, mouse.y, engine);
	}
}

bool CharacterController::Close()
{
	return true;
}