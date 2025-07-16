#pragma once

#include "IComponent.h"
#include <SDL3/SDL_rect.h>

struct Engine;
struct Entity;
struct Game;

struct SDL_Texture;

struct RendererComponent : IComponent
{
	bool Init() override;
	void Update(Engine& engine, Game& game) override;
	bool Close() override;

	Entity* entity = nullptr;
	SDL_Texture* texture = nullptr;
	SDL_FRect tex_src{};

	float parallaxFactor = 1.0f;
};
