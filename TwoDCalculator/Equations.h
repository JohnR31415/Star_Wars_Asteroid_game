#ifndef EQUATIONS
#define EQUATIONS
#include <iostream>
#include "Engine.h"
#include "RenderUI.h"
#include "Math\Vector2D.h"
#include "Math\Matrix2D.h"
#include "Math\Matrix3D.h"
#include "LinesForYourReference.h"

Vector2D left;
Vector2D right;
Vector2D result;

Vector2D normal;
Vector2D cw;
Vector2D ccw;

Vector2D projection;
Vector2D rejection;

Vector2D aMinusB;
Vector2D aLerp;
Vector2D bLerp;

Vector3D lines3D[5];

Vector3D vectorLines[5];

Matrix3D basis;



int maxMatrixIndex;
int matrixCount;

Matrix3D matrices[10];
Matrix3D currentTransform;

void MyBasicVectorEquationCallback(const BasicVectorEquationInfo& info)
{

	left.x = info.x1 * info.scalar1;
	left.y = info.y1 * info.scalar1;

	right.x = info.x2 * info.scalar2;
	right.y = info.y2 * info.scalar2;

	result = info.add ? left+right : left-right;
}

void MyPerpendicularDataCallback(const PerpendicularData& info)
{
	left.x = info.x;
	left.y = info.y;

	normal = left.Normalized();

	cw = left.perpCW();
	ccw = left.perpCCW();


}

//With member
void MyDotProductDataCallback(const DotProductData& info)
{
	left.x = info.v1i;
	left.y = info.v1j;

	right.x = info.v2i;
	right.y = info.v2j;

	if(info.projectOntoLeftVector)
	{
		projection = left.Normalized() * left.Dot(right) / left.Length();
		rejection = right - projection;
	}
	else
	{
		projection = right.Normalized() * right.Dot(left) / right.Length();
		rejection = left - projection;
	}
}

//With non-member
void MyDotProductDataCallback2(const DotProductData& info)
{
	left.x = info.v1i;
	left.y = info.v1j;

	right.x = info.v2i;
	right.y = info.v2j;

	if(info.projectOntoLeftVector)
	{
		projection = left.Normalized() * Dot(left, right) / left.Length();
		rejection = right - projection;
	}
	else
	{
		projection = right.Normalized() * Dot(right, left) / right.Length();
		rejection = left - projection;
	}
}

void MyLerpDataCallback(const LerpData& info)
{
	left.x = info.a_i;
	left.y = info.a_j;

	right.x = info.b_i;
	right.y = info.b_j;

	aMinusB = right - left;

	result = (1-info.beta) * left + info.beta * right;

	aLerp = (1-info.beta) * left;
	bLerp = info.beta * right;
}

void MyLinearTransformationCallback(const LinearTransformationData& data)
{
	Vector2D v1(data.v0, data.v1);
	Matrix2D op(Vector2D(data.m00, data.m10), Vector2D(data.m01, data.m11));
    result = op * v1;
}

void MyAffineTransformationCallback(const AffineTransformationData& data)
{
	Matrix3D result3D(
		Vector3D(data.data[0], data.data[1], data.data[2]),
		Vector3D(data.data[3], data.data[4], data.data[5]),
		Vector3D(data.data[6], data.data[7], data.data[8]));

	vectorLines[0] = result3D * Vector3D(data.data[9], data.data[10], data.data[11]);
	vectorLines[1] = result3D * Vector3D(data.data[12], data.data[13], data.data[14]);
	vectorLines[2] = result3D * Vector3D(data.data[15], data.data[16], data.data[17]);
	vectorLines[3] = result3D * Vector3D(data.data[18], data.data[19], data.data[20]);
	vectorLines[4] = result3D * Vector3D(data.data[21], data.data[22], data.data[23]);
}

void MyMatrixTransformCallback2D(const MatrixTransformData2D& data)
{
	
	if(data.selectedMatrix > maxMatrixIndex)
	{
		maxMatrixIndex = data.selectedMatrix;
	}

	Matrix3D xScaler = scaleX(data.scaleX);
	Matrix3D yScaler = scaleY(data.scaleY);
	Matrix3D rotator = rotate(data.rotate);

	Matrix3D tranX = transX(data.translateX);
	Matrix3D tranY = transY(data.translateY);
	matrices[data.selectedMatrix] = xScaler * yScaler * rotator * tranX * tranY;
	currentTransform = matrices[0] * matrices[1] * matrices[2] * matrices[3] * matrices[4] * matrices[5] * matrices[6] * matrices[7] * matrices[8] * matrices[9];
}
#endif