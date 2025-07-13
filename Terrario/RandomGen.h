#pragma once

#include <random>

struct RandomGen
{
	void Create();

	float RandomFloat() { return float_dist(rng); };
	int RandomInt() { return int_dist(rng); };

	float RandomFloatRange(float min, float max);
	int RandomIntRange(int min, int max);

	std::mt19937 rng;
	std::uniform_real_distribution<float> float_dist;
	std::uniform_int_distribution<int> int_dist;
};