#pragma once

#include "Vector2.h"
#include "CameraComponent.h"

#include <stdint.h>
#include <string>
#include <vector>

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;
struct SDL_FRect;

struct Renderer
{
	bool Create(SDL_Window* window);
	void Destroy();

	void PreRender() const;
	void Render() const;
	void RenderRect(const SDL_FRect& rect, uint8_t r, uint8_t g, uint8_t b, uint8_t a, float parallaxFactor = 1.0f, bool fill = true) const;
	void RenderTexture(SDL_Texture* texture, const SDL_FRect& source, const SDL_FRect& destination, float parallaxFactor) const;
	void RenderDebugText(const std::string& text, float x, float y) const;

	SDL_Texture* LoadTexture(const char* filepath) const;
	void UnloadTexture(const SDL_Texture* texture);

	const Vector2& GetCameraPos() const { return camera->GetPosition(); }

	SDL_Renderer* sdl_renderer = nullptr;
	SDL_Texture* render_texture = nullptr;

	std::vector<SDL_Texture*> textures;
	CameraComponent* camera = nullptr;
};