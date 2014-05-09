#include "Asteroid.h"

Vector3D AsteroidPoints[] =
{
	Vector3D(1.0f, 7.0f),
	Vector3D(2.0f, 6.5f),
	Vector3D(5.0f, 5.5f),
	Vector3D(6.5f, 3.0f),
	Vector3D(7.0f, 1.5f),
	Vector3D(8.0f, 0.0f),

	Vector3D(8.5f, -3.0f),
	Vector3D(8.0f, -3.0f),
	Vector3D(7.0f, -4.0f),
	Vector3D(5.5f, -4.5f),
	Vector3D(2.0f, -8.0f),
	Vector3D(1.5f, -8.5f),
	Vector3D(0.0f, -8.0f),

	Vector3D(-2.5f, -8.0f),
	Vector3D(-3.5f, -7.5f),
	Vector3D(-4.0f, -6.5f),
	Vector3D(-5.5f, -6.5f),
	Vector3D(-7.0f, -5.5f),
	Vector3D(-8.5f, -3.0f),
	Vector3D(-8.5f, -1.5f),
	Vector3D(-8.0f, 0.0f),

	Vector3D(-7.0f, 1.5f),
	Vector3D(-7.0f, 3.5f),
	Vector3D(-7.5f, 4.5f),
	Vector3D(-7.0f, 5.5f),
	Vector3D(-6.5f, 7.0f),
	Vector3D(-5.0f, 8.0f),
	Vector3D(-3.0f, 8.5f),
	Vector3D(0.0f, 8.0f),
};

Vector3D ChunkPoints[] = 
{
	Vector3D(3.0f, 3.0f),
	Vector3D(3.0f, -3.0f),
	Vector3D(-3.0f, -3.0f),
	Vector3D(-3.0f, 3.0f),
};

int getAdjustedRandom()
{
	int randomInt = (rand() % 40) + 1;
	if(randomInt == 40)
		return 16;
	else if(randomInt == 39)
		return 15;
	else if(randomInt == 38)
		return 14;
	else if(randomInt == 37)
		return 13;
	else if(randomInt <= 36 && randomInt >= 35)
		return 12;
	else if(randomInt <= 34 && randomInt >= 33)
		return 11;
	else if(randomInt <= 32 && randomInt >= 31)
		return 10;
	else if(randomInt <= 30 && randomInt >= 29)
		return 9;
	else if(randomInt <= 28 && randomInt >= 26)
		return 8;
	else if(randomInt <= 25 && randomInt >= 23)
		return 7;
	else if(randomInt <= 22 && randomInt >= 20)
		return 6;
	else if(randomInt <= 19 && randomInt >= 17)
		return 5;
	else if(randomInt <= 16 && randomInt >= 13)
		return 4;
	else if(randomInt <= 12 && randomInt >= 9)
		return 3;
	else if(randomInt <= 8 && randomInt >= 5)
		return 2;
	else return 1;
}

Asteroid::Asteroid()
{
}
Asteroid::~Asteroid()
{
}

void Asteroid::Initialize()
{
	isSpawned = false;
	isDead = false;
	isPlayer = false;

	int randomInt = getAdjustedRandom();

	contactRadius = 8.0f;
	health = 100.0f * (float)randomInt;
	totalHealth = health;
	armor = 0.2f;
	mass = (float)randomInt;
	lifetime = 10.0f;

	rotation = 0;
	scalar = (float)randomInt;
	acceleration = 0.2f;
	turnSpeed = 0.2f;

	entityName = "Asteroid";

	color.r = 200;
	color.g = 100;
	color.b = 0;
	hb.Initialize();

	direction = Vector3D(0, 1);
	position = Vector3D();
	velocity = Vector3D();
	matrix = Matrix3D();
}
void Asteroid::Initialize2(Vector3D pos, Vector3D vec, float scale)
{
	isSpawned = true;
	isDead = false;
	isPlayer = false;

	contactRadius = 8.0f;
	health = 100.0f * scale;
	totalHealth = health;
	armor = 0.2f;
	mass = scale;
	lifetime = 10.0f;

	rotation = 0;
	scalar = scale;
	acceleration = 0.2f;
	turnSpeed = 0.2f;

	entityName = "Asteroid";

	color.r = 200;
	color.g = 100;
	color.b = 0;
	hb.Initialize();

	direction = Vector3D(0, 1);
	position = pos;
	velocity = vec;
	matrix = Matrix3D();
}

