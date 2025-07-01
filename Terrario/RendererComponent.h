#pragma once

#include "IComponent.h"

struct Engine;
struct Entity;

struct SDL_Texture;

struct RendererComponent : IComponent
{
	bool Init() override;
	void Update(const Engine& engine) override;
	bool Close() override;

	void SetEntity(Entity* parent) { entity = parent; };

	Entity* entity = nullptr;
	SDL_Texture* texture = nullptr;
};
