#pragma once

struct IntVector2
{
	IntVector2() = default;
	IntVector2(int x, int y) : x(x), y(y) {};

	int x = 0;
	int y = 0;

	IntVector2 operator*(int other) const
	{
		return { x * other, y * other };
	}

	IntVector2& operator+=(const IntVector2& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}
};
