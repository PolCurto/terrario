#pragma once

#include <vector>

struct Scene;
struct Engine;

struct Game
{
	Game();
	~Game();

	void Update(const Engine& engine);


	std::vector<Scene*> scenes{};
	Scene* activeScene = nullptr;
};