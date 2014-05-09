#include "RenderUI.h"
#include "Engine.h"
#include "Math\Vector2D.h"
#include "Equations.h"

int main(int argc, char* argv[])
{
	Engine::Init();

	RenderUI renderUI;

	//Vector Tabs
	renderUI.setBasicVectorEquationData(
		MyBasicVectorEquationCallback, left, right, result);

	renderUI.setPerpendicularData(
		left, normal, cw, ccw, MyPerpendicularDataCallback);

	renderUI.setDotProductData(
		left, right, projection, rejection, MyDotProductDataCallback);

	renderUI.setLerpData(
		left, right, aMinusB, aLerp, bLerp, result, MyLerpDataCallback);

	//Matrix Tabs
	renderUI.setLinearTransformationData(result, MyLinearTransformationCallback);

	renderUI.setAffineTransformationData(
		reinterpret_cast<float*>(vectorLines), 
		MyAffineTransformationCallback);

	renderUI.set2DMatrixVerticesTransformData(
		reinterpret_cast<float*>(lines), numLines, 
		reinterpret_cast<float*>(matrices), 
		reinterpret_cast<float*>(&currentTransform), 
		MyMatrixTransformCallback2D);


	if( ! renderUI.initialize(argc, argv))
		return -1;
	return renderUI.run();
}