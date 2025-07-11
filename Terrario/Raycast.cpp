#include "Raycast.h"

#include "Vector2.h"
#include "TileSystem.h"

bool Raycast::ThrowTilesRay(const Vector2& start_pos, const Vector2& end_pos, const TileSystem& tile_system)
{
	// Reference: 2D version of Bresenham's line algorithm or Digital Differential Analyzer (DDA)

	Vector2 start = start_pos;
	Vector2 end = end_pos;

	// Assumes x and y are in world pos, and must be converted to tile pos
	tile_system.WorldToTilePos(&start.x, &start.y);
	tile_system.WorldToTilePos(&end.x, &end.y);


	const int x0 = static_cast<int>(std::floor(start.x));
	const int x1 = static_cast<int>(std::floor(end.x));

	const int y0 = static_cast<int>(std::floor(start.y));
	const int y1 = static_cast<int>(std::floor(end.y));

	const int dx = std::abs(x1 - x0);
	const int dy = std::abs(y1 - y0);

	const int slope_x = (x0 < x1) ? 1 : -1;
	const int slope_y = (y0 < y1) ? 1 : -1;

	int error = dx - dy;

	int x = x0;
	int y = y0;

	while (true)
	{
		if (tile_system.IsTile(x, y)) return true;

		if (x == x1 && y == y1) return false;

		int e2 = 2 * error;
		if (e2 > -dy)
		{
			error -= dy;
			x += slope_x;
		}
		if (e2 < dx)
		{
			error += dx;
			y += slope_y;
		}
	}
}