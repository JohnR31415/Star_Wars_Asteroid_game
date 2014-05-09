#ifndef TWO_D_HARNDESS_RENDER_UI_H
#define TWO_D_HARNDESS_RENDER_UI_H
#include "TypeDefs.h"
#include "EventArgs.h"

#define TWOD_CALCULATOR_EXPORTS
#ifdef TWOD_CALCULATOR_EXPORTS
#define CALCULATOR_SHARED __declspec( dllexport )
#else
#define CALCULATOR_SHARED __declspec( dllimport )
#endif

class CALCULATOR_SHARED RenderUI
{

	// Vector operation data
	BasicVectorEquationCallback newBasicVectorEquation;
	const float* leftVector;
	const float* rightVector;
	const float* resultVector;

	// Perpendicular data
	const float* orignalVector; 
	const float* normalVector;
	const float* cwPerpendicularVector;
	const float* ccwPerpendicularVector;
	PerpendicularDataCallback newPerpendicularDataCallback;

	// Line equation data
	const float* p; // Vector
	const float* n; // Vector
	const float* d; // Scalar
	LineEquationDataCallback lineEquationDataCallback;

	// Dot and Cross Product
	const float* dotProductVector1;
	const float* dotProductVector2;
	const float* dotProductProjectionVector;
	const float* dotProductRejectionVector;
	DotProductDataCallback dotProductCallback;

	// LERP
	const float* lerpAVector;
	const float* lerpBVector;
	const float* lerpAMinusBVector;
	const float* lerpAVectorLerpPortion;
	const float* lerpBVectorLerpPortion;
	const float* lerpLerpResultVector;
	LerpDataCallback lerpCallback;

	// Basic matrix multiply
	const float* basicMatrixMultiplyResultVector;
	LinearTransformationCallback basicMatrixMultiplyCallback;

	// Matrix slider widget
	const float* affineTransformationResultVectors;
	AffineTransformationCallback affineTransformationCallback;

	// 2D Matrix transformation
	const float* lines;
	int NUM_LINES;
	const float* matrices;
	const float* currentTransform;
	MatrixTransformCallback2D matrixUiChangedCallback;

	// 3D Matrix transformation
	const float* matrices3d;
	const float* fullTransform3d;
	const char* fbxFileName;
	MatrixTransformCallback3D matrixTransformData3DCallback;

	bool showCameraTransform;

public:
	RenderUI();
	void setBasicVectorEquationData(
		BasicVectorEquationCallback newBasicVectorEquation, 
		const float* leftVector, const float* rightVector, 
		const float* resultVector);
	void setPerpendicularData(
		const float* orignalVector, 
		const float* normalVector,
		const float* cwPerpendicularVector,
		const float* ccwPerpendicularVector,
		PerpendicularDataCallback perpendicularDataCallback);
	void setLineEquationData(
		const float* p, // Vector
		const float* n, // Vector
		const float* d, // Scalar
		LineEquationDataCallback callback);
	void setDotProductData(
		const float* vector1,
		const float* vector2,
		const float* projectionVector,
		const float* rejectionVector,
		DotProductDataCallback callback);
	void setLerpData(
		const float* aVector,
		const float* bVector,
		const float* aMinusBVector,
		const float* aVectorLerpPortion,
		const float* bVectorLerpPortion,
		const float* lerpResultVector,
		LerpDataCallback callback);
	void setLinearTransformationData(
		const float* resultVector,
		LinearTransformationCallback callback);
	void setAffineTransformationData(
		const float* resultVectors,
		AffineTransformationCallback callback);
	void set2DMatrixVerticesTransformData(
			const float* lines, int numLines, 
			const float* matrices,
			const float* currentTransform,
			MatrixTransformCallback2D uiChangedCallback);
	bool initialize(int argc, char* argv[]);
	bool shutdown();
	int run();
};

#endif