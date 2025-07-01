#include "RendererComponent.h"

#include "Engine.h"
#include "Entity.h"

#include <SDL3/SDL_render.h>

bool RendererComponent::Init()
{
	return true;
}

void RendererComponent::Update(const Engine& engine)
{
	SDL_SetRenderDrawColor(engine.window.renderer, 255, 255, 255, 255);

	SDL_FRect rectangle{};
	rectangle.x = entity->position.x;
	rectangle.y = entity->position.y;
	rectangle.h = 40.0f;
	rectangle.w = 40.0f;

	SDL_RenderFillRect(engine.window.renderer, &rectangle);
}

bool RendererComponent::Close()
{
	return true;
}