void Asteroid::Draw(Core::Graphics& g)
{
	g;
	if(lifetime > 0 && !isDead)
	{
		g.SetColor(RGB(color.r, color.g, color.b));
		const unsigned int NUM_POINTS = sizeof(AsteroidPoints) / sizeof(*AsteroidPoints);
		for(unsigned int i = 0;i< NUM_POINTS;i++)
		{
			Vector3D currentPoint = AsteroidPoints[i] * scalar;
			Vector3D nextPoint = AsteroidPoints[(i+1) % NUM_POINTS] * scalar;

			const Vector3D& p1 = matrix * currentPoint + position;
			const Vector3D& p2 = matrix * nextPoint + position;

			g.DrawLine(p1.x, p1.y, p2.x, p2.y);
		}
		hb.Draw(g);
	}
}
void Asteroid::Update(float dt)
{
	dt;
	if(lifetime > 0 && !isDead)
	{
		for(unsigned int i=0;i<obstacles.size();i++)
		{
			if(obstacles[i] != this)
			{
				float distance = pow(obstacles[i]->position.x - position.x, 2) + pow(position.y - obstacles[i]->position.y, 2);
				float radius = pow((contactRadius * scalar) + (obstacles[i]->contactRadius * obstacles[i]->scalar), 2);
				if(distance <= radius && !obstacles[i]->isDead && !isDead)
				{
					Bounce(obstacles[i]);
					if(position.x > 0 && position.x <= screenWidth && position.y > 0 && position.y <= screenHeight)
					{
						Bounce(obstacles[i]);
						float damage1 = 0.5f * mass * velocity.Length();
						float damage2 = 0.5f * obstacles[i]->mass * obstacles[i]->velocity.Length();
						if(DamageEntity(obstacles[i], damage1))
							obstacles[i]->Explode();
						if(DamageEntity(this, damage2))
							Explode();
					}
				}
			}
		}

		float distance = pow(playerShip->position.x - position.x, 2) + pow(position.y - playerShip->position.y, 2);
		float radius = pow((contactRadius * scalar) + (playerShip->contactRadius * playerShip->scalar), 2);
		if(distance <= radius && !playerShip->isDead && !isDead)
		{
			Bounce(playerShip);
			float damage1 = 0.5f * mass * velocity.Length();
			float damage2 = 0.5f * playerShip->mass * playerShip->velocity.Length();
			if(DamageEntity(playerShip, damage1))
				playerShip->Explode();
			if(DamageEntity(this, damage2))
				Explode();
		}

		position = position + velocity;
		hb.position = Vector3D(position.x - 25, position.y + (contactRadius * scalar) + 5);
		hb.Update(dt);
		if(position.x < 0 || position.x > screenWidth || position.y < 0 || position.y > screenHeight)
		{
			lifetime -= dt;
		}
	}
}

