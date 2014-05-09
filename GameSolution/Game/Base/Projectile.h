#pragma once
#ifndef PROJECTILE
#define PROJECTILE

#include "GameEntity.h"

enum ProjectileType 
{
	RB,
	RL,
	RM,
	RT,
	IB,
	IL,
	IM,
	IT
};

class Projectile
	: public GameEntity
{
public:
	ProjectileType type;
	bool isFired;
	bool hit;

	float damage;

	virtual ~Projectile() { }
	virtual void Initialize(Vector3D pos, Vector3D vel, Matrix3D mat) { pos; vel; mat; }
};

#endif