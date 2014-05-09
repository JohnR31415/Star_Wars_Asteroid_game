#pragma once
#ifndef PARTICLE
#define PARTICLE
#include "Core.h"
#include "..\Math\Vector3D.h"
#include "..\Math\Matrix3D.h"
#include "Debug\DebugMemory.h"
using Core::RGB;

class Particle
{
public:
	Vector3D position;
	Vector3D velocity;
	Matrix3D matrix;
	RGB color;
	float lifetime;
	float scalar;
};

#endif