#include "Window.h"

#include "Globals.h"

#include <SDL3/SDL.h>
#include <iostream>

bool Window::Create()
{
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return false;
	}

	const SDL_DisplayMode* dm = SDL_GetDesktopDisplayMode(1);
	if (!dm)
	{
		std::cerr << "SDL_GetDesktopDisplayMode Error: " << SDL_GetError() << std::endl;
		return false;
	}

	sdl_window = SDL_CreateWindow(
		"Terrario",
		dm->w / 2, dm->h / 2,
		SDL_WINDOW_RESIZABLE
	);

	if (!sdl_window)
	{
		std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		return false;
	}

	SDL_GetWindowSize(sdl_window, &width, &height);

	return true;
}

void Window::Destroy()
{
	SDL_DestroyWindow(sdl_window);
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

void Window::UpdateWindowSize()
{
	SDL_GetWindowSize(sdl_window, &width, &height);
}