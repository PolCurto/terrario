#include "CharacterController.h"

#include "Engine.h"

#include <SDL3/SDL_scancode.h>
#include <iostream>

bool CharacterController::Init()
{
	return true;
}

void CharacterController::Update(Engine& engine)
{
	direction.x = 0;
	direction.y = 0;

	if (engine.inputs.keyboard[SDL_SCANCODE_LSHIFT])
	{
		current_speed = 1000.0f;
	}
	else
	{
		current_speed = 150.0f;
	}

	if (engine.inputs.keyboard[SDL_SCANCODE_W])
	{ 
		direction.y -= 1;
	}
	if (engine.inputs.keyboard[SDL_SCANCODE_A])
	{
		direction.x -= 1;
	}
	if (engine.inputs.keyboard[SDL_SCANCODE_S])
	{
		direction.y += 1;
	}
	if (engine.inputs.keyboard[SDL_SCANCODE_D])
	{
		direction.x += 1;
	}

	entity->position += direction * current_speed * (engine.timer.delta_time / 1000.0f);
}

bool CharacterController::Close()
{
	return true;
}