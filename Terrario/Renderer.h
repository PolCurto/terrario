#pragma once

#include "Vector2.h"

#include <stdint.h>
#include <string>

struct CameraComponent;

struct SDL_Window;
struct SDL_Renderer;
struct SDL_FRect;

struct Renderer
{
	bool Create(SDL_Window* window);
	void Destroy();

	void Render();
	void RenderRect(SDL_FRect& rect, uint8_t r, uint8_t g, uint8_t b, uint8_t a, float parallaxFactor = 1.0f, bool fill = true) const;
	void RenderDebugText(const std::string& text, float x, float y) const;

	SDL_Renderer* sdl_renderer = nullptr;

	CameraComponent* camera;
};