void Asteroid::Spawn()
{
	Random random = Random();
	int spawnNum = rand() % 4;
	Vector3D newPos;
	bool foundPosition = false;
	while(!foundPosition)
	{
		switch(spawnNum)
		{
		case 0:
			newPos = topSpawn[rand() % (sizeof(topSpawn) / sizeof(*topSpawn))];
			for(unsigned int i=0;i<obstacles.size();i++)
			{
				float distance = pow(obstacles[i]->position.x - newPos.x, 2) + pow(newPos.y - obstacles[i]->position.y, 2);
				float radius = pow((contactRadius * scalar) + (obstacles[i]->contactRadius * obstacles[i]->scalar), 2);
				if(distance > radius)
				{
					position = newPos;
					velocity = random.randomAngleVector(30) * random.randomInRange(1.0f, 2.0f);
					foundPosition = true;
				}
			}

			break;
		case 1:
			newPos = bottomSpawn[rand() % (sizeof(bottomSpawn) / sizeof(*bottomSpawn))];
			for(unsigned int i=0;i<obstacles.size();i++)
			{
				float distance = pow(obstacles[i]->position.x - newPos.x, 2) + pow(newPos.y - obstacles[i]->position.y, 2);
				float radius = pow((contactRadius * scalar) + (obstacles[i]->contactRadius * obstacles[i]->scalar), 2);
				if(distance > radius)
				{
					position = newPos;
					velocity = (random.randomAngleVector(30) * random.randomInRange(1.0f, 2.0f)).perpCW().perpCW();
					foundPosition = true;
				}
			}
			break;
		case 2:
			newPos = leftSpawn[rand() % (sizeof(leftSpawn) / sizeof(*leftSpawn))];
			for(unsigned int i=0;i<obstacles.size();i++)
			{
				float distance = pow(obstacles[i]->position.x - newPos.x, 2) + pow(newPos.y - obstacles[i]->position.y, 2);
				float radius = pow((contactRadius * scalar) + (obstacles[i]->contactRadius * obstacles[i]->scalar), 2);
				if(distance > radius)
				{
					position = newPos;
					velocity = (random.randomAngleVector(30) * random.randomInRange(1.0f, 2.0f)).perpCCW();
					foundPosition = true;
				}
			}
			break;
		case 3:
			newPos = rightSpawn[rand() % (sizeof(rightSpawn) / sizeof(*rightSpawn))];
			for(unsigned int i=0;i<obstacles.size();i++)
			{
				float distance = pow(obstacles[i]->position.x - newPos.x, 2) + pow(newPos.y - obstacles[i]->position.y, 2);
				float radius = pow((contactRadius * scalar) + (obstacles[i]->contactRadius * obstacles[i]->scalar), 2);
				if(distance > radius)
				{
					position = newPos;
					velocity = (random.randomAngleVector(30) * random.randomInRange(1.0f, 2.0f)).perpCW();
					foundPosition = true;
				}
			}
			break;
		}
	}
	isSpawned = true;
}
void Asteroid::Collide()
{
}
void Asteroid::Bounce(GameEntity* entity)
{
	entity;
	float m21 = entity->mass / mass;
	float x21 = entity->position.x - position.x;
	float y21 = entity->position.y - position.y;
	float vx21 = entity->velocity.x - velocity.x;
	float vy21 = entity->velocity.y - velocity.y;

	if((vx21 * x21 + vy21 * y21) >= 0)
		return;

	if(x21 == 0)
		x21 = 0.00000001f;
	float a = y21 / x21;
	float dvx2 = -2 * (vx21 + a * vy21) / ((1 + a * a) * (1 + m21));
	entity->velocity.x = entity->velocity.x + dvx2;
	entity->velocity.y = entity->velocity.y + a * dvx2;
	velocity.x = velocity.x - m21 * dvx2;
	velocity.y = velocity.y - a * m21 * dvx2;
}
bool Asteroid::DamageEntity(GameEntity* entity, float damage)
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
void Asteroid::Explode()
{
	float chunkScale = floor(scalar/3);
	Random random;
	if(chunkScale > 0)
	{
		for(int i=0;i<4;i++)
		{
			Vector3D mainPosition = ChunkPoints[i] * scalar;
			const Vector3D& p1 = (matrix * mainPosition) + position;
			//p1, velocity, chunkScale
			chunks.push_back(new Asteroid());
			Vector3D randomVector = (random.randomDirectionVector(velocity, 30.0f));
			chunks.back()->Initialize2(p1, randomVector, chunkScale);
		}
	}
	explosions.push_back(new AsteroidExplosion(position, 1, 200));
	if(chunkScale > 0)
		explosions.push_back(new AsteroidChunks(position, 100, 200));
	explosions.push_back(new AsteroidExplosion(position, 1, 200));
	isDead = true;
	lifetime = 0;
}

void Asteroid::Display(float dt)
{
	dt;
}
void Asteroid::ReadyForGame()
{
}