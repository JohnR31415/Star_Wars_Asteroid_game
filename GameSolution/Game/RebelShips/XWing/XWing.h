#pragma once
#ifndef REBELSHIPS_XWING
#define REBELSHIPS_XWING

#include "..\..\Base\Ship.h"
#include "..\..\Global.h"
#include "..\..\Weapons\RebelLazer.h"
#include "..\..\Effects\XWingExplosion.h"
#include "..\..\Weapons\RebelTorpedo.h"
#include "..\..\Effects\RebelTorpedoBlast.h"

class XWing
	: public Ship
{
public:
	XWing::XWing();
	XWing::~XWing();

	void XWing::Initialize();

	void XWing::Draw(Core::Graphics& g);
	void XWing::Update(float dt);

	void XWing::Spawn();
	void XWing::Collide();
	void XWing::Bounce(GameEntity* entity);
	void XWing::BounceOffScreen();
	bool XWing::DamageEntity(GameEntity* entity, float damage);
	void XWing::Explode();

	void XWing::ShootLazer();
	void XWing::ShootMissle();
	void XWing::ShootTorpedo();
	void XWing::ShootCannon();
	
	void XWing::Display(float dt);
	void XWing::ReadyForGame();
};

#endif