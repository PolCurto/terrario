#pragma once

struct Engine;

struct IComponent
{
	virtual bool Init() = 0;
	virtual void Update(Engine& engine) = 0;
	virtual bool Close() = 0;
};
