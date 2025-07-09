#pragma once

#include "Entity.h"
#include "IComponent.h"
#include "Vector2.h"

struct Entity;
struct Game;

struct CameraComponent : IComponent
{
	bool Init() override {
		return true;
	};
	void Update(Engine& engine, Game& game) override {};
	bool Close() override { return true; };

	void SetAsMainCamera(Engine& engine);
	const Vector2& GetPosition() const { return entity->position; };

	Entity* entity = nullptr;
	bool free_cam = false;
};