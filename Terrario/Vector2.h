#pragma once

struct Vector2
{
	float x = 0;
	float y = 0;

	// TODO: Operators (when the need raises)

	Vector2 operator*(float other) const
	{
		return { x * other, y * other };
	}

	Vector2& operator+=(const Vector2& other)
	{
		x += other.x;
		y += other.y; 
		return *this;
	}
};
