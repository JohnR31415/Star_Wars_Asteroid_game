#ifndef VECTOR2D
#define VECTOR2D
#include <iostream>
#include "Engine.h"

struct Vector2D
{
	float x;
	float y;
public:
	Vector2D(float x = 0, float y = 0) : x(x), y(y) {} 

	inline operator float*()
	{
		return &x;
	}

	inline Vector2D perpCW() const
	{
		return Vector2D(-y, x);
	}

	inline Vector2D perpCCW() const
	{
		return Vector2D(y, -x);
	}

	inline Vector2D Normalized() const
	{
		return Vector2D(x/Length(), y/Length());
	}

	inline float Length() const
	{
		return sqrt(x*x + y*y);
	}

	inline float LengthSquared() const
	{
		float length = Length();
		return length*length;
	}

	inline float Dot(const Vector2D& right) const
	{
		return x*right.x + y*right.y;
	}

	inline float Cross(const Vector2D& right) const
	{
		return x*right.y - right.x*y;
	}
};

inline Vector2D operator+(const Vector2D& left, const Vector2D& right)
{
	Vector2D ret;
	ret.x = left.x + right.x;
	ret.y = left.y + right.y;
	return ret;
}

inline Vector2D operator-(const Vector2D& left, const Vector2D& right)
{
	Vector2D ret;
	ret.x = left.x - right.x;
	ret.y = left.y - right.y;
	return ret;
}

inline Vector2D operator*(const Vector2D& left, const Vector2D&right)
{
	Vector2D ret;
	ret.x = left.x * right.x;
	ret.y = left.y * right.y;
	return ret;
}

inline Vector2D operator*(const Vector2D& left, const float& right)
{
	Vector2D ret;
	ret.x = left.x * right;
	ret.y = left.y * right;
	return ret;
}

inline Vector2D operator*(const float& left, const Vector2D& right)
{
	Vector2D ret;
	ret.x = left * right.x;
	ret.y = left * right.y;
	return ret;
}

inline Vector2D operator/(const Vector2D& left, const Vector2D&right)
{
	Vector2D ret;
	ret.x = left.x / right.x;
	ret.y = left.y / right.y;
	return ret;
}

inline Vector2D operator/(const Vector2D& left, const float&right)
{
	Vector2D ret;
	ret.x = left.x / right;
	ret.y = left.y / right;
	return ret;
}

inline Vector2D operator/(const float& left, const Vector2D&right)
{
	Vector2D ret;
	ret.x = left / right.x;
	ret.y = left / right.y;
	return ret;
}

inline std::ostream& operator<<(std::ostream& stream, const Vector2D& right)
{
	std::cout << "[" << right.x << ", " << right.y << "]";
	return stream;
	
}

inline float Dot(const Vector2D& left, const Vector2D& right)
{
	return left.x*right.x + left.y*right.y;
}

inline float Cross(const Vector2D& left, const Vector2D& right)
{
	return left.x*right.y - right.x*left.y;
}
#endif