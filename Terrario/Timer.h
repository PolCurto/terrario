#pragma once

#include <stdint.h>

struct Timer
{
	void Tick();

	float elapsed_time = 0;
	float delta_time = 0;
	uint64_t lastTick = 0;
};