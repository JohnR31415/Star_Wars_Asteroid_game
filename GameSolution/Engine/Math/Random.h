#pragma once
#ifndef RANDOM
#define RANDOM
#include <stdlib.h>
#include "Vector3D.h"
#include "Matrix3D.h"

class Random
{
public:
	float pi;
	Random()
	{
		pi = 3.141592653589793238462643383f;
	}
	float randomFloat()
	{
		return (float)rand() / RAND_MAX;
	}

	Vector3D randomVector()
	{
		float angle = 2 * pi * randomFloat();
		Vector3D vector(cos(angle), sin(angle));
		return vector;
	}

	Vector3D randomAngleVector(float range)
	{
		/*range;
		float angle = (float)range/100.0f * pi * randomFloat();
		Vector3D vector(cos(angle), sin(angle));
		return vector;*/
		Vector3D randVector(0, 1, 0);
		float randAngle = randomInRange(-DegreesToRadians(range), DegreesToRadians(range));
		Matrix3D r = rotate(randAngle);
		randVector = r * randVector;
		return randVector;
	}

	Vector3D randomDirectionVector(Vector3D dir, float range)
	{
		/*range;
		float angle = (float)range/100.0f * pi * randomFloat();
		Vector3D vector(cos(angle), sin(angle));
		return vector;*/
		Vector3D randVector = dir;
		float randAngle = randomInRange(-DegreesToRadians(range), DegreesToRadians(range));
		Matrix3D r = rotate(randAngle);
		randVector = r * randVector;
		return randVector;
	}

	Vector3D random45Vector()
	{
		Vector3D randVector(0, 1, 0);
		float randAngle = randomInRange(-pi/6, pi/6);
		Matrix3D r = rotate(randAngle);
		randVector = r * randVector;
		
		return randVector;
	}

	float randomInRange(float min, float max)
	{
		return randomFloat() * (max-min) + min;
	}
};



#endif