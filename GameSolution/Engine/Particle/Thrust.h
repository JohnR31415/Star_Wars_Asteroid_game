#ifndef THRUST
#define THRUST
#include "Math\Vector3D.h"
#include "Core.h"
#include "Particle\ParticleEffects.h"
using Core::RGB;

class Thrust
	: public ParticleEffects
{
public:
	bool expelled;
	bool forwards;
	Vector3D direction;
	Matrix3D matrix;
	Thrust::Thrust(Vector3D start, float min, float max)
		: ParticleEffects(1000, start, RGB(128, 255, 255))
	{
		start;
		min;
		max;
		for(int i=0;i<numParticles;i++)
		{
			particles[i].velocity = Vector3D(0, 0, 0);
			particles[i].color = varColor(particles[i].color, 50);
			particles[i].lifetime = 0.0f;
		}
		expelled = false;
	}

	Thrust()
	{
		expelled = false;
	}

	void Thrust::Fire(Vector3D direction)
	{
		direction;
		expelled = true;
	}

	void Thrust::Update(float dt)
	{
		for(int i=0;i<numParticles;i++)
		{
			particles[i].lifetime -= dt;
			//if the particle is dead and the ship is thrusting
			//refresh
			if(particles[i].lifetime < 0 && expelled)
			{
				
				particles[i].velocity = rand.random45Vector() * rand.randomInRange(100, 200);
				if(forwards)
					particles[i].velocity = matrix * particles[i].velocity;
				else
					particles[i].velocity = matrix * particles[i].velocity.perpCW().perpCW();
				particles[i].position = origin;
				particles[i].lifetime = rand.randomInRange(1.0f, 3.0f);
				particles[i].color = varColor(RGB(128, 255, 255), 50);
			}
			else if(particles[i].lifetime < 0)
			{
				particles[i].color = varColor(RGB(128, 255, 255), 50);
				particles[i].position = Vector3D(-500, -500, 0);
				particles[i].velocity = Vector3D(-10, -10, 0);
				particles[i].lifetime = rand.randomInRange(1.0f, 3.0f);
			}
			else
				particles[i].position = particles[i].position + particles[i].velocity * dt;

		}
		//updateExpelled();
	}
	

	void Thrust::Draw(Core::Graphics& g)
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

	void updateExpelled()
	{
		float largestAlive = -999.0f;
		for(int i=0;i<numParticles;i++)
			if(particles[i].lifetime > largestAlive)
				largestAlive = particles[i].lifetime;
		if(largestAlive < 0)
		{
			expelled = false;
		}
	}
};

#endif