#include "Renderer.h"

#include "SDL3/SDL_render.h"
#include <iostream>

bool Renderer::Create(SDL_Window* window)
{
	sdl_renderer = SDL_CreateRenderer(window, NULL);
	if (!sdl_renderer)
	{
		std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		return false;
	}
}

void Renderer::Destroy()
{
	SDL_DestroyRenderer(sdl_renderer);
}

void Renderer::Render()
{
	SDL_RenderPresent(sdl_renderer);

	SDL_SetRenderDrawColor(sdl_renderer, 100, 100, 100, 255);
	SDL_RenderClear(sdl_renderer);
}

void Renderer::RenderRect(const SDL_FRect& rect, uint8_t r, uint8_t g, uint8_t b, uint8_t a) const
{
	SDL_SetRenderDrawColor(sdl_renderer, r, g, b, a);
	SDL_RenderFillRect(sdl_renderer, &rect);
}

void Renderer::RenderDebugText(const std::string& text, float x, float y) const
{
	SDL_RenderDebugText(sdl_renderer, x, y, text.c_str());
}