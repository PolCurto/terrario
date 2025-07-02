#pragma once

#include <vector>

struct Scene;
struct Engine;

struct Game
{
	Game(Engine& engine);
	~Game();

	void Update(Engine& engine);


	std::vector<Scene*> scenes{};
	Scene* activeScene = nullptr;
};