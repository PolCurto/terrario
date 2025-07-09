#pragma once

#include "IComponent.h"
#include "Entity.h"

struct Game;

struct CameraController : IComponent
{
	bool Init() override { return true; };
	void Update(Engine& engine, Game& game) override;
	bool Close() override { return true; };

	Entity* entity = nullptr;

	bool debug_mode = false;
	bool is_fast = false;

	Entity* target;
};