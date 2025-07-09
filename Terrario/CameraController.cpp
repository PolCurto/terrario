#include "CameraController.h"

#include "Engine.h"
#include "Vector2.h"

#include <SDL3/SDL_scancode.h>

constexpr int DEFAULT_SPEED = 1000;
constexpr int FAST_SPEED = 4000;

void CameraController::Update(Engine& engine, Game& game)
{
	Vector2 direction(0.0f, 0.0f);

	if (engine.inputs.keyboard[SDL_SCANCODE_F2] == KeyState::Down) debug_mode = !debug_mode;

	if (debug_mode)
	{
		if (engine.inputs.keyboard[SDL_SCANCODE_LSHIFT] == KeyState::Down) is_fast = !is_fast;

		float current_speed = is_fast ? FAST_SPEED : DEFAULT_SPEED;

		if (engine.inputs.keyboard[SDL_SCANCODE_UP] == KeyState::Hold)
		{
			direction.y -= 1;
		}
		if (engine.inputs.keyboard[SDL_SCANCODE_LEFT] == KeyState::Hold)
		{
			direction.x -= 1;
		}
		if (engine.inputs.keyboard[SDL_SCANCODE_DOWN] == KeyState::Hold)
		{
			direction.y += 1;
		}
		if (engine.inputs.keyboard[SDL_SCANCODE_RIGHT] == KeyState::Hold)
		{
			direction.x += 1;
		}

		entity->position += direction * current_speed * (engine.timer.delta_time / 1000.0f);
	}
	else
	{
		entity->position = target->position;
	}
}