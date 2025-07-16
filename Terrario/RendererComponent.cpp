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

	// Place the pivot at the center
	rectangle.x = entity->position.x - entity->size.x / 2;
	rectangle.y = entity->position.y - entity->size.y / 2;
	rectangle.w = entity->size.x;
	rectangle.h = entity->size.y;

	//TODO: remove SDL_Frect tyoe from here, pass to the render function the position and widht/height (We will see if that fits with textures)
	engine.renderer.RenderTexture(texture, tex_src, rectangle, parallaxFactor);
}

bool RendererComponent::Close()
{
	return true;
}