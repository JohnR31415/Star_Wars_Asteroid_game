#ifndef LAZERBLAST
#define LAZERBLAST
#include "Math\Vector3D.h"
#include "Core.h"
#include "Particle\ParticleEffects.h"
using Core::RGB;

class LazerBlast 
	: public ParticleEffects
{
public:
	bool explode;
	LazerBlast::LazerBlast(Vector3D start, float min, float max) 
		: ParticleEffects(100, start, RGB(135, 50, 50))
	{
		min;
		max;
		for(int i=0;i<numParticles;i++)
		{
			particles[i].velocity = rand.randomVector() * rand.randomInRange(min, max);
			particles[i].color = varColor(particles[i].color, 100);
			particles[i].lifetime = rand.randomInRange(0.5f, 1.0f);
			particles[i].scalar = 1;
		}
		explode = false;
	}
	LazerBlast()
	{
		explode = false;
	}

	void LazerBlast::Update(float dt)
	{
		for(int i=0;i<numParticles;i++)
		{
			particles[i].lifetime -= dt;
			particles[i].position = particles[i].position + particles[i].velocity * dt;
		}
		updateExploded();
	}

	void LazerBlast::Draw(Core::Graphics& g)
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

	void updateOrigin(Vector3D newPosition)
	{
		origin = newPosition;
		for(int i=0;i<numParticles;i++)
		{
			particles[i].position = newPosition;
		}
	}

	void updateExploded()
	{
		float largestAlive = -999.0f;
		for(int i=0;i<numParticles;i++)
			if(particles[i].lifetime > largestAlive)
				largestAlive = particles[i].lifetime;
		if(largestAlive < 0)
		{
			explode = false;
		}
			
	}
};

#endif