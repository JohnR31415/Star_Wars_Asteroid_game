#ifndef ENGINE_TYPEDEFS_H
#define ENGINE_TYPEDEFS_H
#include "EventArgs.h"

typedef void (*BasicVectorEquationCallback)(const BasicVectorEquationInfo&);
typedef void (*PerpendicularDataCallback)(const PerpendicularData&);
typedef void (*LineEquationDataCallback)(const LineEquationData&);
typedef void (*DotProductDataCallback)(const DotProductData&);
typedef void (*LerpDataCallback)(const LerpData&);
typedef void (*LinearTransformationCallback)(const LinearTransformationData&);
typedef void (*AffineTransformationCallback)(const AffineTransformationData&);
typedef void (*MatrixTransformCallback2D)(const MatrixTransformData2D&);
typedef void (*MatrixTransformCallback3D)(const MatrixTransformData3D&);

typedef unsigned int UINT;
const float PI = 3.1415927f;
#endif