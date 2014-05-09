#pragma once
#ifndef OBSTACLE
#define OBSTACLE

#include "GameEntity.h"

class Obstacle
	: public GameEntity
{
public:
	virtual ~Obstacle() { }
	virtual void Initialize2(Vector3D pos, Vector3D vec, float scale) { pos; vec; scale; }
};

#endif