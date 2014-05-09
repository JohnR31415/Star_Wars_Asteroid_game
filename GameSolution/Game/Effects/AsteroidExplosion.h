#pragma once
#ifndef ASTEROIDEXPLOSION
#define ASTEROIDEXPLOSION

#include "Particle\ParticleEffects.h"

static Vector3D OctogonPoints[] =
{
	Vector3D(1.0f, 2.0f),
	Vector3D(2.0f, 1.0f),
	Vector3D(2.0f, -1.0f),
	Vector3D(1.0f, -2.0f),
	Vector3D(-1.0f, -2.0f),
	Vector3D(-2.0f, -1.0f),
	Vector3D(-2.0f, 1.0f),
	Vector3D(-1.0f, 2.0f),
};

class AsteroidExplosion
	: public ParticleEffects
{
public:
	AsteroidExplosion::AsteroidExplosion(Vector3D start, float min, float max)
		: ParticleEffects(500, start, RGB(200, 100, 0))
	{
		min;
		max;
		lifetime = 2.0f;
		for(int i=0;i<numParticles;i++)
		{
			particles[i].velocity = rand.randomVector() * rand.randomInRange(min, max);
			particles[i].color = varColor(particles[i].color, 50);
			particles[i].lifetime = rand.randomInRange(1.0f, 2.0f);
			particles[i].scalar = 1;
		}
	}

	void AsteroidExplosion::Draw(Core::Graphics& g)
	{
		if(lifetime > 0)
		{
			for(int i=0;i<numParticles;i++)
			{
				if(particles[i].lifetime > 0)
				{
					g.SetColor(particles[i].color);
					Vector3D p1 = particles[i].position;
					Vector3D p2 = particles[i].position + Vector3D(0, 1, 0);
					g.DrawLine(p1.x, p1.y, p2.x, p2.y);
				}
				if(particles[i].lifetime < 1)
				{
					particles[i].color = brightness(particles[i].color, particles[i].lifetime);
				}
			}
		}
	}

	void AsteroidExplosion::Update(float dt)
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

class AsteroidChunks
	: public ParticleEffects
{
public:
	int type;
	AsteroidChunks::AsteroidChunks(Vector3D start, float min, float max)
		: ParticleEffects(25, start, RGB(200, 100, 0))
	{
		min;
		max;
		lifetime = 3.0f;
		for(int i=0;i<numParticles;i++)
		{
			particles[i].velocity = rand.randomVector() * rand.randomInRange(min, max);
			particles[i].color = varColor(particles[i].color, 50);
			particles[i].lifetime = rand.randomInRange(1.5f, 3.0f);
			particles[i].scalar = (float)(std::rand() % 5);
		}
	}
	void AsteroidChunks::Draw(Core::Graphics& g)
	{
		if(lifetime > 0)
		{
			for(int i=0;i<numParticles;i++)
			{
				if(particles[i].lifetime > 0)
				{
					g.SetColor(particles[i].color);
					const unsigned int NUM_POINTS = sizeof(OctogonPoints) / sizeof(*OctogonPoints);
					for(unsigned int j = 0;j< NUM_POINTS;j++)
					{
						Vector3D currentPoint = Vector3D(OctogonPoints[j].x, OctogonPoints[j].y) * particles[i].scalar;
						Vector3D nextPoint = Vector3D(OctogonPoints[(j+1) % NUM_POINTS].x, OctogonPoints[(j+1) % NUM_POINTS].y) * particles[i].scalar;

						const Vector3D& p1 = currentPoint + particles[i].position;
						const Vector3D& p2 = nextPoint + particles[i].position;

						g.DrawLine(p1.x, p1.y, p2.x, p2.y);
					}
				}
				if(particles[i].lifetime < 1)
				{
					particles[i].color = brightness(particles[i].color, particles[i].lifetime);
				}
			}
		}
	}

	void AsteroidChunks::Update(float dt)
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