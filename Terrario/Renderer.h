#pragma once

#include "Vector2.h"

#include <stdint.h>
#include <string>

struct SDL_Window;
struct SDL_Renderer;
struct SDL_FRect;

struct Renderer
{
	bool Create(SDL_Window* window);
	void Destroy();

	void Render();
	void RenderRect(const SDL_FRect& rect, uint8_t r, uint8_t g, uint8_t b, uint8_t a) const;
	void RenderDebugText(const std::string& text, float x, float y) const;

	SDL_Renderer* sdl_renderer = nullptr;

	// TODO: Maybe in the future this needs a full camera class?
	Vector2 camera_pos;
};