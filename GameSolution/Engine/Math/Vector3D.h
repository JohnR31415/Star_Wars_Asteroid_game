#ifndef VECTOR3D
#define VECTOR3D
#include <iostream>
#include "..\Engine.h"

struct Vector3D
{
	//float val[3];
	float x;
	float y;
	float z;
public:
	Vector3D(float x = 0, float y = 0, float z = 0) 
		: x(x), y(y), z(z)
	{
	} 

	inline operator float*()
	{
		return &x;
	}

	inline Vector3D perpCW() const
	{
		return Vector3D(-y, x);
	}

	inline Vector3D perpCCW() const
	{
		return Vector3D(y, -x);
	}

	inline Vector3D Normalized() const
	{
		return Vector3D(x/Length(), y/Length());
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

	inline float Dot(const Vector3D& right) const
	{
		return x*right.x + y*right.y;
	}

	inline float Cross(const Vector3D& right) const
	{
		return x*right.y - right.x*y;
	}
};

inline Vector3D operator+(const Vector3D& left, const Vector3D& right)
{
	Vector3D ret;
	ret.x = left.x + right.x;
	ret.y = left.y + right.y;
	ret.z = left.z + right.z;
	return ret;
}

inline Vector3D operator-(const Vector3D& left, const Vector3D& right)
{
	Vector3D ret;
	ret.x = left.x - right.x;
	ret.y = left.y - right.y;
	ret.z = left.z * right.z;
	return ret;
}

inline Vector3D operator*(const Vector3D& left, const Vector3D&right)
{
	Vector3D ret;
	ret.x = left.x * right.x;
	ret.y = left.y * right.y;
	ret.z = left.z * right.z;
	return ret;
}

inline Vector3D operator*(const Vector3D& left, const float& right)
{
	Vector3D ret;
	ret.x = left.x * right;
	ret.y = left.y * right;
	ret.z = left.z * right;
	return ret;
}

inline Vector3D operator*(const float& left, const Vector3D& right)
{
	Vector3D ret;
	ret.x = left * right.x;
	ret.y = left * right.y;
	ret.z = left * right.z;
	return ret;
}

inline Vector3D operator/(const Vector3D& left, const Vector3D&right)
{
	Vector3D ret;
	ret.x = left.x / right.x;
	ret.y = left.y / right.y;
	ret.z = left.y / right.z;
	return ret;
}

inline Vector3D operator/(const Vector3D& left, const float&right)
{
	Vector3D ret;
	ret.x = left.x / right;
	ret.y = left.y / right;
	ret.z = left.z / right;
	return ret;
}

inline Vector3D operator/(const float& left, const Vector3D&right)
{
	Vector3D ret;
	ret.x = left / right.x;
	ret.y = left / right.y;
	ret.z = left / right.z;
	return ret;
}

inline std::ostream& operator<<(std::ostream& stream, const Vector3D& right)
{
	std::cout << "[" << right.x << ", " << right.y << ", " << right.z << "]";
	return stream;
	
}

inline float Dot(const Vector3D& left, const Vector3D& right)
{
	return left.x*right.x + left.y*right.y;
}

inline float Cross(const Vector3D& left, const Vector3D& right)
{
	return left.x*right.y - right.x*left.y;
}

struct Path
{
public:
	Vector3D start;
	Vector3D end;

	Path(Vector3D s, Vector3D e)
	{
		start = s;
		end = e;
	}
	Path() {}
};
#endif