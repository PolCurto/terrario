#pragma once

#include "IComponent.h"

#include "IntVector2.h"

#include <vector>

struct Entity;


struct TreeComponent : IComponent
{
	TreeComponent(const IntVector2& first_tile);

	bool Init() override { return true; };
	void Update(Engine& engine, Game& game) override;
	bool Close() override {	return true; }

	Entity* entity = nullptr;
	std::vector<IntVector2> tiles;

	float time_elapsed = 0.0f;
	float growth_ratio = 0.0f;
	bool is_growing = true;
	int max_growth = 0;
	int curr_growth = 0;
};