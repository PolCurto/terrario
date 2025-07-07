#pragma once

struct SDL_Window;

struct Window
{
	bool Create();
	void Destroy();

	void UpdateWindowSize();

	SDL_Window* sdl_window = nullptr;
	int width;
	int height;
};