
#pragma once
#ifndef MATRIX2D
#define MATRIX2D
#include "Vector2D.h"

struct Matrix2D
{
	Vector2D basis1;
	Vector2D basis2;

	Matrix2D(Vector2D x = Vector2D(1, 0), Vector2D y = Vector2D(0, 1)) : basis1(x), basis2(y) 
	{

	} 
	void setValueAt(int col, int row, float scale)
	{
		switch(col)
		{
		case 0:
			switch(row)
			{
			case 0:
				basis1.x = scale;
				break;
			case 1:
				basis1.y = scale;
				break;
			}
			break;
		case 1:
			switch(row)
			{
			case 0:
				basis2.x = scale;
				break;
			case 1:
				basis2.y = scale;
				break;
			}
			break;
		}
	}
};

inline Vector2D operator*(const Matrix2D& op, Vector2D& right)
{
	return Vector2D(
		op.basis1.x * right.x + op.basis2.x * right.y,
		op.basis1.y * right.x + op.basis2.y * right.y);
}

inline Vector2D operator*(Vector2D& right, const Matrix2D& op)
{
	return Vector2D(
		op.basis1.x * right.x + op.basis2.x * right.y,
		op.basis1.y * right.x + op.basis2.y * right.y);
}

inline Matrix2D operator*(const Matrix2D& left, Matrix2D& right)
{
	Matrix2D ret;
	ret.basis1.x =
		left.basis1.x * right.basis1.x + left.basis1.y * right.basis2.x;
	ret.basis1.y =
		left.basis1.x * right.basis1.y + left.basis1.y * right.basis2.y;
	ret.basis2.x =
		left.basis2.x * right.basis1.x + left.basis2.y * right.basis2.x;
	ret.basis2.y =
		left.basis2.x * right.basis1.y + left.basis2.y * right.basis2.y;
	return ret;
}

inline Matrix2D Rotate(float angle)
{
	Matrix2D ret;
	ret.setValueAt(0, 0, cos(angle));
	ret.setValueAt(1, 0, sin(angle));
	ret.setValueAt(0, 1, -sin(angle));
	ret.setValueAt(1, 1, cos(angle));
	return ret;
}

inline Matrix2D Scale(float scale)
{
	Matrix2D ret;
	ret.setValueAt(0, 0, scale);
	ret.setValueAt(1, 1, scale);
	return ret;
}

inline Matrix2D ScaleX(float scale)
{
	Matrix2D ret;
	ret.setValueAt(0, 0, scale);
	return ret;
}
inline Matrix2D ScaleY(float scale)
{
	Matrix2D ret;
	ret.setValueAt(1, 1, scale);
	return ret;
}

#endif
