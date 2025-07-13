#pragma once

#include <stdint.h>

struct Inputs;

struct Timer
{
	void Tick(const Inputs& inputs);

	float elapsed_time = 0;
	float delta_time = 0;
	uint64_t lastTick = 0;
};