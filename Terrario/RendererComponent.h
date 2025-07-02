#pragma once

#include "IComponent.h"

struct Engine;
struct Entity;

struct SDL_Texture;

struct RendererComponent : IComponent
{
	bool Init() override;
	void Update(Engine& engine) override;
	bool Close() override;

	Entity* entity = nullptr;
	SDL_Texture* texture = nullptr;

	float parallaxFactor = 1.0f;
};
