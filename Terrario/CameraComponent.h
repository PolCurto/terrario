#pragma once

#include "IComponent.h"
#include "Vector2.h"

struct Entity;

struct CameraComponent : IComponent
{
	bool Init() override {
		return true;
	};
	void Update(Engine& engine) override {};
	bool Close() override { return true; };

	void SetAsMainCamera(Engine& engine);
	const Vector2& GetPosition() const;

	Entity* entity = nullptr;
};