#pragma once

struct Engine;
struct Game;

struct IComponent
{
	virtual bool Init() = 0;
	virtual void Update(Engine& engine, Game& game) = 0;
	virtual bool Close() = 0;
};
