#pragma once

#include "IComponent.h"
#include "Entity.h"

struct CharacterController : IComponent
{
	bool Init() override;
	void Update(const Engine& engine) override;
	bool Close() override;

	void SetEntity(Entity* parent) { entity = parent; }

	Entity* entity = nullptr;
};