#include "CharacterController.h"

#include "Engine.h"
#include "Globals.h"
#include "Game.h"

#include <SDL3/SDL_scancode.h>
#include <iostream>

constexpr float DEFUALT_SPEED = 150.0f;

bool CharacterController::Init()
{
	return true;
	current_speed = DEFUALT_SPEED;
}

void CharacterController::Update(Engine& engine, Game& game)
{
	direction.x = 0;
	direction.y = 0;

	if (engine.inputs.keyboard[SDL_SCANCODE_LSHIFT] == KeyState::Down)
	{
		current_speed = DEFUALT_SPEED * 10;
	}
	else if (engine.inputs.keyboard[SDL_SCANCODE_LSHIFT] == KeyState::Up)
	{
		current_speed = DEFUALT_SPEED;
	}

	if (engine.inputs.keyboard[SDL_SCANCODE_W] == KeyState::Hold)
	{ 
		direction.y -= 1;
	}
	if (engine.inputs.keyboard[SDL_SCANCODE_A] == KeyState::Hold)
	{
		direction.x -= 1;
	}
	if (engine.inputs.keyboard[SDL_SCANCODE_S] == KeyState::Hold)
	{
		direction.y += 1;
	}
	if (engine.inputs.keyboard[SDL_SCANCODE_D] == KeyState::Hold)
	{
		direction.x += 1;
	}

	entity->position += direction * current_speed * (engine.timer.delta_time / 1000.0f);


	// Mouse input
	Vector2 mouse;

	mouse.x = engine.inputs.mouse_pos.x - engine.window.width / 2.0f;
	mouse.y = engine.inputs.mouse_pos.y - engine.window.height / 2.0f;

	DebugLog("Player position: " + std::to_string(entity->position.x) + " " + std::to_string(entity->position.y));
	DebugLog("Mouse world position: " + std::to_string(mouse.x) + " " + std::to_string(mouse.y));
	DebugLog("----");

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