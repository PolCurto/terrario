#pragma once

#include "IComponent.h"

struct Engine;

struct SDL_Texture;

struct RendererComponent : IComponent
{
	bool Init() override;
	void Update(const Engine& engine) override;
	bool Close() override;

	SDL_Texture* texture = nullptr;
};
