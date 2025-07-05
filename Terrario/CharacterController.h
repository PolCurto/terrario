#pragma once

#include "IComponent.h"
#include "Entity.h"

struct CharacterController : IComponent
{
	bool Init() override;
	void Update(Engine&	engine) override;
	bool Close() override;

	void SetEntity(Entity* parent) { entity = parent; }

	Entity* entity = nullptr;

	float speed = 150.0f;
	Vector2 direction;
};