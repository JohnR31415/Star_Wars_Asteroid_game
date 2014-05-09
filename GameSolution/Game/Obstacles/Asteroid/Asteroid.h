#pragma once
#ifndef ASTEROID
#define ASTEROID

#include "..\..\Base\Obstacle.h"
#include "..\..\Global.h"
#include "..\..\Effects\AsteroidExplosion.h"

class Asteroid
	: public Obstacle
{
public:
	Asteroid::Asteroid();
	Asteroid::~Asteroid();

	void Asteroid::Initialize();
	void Asteroid::Initialize2(Vector3D pos, Vector3D vec, float scale);

	void Asteroid::Draw(Core::Graphics& g);
	void Asteroid::Update(float dt);

	void Asteroid::Spawn();
	void Asteroid::Collide();
	void Asteroid::Bounce(GameEntity* entity);
	bool Asteroid::DamageEntity(GameEntity* entity, float damage);
	void Asteroid::Explode();

	void Asteroid::Display(float dt);
	void Asteroid::ReadyForGame();
};

#endif