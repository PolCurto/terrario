#include "Renderer.h"

#include "CameraComponent.h"
#include "Entity.h"
#include "Window.h"

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

void Renderer::RenderRect(SDL_FRect& rect, uint8_t r, uint8_t g, uint8_t b, uint8_t a, float parallaxFactor) const
{
	SDL_SetRenderDrawColor(sdl_renderer, r, g, b, a);

	// Move according to the camera
	rect.x = rect.x - camera->GetPosition().x * parallaxFactor + static_cast<float>(WINDOW_WIDTH) / 2;
	rect.y = rect.y - camera->GetPosition().y * parallaxFactor + static_cast<float>(WINDOW_HEIGHT) / 2;

	SDL_RenderFillRect(sdl_renderer, &rect);
}

void Renderer::RenderDebugText(const std::string& text, float x, float y) const
{
	SDL_RenderDebugText(sdl_renderer, x, y, text.c_str());
}