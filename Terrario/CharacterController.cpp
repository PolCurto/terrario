#include "CharacterController.h"

#include "Engine.h"

#include <SDL3/SDL_scancode.h>

bool CharacterController::Init()
{
	return true;
}

void CharacterController::Update(Engine& engine)
{
	if (engine.inputs.keyboard[SDL_SCANCODE_W])
	{ 
		entity->position.y -= 0.01f;
	}
	if (engine.inputs.keyboard[SDL_SCANCODE_A])
	{
		entity->position.x -= 0.01f;
	}
	if (engine.inputs.keyboard[SDL_SCANCODE_S])
	{
		entity->position.y += 0.01f;
	}
	if (engine.inputs.keyboard[SDL_SCANCODE_D])
	{
		entity->position.x += 0.01f;
	}
}

bool CharacterController::Close()
{
	return true;
}