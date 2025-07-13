#include "RandomGen.h"

void RandomGen::Create()
{
	rng = std::mt19937(std::random_device{}());
	float_dist = std::uniform_real_distribution<float>(1.0f, 100.0f);
	int_dist = std::uniform_int_distribution<int>(1, 100);
}

float RandomGen::RandomFloatRange(float min, float max)
{
	std::uniform_real_distribution<float> temp_dist(min, max);
	return temp_dist(rng);
}

int RandomGen::RandomIntRange(int min, int max)
{
	std::uniform_int_distribution<int> temp_dist(min, max);
	return temp_dist(rng);
}