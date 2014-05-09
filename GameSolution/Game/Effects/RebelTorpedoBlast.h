#pragma once
#ifndef REBELTORPEDOBLAST
#define REBELTORPEDOBLAST

#include "Particle\ParticleEffects.h"

class RebelTorpedoBlast
	: public ParticleEffects
{
public:
	RebelTorpedoBlast::RebelTorpedoBlast(Vector3D start, float min, float max)
		: ParticleEffects(500, start, RGB(255, 100, 125))
	{
		start;
		min;
		max;
		lifetime = 2.0f;
		for(int i=0;i<numParticles;i++)
		{
			particles[i].velocity = rand.randomVector() * rand.randomInRange(min, max);
			particles[i].color = varColor(particles[i].color, 100);
			particles[i].lifetime = rand.randomInRange(1.5f, 2.0f);
			particles[i].scalar = 1;
		}
	}

	void RebelTorpedoBlast::Draw(Core::Graphics& g)
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

	void RebelTorpedoBlast::Update(float dt)
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
	}
};

#endif