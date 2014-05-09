#pragma once
#ifndef HEALTHBAR
#define HEALTHBAR

#include "Core.h"
#include "Math\Vector3D.h"
#include "Math\Matrix3D.h"

class Healthbar
{
private:
	Vector3D* healthLines;
	float currentHealth;
	int healthBarCount;
	float scalar;
public:
	Vector3D position;
	Matrix3D matrix;

	Healthbar() { }

	~Healthbar() 
	{
		delete [] healthLines;
	}
	void Initialize()
	{
		healthBarCount = 100;
		currentHealth = 100.0f;
		scalar = 0.5;
		healthLines = new Vector3D[healthBarCount];

		for(int i=0;i < healthBarCount;i++)
		{
			healthLines[i] = Vector3D((float)i + 1, 1.0f);
		}
		position = Vector3D();
		matrix = Matrix3D();
	}

	void Draw(Core::Graphics& g)
	{
		g.SetColor(RGB(255, 0, 0));
		float atLeastOneBar = currentHealth;
		if(currentHealth < 1  && currentHealth > 0)
			atLeastOneBar = 1.0f;

		for(int i = 0;i < atLeastOneBar; i++)
		{
			Vector3D currentPoint = Vector3D(healthLines[i].x, healthLines[i].y) * scalar;
			Vector3D nextPoint = Vector3D(healthLines[i].x, 11) * scalar;

			const Vector3D& p1 = matrix * currentPoint + position;
			const Vector3D& p2 = matrix * nextPoint + position;

			g.DrawLine(p1.x, p1.y, p2.x, p2.y);
		}
	}

	void Update(float dt)
	{
		dt;
	}

	void removeHealth(float damage)
	{
		currentHealth -= damage;
	}

	void setHealth(float health)
	{
		currentHealth = health;
	}
};

#endif