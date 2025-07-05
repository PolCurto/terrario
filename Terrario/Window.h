#pragma once

struct SDL_Window;

struct Window
{
	bool Create();
	void Destroy();

	SDL_Window* sdl_window = nullptr;
};