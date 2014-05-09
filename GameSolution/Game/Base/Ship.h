#pragma once
#ifndef SHIP
#define SHIP

#include "GameEntity.h"

enum ShipType
{
	AW,
	BW,
	XW,
	YW,
	TB,
	TD,
	TF,
	TI
};

enum FireMode
{
	ALT,
	ALL,
	CHARGE
};

class Ship
	: public GameEntity
{
public:
	ShipType type;
	FireMode mode;

	Vector3D* engines;
	Vector3D* barrels;
	
	int currentBarrel;
	int barrelCount;

	bool bombLastFrame;
	bool cannonLastFrame;
	bool lazerLastFrame;
	bool missleLastFrame;
	bool torpedoLastFrame;

	float bombCooldown;
	float cannonCooldown;
	float lazerCooldown;
	float missleCooldown;
	float torpedoCooldown;

	bool startBombCooldown;
	bool startCannonCooldown;
	bool startLazerCooldown;
	bool startMissleCooldown;
	bool startTorpedoCooldown;

	float bombFrequency;
	float cannonFrequency;
	float lazerFrequency;
	float missleFrequency;
	float torpedoFrequency;

	float shieldRadius;
	bool hasAstromechDroid;

	virtual ~Ship() { }
	virtual void BounceOffScreen() { }
	virtual void ShootLazer() { }
	virtual void ShootMissle() { }
	virtual void ShootTorpedo() { }
	virtual void ShootCannon() { }
};

#endif