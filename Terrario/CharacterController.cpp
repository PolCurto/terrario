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
	return true;
}

void CharacterController::Update(Engine& engine, Game& game)
{
	Vector2 desired_position{};
	speed.x = 0;

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

	if (engine.inputs.keyboard[SDL_SCANCODE_SPACE] == KeyState::Down)
	{
		speed.y = -500.0f;
	}

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
	}

	if (!is_grounded) speed.y += GRAVITY * (engine.timer.delta_time / 1000.0f);

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
		game.tile_system.PlaceTile(mouse.x, mouse.y, engine, TileType::Dirt);
	}
}

bool CharacterController::Close()
{
	return true;
}