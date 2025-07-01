#include "Window.h"

#include <SDL3/SDL_render.h>

#include <iostream>

bool Window::Create()
{
	window = SDL_CreateWindow(
		"Terrario",
		1920, 1080,
		SDL_WINDOW_RESIZABLE
	);

	if (!window)
	{
		std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		return false;
	}

	renderer = SDL_CreateRenderer(window, NULL);
	if (!renderer)
	{
		std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		return false;
	}
}

void Window::Destroy()
{
	SDL_DestroyWindow(window);
}

void Window::Render()
{
	SDL_RenderPresent(renderer);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}

void Window::RenderRect(const SDL_FRect& rect, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_RenderRect(renderer, &rect);
}

void Window::RenderDebugText(const std::string& text, float x, float y)
{
	SDL_RenderDebugText(renderer, x, y, text.c_str());
}