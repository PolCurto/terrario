#include "RendererComponent.h"

#include "Engine.h"
#include "Entity.h"

#include <SDL3/SDL_render.h>

bool RendererComponent::Init()
{
	return true;
}

void RendererComponent::Update(Engine& engine)
{
	SDL_FRect rectangle{};
	rectangle.x = entity->position.x;
	rectangle.y = entity->position.y;
	rectangle.h = 40.0f; 
	rectangle.w = 40.0f;

	//TODO: remove SDL_Frect tyoe from here, pass to the render function the position and widht/height (We will see if that fits with textures)
	engine.renderer.RenderRect(rectangle, 0xFF, 0xFF, 0xFF, 0xFF, parallaxFactor);
}

bool RendererComponent::Close()
{
	return true;
}