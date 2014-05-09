#pragma once
#ifndef EXPLOSION
#define EXPLOSION
#include "Math\Vector3D.h"
#include "Core.h"
#include "Particle\ParticleEffects.h"
using Core::RGB;

class Explosion 
	: public ParticleEffects
{
public:
	Explosion::Explosion(Vector3D start, float min, float max) 
		: ParticleEffects(2500, start, RGB(255, 255, 125))
	{
		min;
		max;
		for(int i=0;i<numParticles;i++)
		{
			particles[i].velocity = rand.randomVector() * rand.randomInRange(min, max);
			particles[i].color = varColor(particles[i].color, 50);
		}
	}

	Explosion()
	{
	}

	void Explosion::Update(float dt)
	{
		for(int i=0;i<numParticles;i++)
		{
			particles[i].lifetime -= dt;
			particles[i].position = particles[i].position + particles[i].velocity * dt;
		}
	}

	void Explosion::Draw(Core::Graphics& g)
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
};

#endif