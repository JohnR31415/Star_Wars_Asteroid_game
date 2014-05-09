#ifndef MATRIX3D
#define MATRIX3D
#include "Vector3D.h"

static float pi = 3.141592653589793238462643383f;
class Matrix3D
{
public:
	Vector3D basis1;
	Vector3D basis2;
	Vector3D basis3;

	Matrix3D(Vector3D x = Vector3D(1, 0, 0), Vector3D y = Vector3D(0, 1, 0), Vector3D z = Vector3D(0, 0, 1)) 
		: basis1(x), basis2(y), basis3(z) {  }
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
			case 2:
				basis1.z = scale;
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
			case 2:
				basis2.z = scale;
				break;
			}
			break;
		case 2:
			switch(row)
			{
			case 0:
				basis3.x = scale;
				break;
			case 1:
				basis3.y = scale;
				break;
			case 2:
				basis3.z = scale;
				break;
			}
			break;
		}
	}
};

inline Matrix3D scale3D(float scale)
{
	Matrix3D ret;
	ret.setValueAt(0, 0, scale);
	ret.setValueAt(1, 1, scale);
	return ret;
}

inline Matrix3D scaleX(float scale)
{
	Matrix3D ret;
	ret.setValueAt(0, 0, scale);
	return ret;
}

inline Matrix3D scaleY(float scale)
{
	Matrix3D ret;
	ret.setValueAt(1, 1, scale);
	return ret;
}

inline Matrix3D rotate(float amount)
{
	Matrix3D ret;
	ret.setValueAt(0, 0, cos(amount));
	ret.setValueAt(1, 0, sin(amount));
	ret.setValueAt(0, 1, -sin(amount));
	ret.setValueAt(1, 1, cos(amount));
	return ret;
}

//inline Matrix3D rotate(float x, float y)
//{
//	y;
//	Matrix3D ret;
//	ret.setValueAt(0, 0, cos(x));
//	ret.setValueAt(1, 0, sin(x));
//	ret.setValueAt(0, 1, -sin(x));
//	ret.setValueAt(1, 1, cos(y));
//	return ret;
//}

inline Matrix3D transX(float translation)
{
	Matrix3D ret;
	ret.basis1.z = translation;
	return ret;
}

inline Matrix3D transY(float translation)
{
	Matrix3D ret;
	ret.basis2.z = translation;
	return ret;
}

inline Matrix3D translate(float x, float y)
{
	Matrix3D ret;
	ret.basis1.z = x;
	ret.basis2.z = y;
	return ret;
}

inline Matrix3D translate(Vector3D vector)
{
	Matrix3D ret;
	ret.basis1.z = vector.x;
	ret.basis2.z = vector.y;
	return ret;
}


inline Vector3D operator*(const Matrix3D& op, const Vector3D& right)
{
	/* 
	00*x + 10*y + 20
	01*x + 11*y + 21
	*/
	Vector3D ret;
	ret.x = op.basis1.x * right.x + op.basis1.y * right.y + op.basis1.z;
	ret.y = op.basis2.x * right.x + op.basis2.y * right.y + op.basis2.z;
	ret.z = 1;
	return ret;
}

inline Matrix3D operator*(const Matrix3D& left, const Matrix3D& right)
{
	/*
	00*00 + 10*01, 00*10 + 10*11, 00*20 + 10*21 + 20
	01*00 + 11*01, 01*10 + 11*11, 01*20 + 11*21 + 21
	0, 0, 1
	*/
	Matrix3D ret;

	//Basis1
	ret.basis1.x =
		left.basis1.x * right.basis1.x + left.basis1.y * right.basis2.x;
	ret.basis1.y =
		left.basis1.x * right.basis1.y + left.basis1.y * right.basis2.y;
	ret.basis1.z =
		left.basis1.x * right.basis1.z + left.basis1.y * right.basis2.z + left.basis1.z;

	//Basis2
	ret.basis2.x =
		left.basis2.x * right.basis1.x + left.basis2.y * right.basis2.x;
	ret.basis2.y =
		left.basis2.x * right.basis1.y + left.basis2.y * right.basis2.y;
	ret.basis2.z =
		left.basis2.x * right.basis1.z + left.basis2.y * right.basis2.z + left.basis2.z;

	//Basis3
	ret.basis3.x = 0;
	ret.basis3.y = 0;
	ret.basis3.z = 1;

	return ret;
}
inline float DegreesToRadians(float degrees)
{
	return degrees * (pi/180);
}

#endif