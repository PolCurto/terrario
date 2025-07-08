#pragma once

struct Vector2
{
	Vector2() = default;
	Vector2(float x, float y) : x(x), y(y) {};

	float x = 0;
	float y = 0;

	Vector2 operator+(Vector2 other) const
	{
		return { x + other.x, y + other.y };
	}
	
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
