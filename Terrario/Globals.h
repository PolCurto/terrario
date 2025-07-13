#pragma once

#include <string>
#include <iostream>
#include <random>

inline void DebugLog(const std::string& log) { std::cout << log << std::endl; } ;

namespace Globals
{
	constexpr int RENDER_TEXTURE_WIDTH = 1920;
	constexpr int RENDER_TEXTURE_HEIGHT = 1080;
}