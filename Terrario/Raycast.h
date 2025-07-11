#pragma once

struct Vector2;
struct TileSystem;

namespace Raycast
{
	bool ThrowTilesRay(const Vector2& start_pos, const Vector2& end_pos, const TileSystem& tile_system);
}
