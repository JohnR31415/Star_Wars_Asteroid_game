#pragma once
#ifndef REBELTORPEDO
#define REBELTORPEDO

#include "..\Base\Projectile.h"
#include "..\Global.h"
#include "..\Effects\RebelTorpedoBlast.h"
#include "Debug\DebugMemory.h"

class RebelTorpedo
	: public Projectile
{
public:
	RebelTorpedo::RebelTorpedo();
	RebelTorpedo::~RebelTorpedo();

	void RebelTorpedo::Initialize(Vector3D pos, Vector3D vel, Matrix3D mat);
	void RebelTorpedo::Initialize() { }

	void RebelTorpedo::Draw(Core::Graphics& g);
	void RebelTorpedo::Update(float dt);

	void RebelTorpedo::Spawn() { }
	void RebelTorpedo::Collide();
	void RebelTorpedo::Bounce(GameEntity* entity) { entity; }
	bool RebelTorpedo::DamageEntity(GameEntity* entity, float damage);
	void RebelTorpedo::Explode();

	void RebelTorpedo::Display(float dt) { dt; }
	void RebelTorpedo::ReadyForGame() { }
};

#endif