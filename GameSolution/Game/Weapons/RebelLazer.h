#pragma once
#ifndef REBELLAZER
#define REBELLAZER

#include "..\Base\Projectile.h"
#include "..\Global.h"
#include "..\Effects\RebelLazerBlast.h"
#include "Debug\DebugMemory.h"

class RebelLazer
	: public Projectile
{
public:
	RebelLazer::RebelLazer();
	RebelLazer::~RebelLazer();

	void RebelLazer::Initialize(Vector3D pos, Vector3D vel, Matrix3D mat);
	void RebelLazer::Initialize() { }

	void RebelLazer::Draw(Core::Graphics& g);
	void RebelLazer::Update(float dt);

	void RebelLazer::Spawn() { }
	void RebelLazer::Collide();
	void RebelLazer::Bounce(GameEntity* entity) { entity; }
	bool RebelLazer::DamageEntity(GameEntity* entity, float damage);
	void RebelLazer::Explode();

	void RebelLazer::Display(float dt) { dt; }
	void RebelLazer::ReadyForGame() { }


};

#endif