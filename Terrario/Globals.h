#pragma once

#include <string>
#include <iostream>

inline void DebugLog(const std::string& log) { std::cout << log << std::endl; } ;

namespace Globals
{
	constexpr int WINDOW_WIDTH = 1920;
	constexpr int WINDOW_HEIGHT = 1080;

	constexpr int RENDER_TEXTURE_WIDTH = 1920;
	constexpr int RENDER_TEXTURE_HEIGHT = 1080;
}