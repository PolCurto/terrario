#pragma once

#include "Vector2.h"

struct Window;

enum class KeyState
{
	Idle,
	Down,
	Hold,
	Up
};

enum MouseButtons
{
	Left,
	Center,
	Right
};

struct Inputs
{
	bool Create();
	bool Update(Window& window);
	bool Destroy();

	KeyState* keyboard = nullptr;
	KeyState* mouse_buttons = nullptr;
	Vector2 mouse_pos{};
};