#include "RendererComponent.h"

#include "Engine.h"
#include "Entity.h"
#include "Game.h"

#include <SDL3/SDL_render.h>

bool RendererComponent::Init()
{
	return true;
}

void RendererComponent::Update(Engine& engine, Game& game)
{
	SDL_FRect rectangle{};
	rectangle.x = entity->position.x;
	rectangle.y = entity->position.y;
	rectangle.w = 32.0f;
	rectangle.h = 64.0f;

	//TODO: remove SDL_Frect tyoe from here, pass to the render function the position and widht/height (We will see if that fits with textures)
	engine.renderer.RenderTexture(texture, { 0.0f, 0.0f, 32.0f, 64.0f }, rectangle, parallaxFactor);
}

bool RendererComponent::Close()
{
	return true;
}