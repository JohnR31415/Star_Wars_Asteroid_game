#ifndef EVENT_ARGS_H
#define EVENT_ARGS_H

struct BasicVectorEquationInfo
{
	float scalar1;
	float x1;
	float y1;
	bool add;
	float scalar2;
	float x2;
	float y2;
};

struct PerpendicularData
{
	float x;
	float y;
};

struct LineEquationData
{
	float d;
	float n_i;
	float n_j;
	float p_x;
};

struct DotProductData
{
	float v1i;
	float v1j;
	bool projectOntoLeftVector;
	float v2i;
	float v2j;
};

struct LerpData
{
	float a_i;
	float a_j;
	float b_i;
	float b_j;
	float beta;
};

struct LinearTransformationData
{
	// row col
	float m00;
	float m10;
	float m01;
	float m11;
	float v0;
	float v1;
};

struct AffineTransformationData
{
	// First 9 floats is the matrix, row major order
	// The rest of the floats are vectors (i, j, k), 5 vectors
	const float* data;
};

struct MatrixTransformData2D
{
	int selectedMatrix;
	float scaleX;
	float scaleY;
	float rotate;
	float translateX;
	float translateY;
	MatrixTransformData2D()
	{
		selectedMatrix = -1;
		scaleX = 1;
		scaleY = 1;
		rotate = 0;
		translateX = 0;
		translateY = 0;
	}
};

struct MatrixTransformData3D
{
	int selectedMatrix;
	float scaleX;
	float scaleY;
	float scaleZ;
	float rotateX;
	float rotateY;
	float rotateZ;
	float translateX;
	float translateY;
	float translateZ;
};

#endif