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
	SDL_FRect rectangle{};
	rectangle.x = entity->position.x - (engine.renderer.camera_pos.x / parallaxFactor) + static_cast<float>(WINDOW_WIDTH) / 2;
	rectangle.y = entity->position.y - (engine.renderer.camera_pos.y / parallaxFactor) + static_cast<float>(WINDOW_HEIGHT) / 2;
	rectangle.h = 40.0f; 
	rectangle.w = 40.0f;

	//TODO: remove SDL_Frect tyoe from here, pass to the render function the position and widht/height (We will see if that fits with textures)
	engine.renderer.RenderRect(rectangle, 0xFF, 0xFF, 0xFF, 0xFF);
}

bool RendererComponent::Close()
{
	return true;
}