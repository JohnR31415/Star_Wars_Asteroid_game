#pragma once
#ifndef PARTICLEEFFECTS
#define PARTICLEEFFECTS
#include "Particle.h"
#include "..\Math\Random.h"
#include "..\Particle\Color.h"
#include "Core.h"

#include "..\Debug\DebugMemory.h"

class ParticleEffects
{
public:
	int numParticles;
	float lifetime;
	Particle* particles;
	Vector3D origin;
	Random rand;
	ParticleEffects(int numOfParticles = 0, Vector3D position = Vector3D(), RGB color = RGB(255, 255, 255))
	{

		numParticles = numOfParticles;
		particles = new Particle[numParticles];
		origin = position;
		lifetime = 2.0f;
		for(int i=0;i<numParticles;i++)
		{
			particles[i].position = position;
			particles[i].velocity = rand.randomVector() * rand.randomInRange(5, 500);
			particles[i].color = varColor(color, 10);
			particles[i].lifetime = rand.randomInRange(1, 3);
			particles[i].scalar = 1;
		}
	}

	virtual ~ParticleEffects()
	{
		delete [] particles;
	}

	virtual void Update(float dt)
	{
		for(int i=0;i<numParticles;i++)
		{
			particles[i].lifetime -= dt;
			particles[i].position = particles[i].position + particles[i].velocity * dt;
		}
		lifetime -= dt;
	}

	virtual void Draw(Core::Graphics& g)
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