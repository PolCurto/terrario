#pragma once

#include "IComponent.h"
#include "Entity.h"

struct Game;

struct CharacterController : IComponent
{
	bool Init() override;
	void Update(Engine&	engine, Game& game) override;
	bool Close() override;

	void SetEntity(Entity* parent) { entity = parent; }

	Entity* entity = nullptr;

	float current_speed = 150.0f;
	Vector2 direction;

	bool debug_mode = false;
};