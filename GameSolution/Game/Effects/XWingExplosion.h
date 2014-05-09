#pragma once
#ifndef XWINGEXPLOSION
#define XWINGEXPLOSION

#include "Particle\ParticleEffects.h"
#include "..\Global.h"

class XWingExplosion
	: public ParticleEffects
{
private:
	float secondExplosionCooldown;
	bool firstExplosion;
	bool pushedExplosion;
public:
	XWingExplosion::XWingExplosion(Vector3D start, float min, float max, bool first, int particleCount)
		: ParticleEffects(particleCount, start, RGB(255, 255, 1))
	{
		start;
		min;
		max;
		lifetime = 3.0f;
		secondExplosionCooldown = 0;
		firstExplosion = first;
		pushedExplosion = false;
		for(int i=0;i<numParticles;i++)
		{
			particles[i].velocity = rand.randomVector() * rand.randomInRange(min, max);
			particles[i].color = varColor(particles[i].color, 150);
			particles[i].lifetime = rand.randomInRange(2.25f, 3.0f);
			particles[i].scalar = 1;
		}
	}

	void XWingExplosion::Draw(Core::Graphics& g)
	{
		if(lifetime > 0)
		{
			for(int i=0;i<numParticles;i++)
			{
				if(particles[i].lifetime > 0)
				{
					Vector3D p1 = particles[i].position;
					Vector3D p2 = particles[i].position + Vector3D(0, 1, 0);
					g.SetColor(particles[i].color);
					g.DrawLine(p1.x, p1.y, p2.x, p2.y);
				}
				if(particles[i].lifetime < 1)
				{
					particles[i].color = brightness(particles[i].color, particles[i].lifetime);
				}
			}
		}
	}

	void XWingExplosion::Update(float dt)
	{
		if(lifetime > 0)
		{
			for(int i=0;i<numParticles;i++)
			{
				particles[i].lifetime -= dt;
				particles[i].position = particles[i].position + particles[i].velocity * dt;
			}
			lifetime -= dt;
		}
		if(secondExplosionCooldown >= 1.15 && firstExplosion && !pushedExplosion)
		{
			pushedExplosion = true;
			explosions.push_back(new XWingExplosion(origin, 1, 750, false, 2000)); 
		}
		else
		{
			secondExplosionCooldown += dt;
		}
	}
};

#endif