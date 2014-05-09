#include "RebelLazer.h"

Vector3D RebelLazerPoints[] =
{
	Vector3D(+1.0f, +4.0f),
	Vector3D(+1.0f, -4.0f),
	Vector3D(-1.0f, -4.0f),
	Vector3D(-1.0f, +4.0f),
};

RebelLazer::RebelLazer()
{
}
RebelLazer::~RebelLazer()
{
}

void RebelLazer::Initialize(Vector3D pos, Vector3D vel, Matrix3D mat)
{
	isSpawned = false;
	isDead = false;
	isPlayer = false;

	contactRadius = 10.0f;
	health = 0;
	totalHealth = 0;
	armor = 0;
	mass = 0;
	lifetime = 2.0f;

	rotation = 0;
	scalar = 1;
	acceleration = 0;
	turnSpeed = 0;

	entityName = "Rebel Lazer";

	color.r = 255;
	color.g = 1;
	color.b = 1;
	hb.Initialize();

	direction = Vector3D(0, 1);
	position = pos;
	velocity = vel;

	matrix = mat;

	type = RL;
	isFired = true;
	hit = false;
	
	damage = 100.0f;
}

void RebelLazer::Draw(Core::Graphics& g)
{
	g;
	if(isFired)
	{
		g.SetColor(RGB(color.r, color.g, color.b));
		const unsigned int NUM_POINTS = sizeof(RebelLazerPoints) / sizeof(*RebelLazerPoints);
		for(unsigned int i = 0;i< NUM_POINTS;i++)
		{
			Vector3D currentPoint = Vector3D(RebelLazerPoints[i].x, RebelLazerPoints[i].y) * scalar;
			Vector3D nextPoint = Vector3D(RebelLazerPoints[(i+1) % NUM_POINTS].x, RebelLazerPoints[(i+1) % NUM_POINTS].y) * scalar;

			const Vector3D& p1 = matrix * currentPoint + position;
			const Vector3D& p2 = matrix * nextPoint + position;

			g.DrawLine(p1.x, p1.y, p2.x, p2.y);
		}
	}
}
void RebelLazer::Update(float dt)
{
	dt;
	if(isFired)
	{
		position = position + velocity;

		for(unsigned int i=0;i<obstacles.size();i++)
		{
			float distance = pow(obstacles[i]->position.x - position.x, 2) + pow(position.y - obstacles[i]->position.y, 2);
			float radius = pow((contactRadius * scalar) + (obstacles[i]->contactRadius * obstacles[i]->scalar), 2);
			if(distance <= radius && !obstacles[i]->isDead && !isDead)
			{
				if(DamageEntity(obstacles[i], damage))
				{
					obstacles[i]->Explode();
					score += (int)obstacles[i]->scalar;
				}	
				Explode();
			}
		}

		Collide();
		lifetime -= dt;
	}
}

void RebelLazer::Collide()
{
	if(position.x > screenWidth || position.x < 5 || position.y > screenHeight || position.y < 5)
	{
		Explode();
	}
}
bool RebelLazer::DamageEntity(GameEntity* entity, float damage)
{
	entity;
	damage;
	float adjustedDamage = sqrt(pow((damage * entity->armor),2));
	entity->health -= adjustedDamage;
	float adjustedRatioDamage = (adjustedDamage * 100) / entity->totalHealth;
	entity->hb.removeHealth(adjustedRatioDamage);
	if(entity->health <= 0)
		return true;
	return false;
}
void RebelLazer::Explode()
{
	isFired = false;
	hit = true;
	lifetime = 0;
	velocity = Vector3D();

	Vector3D adjustedPosition;

	if(position.x > screenWidth)
		adjustedPosition.x = (float)screenWidth;
	else if(position.x < 0)
		adjustedPosition.x = 0;
	else
		adjustedPosition.x = position.x;
	if(position.y > screenWidth)
		adjustedPosition.y = (float)screenHeight;
	else if(position.y < 0)
		adjustedPosition.y = 0;
	else
		adjustedPosition.y = position.y;

	explosions.push_back(new RebelLazerBlast(adjustedPosition, 50, 200));
}