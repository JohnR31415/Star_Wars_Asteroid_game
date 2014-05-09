#pragma once
#ifndef GAMEENTITY
#define GAMEENTITY

#include "Core.h"
#include "Math\Vector3D.h"
#include "Math\Matrix3D.h"
#include "Particle\Color.h"
#include "..\Utility\Healthbar.h"

class GameEntity
{
public:
	bool isSpawned;
	bool isDead;
	bool isPlayer;

	float contactRadius;
	float health;
	float totalHealth;
	float armor;
	float mass;
	float lifetime;

	float rotation;
	float scalar;
	float acceleration;
	float turnSpeed;

	const char* entityName;

	Color color;
	Healthbar hb;

	Vector3D direction;
	Vector3D position;
	Vector3D velocity;

	Matrix3D matrix;

	virtual void Initialize() = 0;

	virtual void Draw(Core::Graphics& g) = 0;
	virtual void Update(float dt) = 0;

	virtual void Spawn() = 0;
	virtual void Collide() = 0;
	virtual void Bounce(GameEntity* entity) = 0;
	virtual bool DamageEntity(GameEntity* entity, float damage) = 0;
	virtual void Explode() = 0;
	
	virtual void Display(float dt) = 0;
	virtual void ReadyForGame() = 0;
};

#endif