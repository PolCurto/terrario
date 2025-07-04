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

	render_texture = SDL_CreateTexture(sdl_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, 1920, 1080);
	SDL_SetRenderTarget(sdl_renderer, render_texture);
}

void Renderer::Destroy()
{
	SDL_DestroyRenderer(sdl_renderer);
}

void Renderer::PreRender() const
{
	SDL_SetRenderTarget(sdl_renderer, render_texture);
	SDL_SetRenderDrawColor(sdl_renderer, 100, 100, 100, 255);

	SDL_RenderClear(sdl_renderer);
}

void Renderer::Render() const
{
	SDL_SetRenderTarget(sdl_renderer, NULL);
	SDL_RenderClear(sdl_renderer);

	SDL_RenderTexture(sdl_renderer, render_texture, NULL, NULL);
	SDL_RenderPresent(sdl_renderer);
}

void Renderer::RenderRect(SDL_FRect& rect, uint8_t r, uint8_t g, uint8_t b, uint8_t a, float parallaxFactor, bool fill) const
{
	SDL_SetRenderDrawColor(sdl_renderer, r, g, b, a);

	SDL_FRect newRect = rect;

	// Move according to the camera
	newRect.x = rect.x - camera->GetPosition().x * parallaxFactor + static_cast<float>(WINDOW_WIDTH) / 2;
	newRect.y = rect.y - camera->GetPosition().y * parallaxFactor + static_cast<float>(WINDOW_HEIGHT) / 2;

	if (fill) SDL_RenderFillRect(sdl_renderer, &newRect);
	else SDL_RenderRect(sdl_renderer, &newRect);
}

void Renderer::RenderDebugText(const std::string& text, float x, float y) const
{
	SDL_RenderDebugText(sdl_renderer, x, y, text.c_str());
}