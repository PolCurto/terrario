#pragma once

struct SDL_Window;

constexpr int WINDOW_WIDTH = 1920;
constexpr int WINDOW_HEIGHT = 1080;


struct Window
{
	bool Create();
	void Destroy();

	SDL_Window* sdl_window = nullptr;
};