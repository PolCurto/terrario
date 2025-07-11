#include "Renderer.h"

#include "CameraComponent.h"
#include "Entity.h"
#include "Globals.h"

#include "SDL3/SDL.h"
#include "SDL3_image/SDL_image.h"
#include <iostream>

bool Renderer::Create(SDL_Window* window)
{
	sdl_renderer = SDL_CreateRenderer(window, NULL);
	if (!sdl_renderer)
	{
		std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		return false;
	}

	render_texture = SDL_CreateTexture(sdl_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, Globals::RENDER_TEXTURE_WIDTH, Globals::RENDER_TEXTURE_HEIGHT);
	SDL_SetRenderTarget(sdl_renderer, render_texture);

	return true;
}

void Renderer::Destroy()
{
	for (std::vector<SDL_Texture*>::iterator it = textures.begin(); it != textures.end(); ++it)
	{
		SDL_DestroyTexture(*it);
	}
	textures.clear();

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

void Renderer::RenderRect(const SDL_FRect& rect, uint8_t r, uint8_t g, uint8_t b, uint8_t a, float parallaxFactor, bool fill) const
{
	SDL_SetRenderDrawColor(sdl_renderer, r, g, b, a);

	SDL_FRect newRect = rect;

	// Move according to the camera
	newRect.x = rect.x - camera->GetPosition().x * parallaxFactor + static_cast<float>(Globals::RENDER_TEXTURE_WIDTH) / 2;
	newRect.y = rect.y - camera->GetPosition().y * parallaxFactor + static_cast<float>(Globals::RENDER_TEXTURE_HEIGHT) / 2;

	if (fill) SDL_RenderFillRect(sdl_renderer, &newRect);
	else SDL_RenderRect(sdl_renderer, &newRect);
}

void Renderer::RenderLine(const Vector2& start_pos, const Vector2& end_pos, uint8_t r, uint8_t g, uint8_t b, uint8_t a) const
{
	SDL_SetRenderDrawColor(sdl_renderer, r, g, b, a);

	int x0 = static_cast<int>(std::floorf(start_pos.x - camera->GetPosition().x + static_cast<float>(Globals::RENDER_TEXTURE_WIDTH) / 2));
	int x1 = static_cast<int>(std::floorf(end_pos.x - camera->GetPosition().x + static_cast<float>(Globals::RENDER_TEXTURE_WIDTH) / 2));
	
	int y0 = static_cast<int>(std::floorf(start_pos.y - camera->GetPosition().y + static_cast<float>(Globals::RENDER_TEXTURE_HEIGHT) / 2));
	int y1 = static_cast<int>(std::floorf(end_pos.y - camera->GetPosition().y + static_cast<float>(Globals::RENDER_TEXTURE_HEIGHT) / 2));

	SDL_RenderLine(sdl_renderer, x0, y0, x1, y1);
}

void Renderer::RenderTexture(SDL_Texture* texture, const SDL_FRect& source, const SDL_FRect& destination, float parallaxFactor) const
{
	SDL_FRect newRect = destination;

	// Move according to the camera
	newRect.x = destination.x - camera->GetPosition().x * parallaxFactor + static_cast<float>(Globals::RENDER_TEXTURE_WIDTH) / 2;
	newRect.y = destination.y - camera->GetPosition().y * parallaxFactor + static_cast<float>(Globals::RENDER_TEXTURE_HEIGHT) / 2;

	SDL_RenderTexture(sdl_renderer, texture, &source, &newRect);
}

void Renderer::RenderDebugText(const std::string& text, const Vector2& pos) const
{
	SDL_SetRenderDrawColor(sdl_renderer, 255, 255, 255, 255);
	SDL_RenderDebugText(sdl_renderer, pos.x, pos.y, text.c_str());
}

SDL_Texture* Renderer::LoadTexture(const char* filepath) const
{
	SDL_Texture* new_tex = IMG_LoadTexture(sdl_renderer, filepath);
	if (!new_tex) std::cerr << "Error when loading texture " << filepath << ": " << SDL_GetError() << std::endl;

	return new_tex;
}

void Renderer::UnloadTexture(const SDL_Texture* texture_to_unload)
{
	for (std::vector<SDL_Texture*>::iterator it = textures.begin(); it != textures.end(); ++it)
	{
		if (*it == texture_to_unload)
		{
			SDL_DestroyTexture(*it);
			textures.erase(it);
			break;
		}
	}
}