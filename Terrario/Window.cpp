#include "Window.h"

#include <SDL3/SDL.h>

#include <iostream>

bool Window::Create()
{
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return false;
	}

	sdl_window = SDL_CreateWindow(
		"Terrario",
		WINDOW_WIDTH, WINDOW_HEIGHT,
		SDL_WINDOW_RESIZABLE
	);

	if (!sdl_window)
	{
		std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		return false;
	}
}

void Window::Destroy()
{
	SDL_DestroyWindow(sdl_window);
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
}
