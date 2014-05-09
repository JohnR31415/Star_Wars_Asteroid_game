#include "XWing.h"

Vector3D XWingPoints[] =
{
	Vector3D(0.0f, 94.0f),

	Vector3D(2.0f, 94.0f),
	Vector3D(4.0f, 91.0f),
	Vector3D(7.0f, 88.0f),
	Vector3D(13.0f, -32.0f),
	Vector3D(17.0f, -32.0f),
	Vector3D(17.0f, -29.0f),
	Vector3D(31.0f, -29.0f),
	Vector3D(31.0f, -35.0f),
	Vector3D(74.0f, -35.0f),
	Vector3D(74.0f, -32.0f),
	Vector3D(77.0f, -32.0f),
	Vector3D(77.0f, +19.0f),
	Vector3D(74.0f, +19.0f),
	Vector3D(74.0f, +21.0f),
	Vector3D(77.0f, +21.0f),
	Vector3D(77.0f, +34.0f),
	Vector3D(79.0f, +34.0f),
	Vector3D(79.0f, +21.0f),
	Vector3D(82.0f, +21.0f),
	Vector3D(82.0f, +19.0f),
	Vector3D(79.0f, +19.0f),
	Vector3D(79.0f, -32.0f),
	Vector3D(82.0f, -32.0f),
	Vector3D(82.0f, -70.0f),
	Vector3D(74.0f, -70.0f),
	Vector3D(74.0f, -61.0f),
	Vector3D(71.0f, -61.0f),
	Vector3D(34.0f, -73.0f),
	Vector3D(28.0f, -73.0f),
	Vector3D(28.0f, -91.0f),
	Vector3D(20.0f, -91.0f),
	Vector3D(20.0f, -73.0f),
	Vector3D(16.0f, -73.0f),
	Vector3D(16.0f, -76.0f),
	Vector3D(13.0f, -79.0f),
	
	Vector3D(0.0f, -79.0f),
};

XWing::XWing()
{
}
XWing::~XWing()
{
	delete [] engines;
	delete [] barrels;
}
void XWing::Initialize()
{
	isSpawned = false;
	isDead = false;
	isPlayer = false;

	contactRadius = 82.0f;
	health = 100.0f;
	totalHealth = health;
	armor = 0.8f;
	mass = 0.05f;
	lifetime = 10.0f;

	rotation = 0;
	scalar = 1;
	acceleration = 40.0f;
	turnSpeed = 0.25f;

	entityName = "X-Wing";

	color.r = 255;
	color.g = 255;
	color.b = 255;
	hb.Initialize();

	direction = Vector3D(0, 1);
	position = Vector3D();
	velocity = Vector3D();
	matrix = Matrix3D();

	type = XW;
	mode = ALT;

	engines = new Vector3D[2];
	barrels = new Vector3D[2];
	barrels[0] = Vector3D(78, 34);
	barrels[1] = Vector3D(-78, 34);

	currentBarrel = 0;
	barrelCount = 2;

	bombLastFrame = false;
	cannonLastFrame = false;
	lazerLastFrame = false;
	missleLastFrame = false;
	torpedoLastFrame = false;

	bombCooldown = 0;
	cannonCooldown = 0;
	lazerCooldown = 0;
	missleCooldown = 0;
	torpedoCooldown = 0;

	startBombCooldown = false;
	startCannonCooldown = false;
	startLazerCooldown = false;
	startMissleCooldown = false;
	startTorpedoCooldown = false;

	bombFrequency = 3.0f;
	cannonFrequency = 0.5f;
	lazerFrequency = 0.1f;
	missleFrequency = 1.0f;
	torpedoFrequency = 2.0f;

	shieldRadius = 1.0f;
	hasAstromechDroid = true;
}

void XWing::Draw(Core::Graphics& g)
{
	g;
	if(!isDead)
	{
		const unsigned int NUM_POINTS = sizeof(XWingPoints) / sizeof(*XWingPoints);
		for(unsigned int i = 0;i < NUM_POINTS - 1;i++)
		{
			Vector3D currentPoint = Vector3D(XWingPoints[i].x, XWingPoints[i].y) * scalar;
			Vector3D nextPoint = Vector3D(XWingPoints[(i+1) % NUM_POINTS].x, XWingPoints[(i+1) % NUM_POINTS].y) * scalar;

			const Vector3D& p1 = matrix * currentPoint + position;
			const Vector3D& p2 = matrix * nextPoint + position;

			g.DrawLine(p1.x, p1.y, p2.x, p2.y);
		}
		for(unsigned int i = NUM_POINTS - 1;i > 0;i--)
		{
			Vector3D currentPoint = Vector3D(-XWingPoints[i].x, XWingPoints[i].y) * scalar;
			Vector3D nextPoint = Vector3D(-XWingPoints[(i-1) % NUM_POINTS].x, XWingPoints[(i-1) % NUM_POINTS].y) * scalar;

			const Vector3D& p1 = matrix * currentPoint + position;
			const Vector3D& p2 = matrix * nextPoint + position;

			g.DrawLine(p1.x, p1.y, p2.x, p2.y);
		}
		if(state == GAME)
		{
			hb.Draw(g);
		}
	}
}

void XWing::Update(float dt)
{
	dt;
	if(state == GAME && isPlayer)
	{
		if(Core::Input::IsPressed(Core::Input::KEY_RIGHT) || Core::Input::IsPressed(0x44))
			rotation += dt * turnSpeed;
		if(Core::Input::IsPressed(Core::Input::KEY_LEFT) || Core::Input::IsPressed(0x41))
			rotation -= dt * turnSpeed;
		matrix = matrix * rotate(rotation);

		if(Core::Input::IsPressed(Core::Input::KEY_UP) || Core::Input::IsPressed(0x57))
		{
			velocity = velocity + (matrix * direction * acceleration) * dt;
			/*thrust.expelled = true;
			thrust.origin = matrix * engine + position;
			thrust.forwards = true;
			thrust.matrix = matrix;*/
		}
		if(Core::Input::IsPressed(Core::Input::KEY_DOWN) || Core::Input::IsPressed(0x53))
		{
			velocity = velocity - (matrix * direction * acceleration) * dt;
			/*thrust.expelled = true;
			thrust.origin = matrix * engine + position;
			thrust.forwards = false;
			thrust.matrix = matrix;*/
		}

		if(hasAstromechDroid)
		{
			rotation = rotation * .92f;
			velocity = velocity * .95f;
		}
		if(bombCooldown >= bombFrequency && startBombCooldown)
		{
			bombLastFrame = false;
			bombCooldown = 0;
			startBombCooldown = false;
		}
		else if(bombCooldown < bombFrequency && startBombCooldown)
			bombCooldown += dt;

		if(lazerCooldown >= lazerFrequency && startLazerCooldown)
		{
			lazerLastFrame = false;
			lazerCooldown = 0;
			startLazerCooldown = false;
		}
		else if(lazerCooldown < lazerFrequency && startLazerCooldown)
			lazerCooldown += dt;

		if(missleCooldown >= missleFrequency && startMissleCooldown)
		{
			missleLastFrame = false;
			missleCooldown = 0;
			startMissleCooldown = false;
		}
		else if(missleCooldown < missleFrequency && startMissleCooldown)
			missleCooldown += dt;

		if(torpedoCooldown >= torpedoFrequency && startTorpedoCooldown)
		{
			torpedoLastFrame = false;
			torpedoCooldown = 0;
			startTorpedoCooldown = false;
		}
		else if(torpedoCooldown < torpedoFrequency && startTorpedoCooldown)
			torpedoCooldown += dt;

		if(Core::Input::IsPressed(Core::Input::BUTTON_LEFT) && !lazerLastFrame)
		{
			ShootLazer();
			lazerLastFrame = true;
			startLazerCooldown = true;
		}
		if(Core::Input::IsPressed(Core::Input::BUTTON_RIGHT) && !torpedoLastFrame)
		{
			ShootTorpedo();
			torpedoLastFrame = true;
			startTorpedoCooldown = true;
		}

		//Old collision code where playership checks against all asteroids, now in asteroid code.
		/*for(unsigned int i=0;i<obstacles.size();i++)
		{
			float distance = pow(obstacles[i]->position.x - position.x, 2) + pow(position.y - obstacles[i]->position.y, 2);
			float radius = pow((contactRadius * scalar) + (obstacles[i]->contactRadius * obstacles[i]->scalar), 2);
			if(distance <= radius && !obstacles[i]->isDead && !isDead)
			{
				Bounce(obstacles[i]);
				float damage1 = 0.5f * mass * velocity.Length();
				float damage2 = 0.5f * obstacles[i]->mass * obstacles[i]->velocity.Length();
				if(DamageEntity(obstacles[i], damage1))
					obstacles[i]->Explode();
				if(DamageEntity(this, damage2))
					Explode();
			}
		}*/
		position = position + velocity;
		BounceOffScreen();
		hb.position = Vector3D(position.x - 25, position.y + 65);
		hb.Update(dt);
	}
	else if(state == GAME && !isPlayer)
	{
	}
	else if(state == MENU)
	{
		matrix = matrix * rotate(rotation);
	}
}

void XWing::Spawn()
{
}
void XWing::Collide()
{
}
void XWing::Bounce(GameEntity* entity)
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
void XWing::BounceOffScreen()
{
	if(position.x > screenWidth)
	{
		velocity.x *= -1;
		position.x = (float)screenWidth - 1;
	}
	if(position.x < 0)
	{
		velocity.x *= -1;
		position.x = 1;
	}
	if(position.y > screenHeight)
	{
		velocity.y *= -1;
		position.y = (float)screenHeight - 1;
	}
	if(position.y < 0)
	{
		velocity.y *= -1;
		position.y = 1;
	}
}
bool XWing::DamageEntity(GameEntity* entity, float damage)
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
void XWing::Explode()
{
	explosions.push_back(new XWingExplosion(position, 1, 100, true, 1000));
	isDead = true;
	lifetime = 0;
	if(isPlayer)
	{
		state = END;
		keepSpawningEnemies = false;
		finalScore = score;
		health = 0;
	}
}

void XWing::ShootLazer()
{
	Vector3D barrel;
	barrel = barrels[currentBarrel];
	Vector3D shotOrigin = matrix * (Vector3D(barrel.x, barrel.y) * scalar) + position;
	Vector3D shotVelocity = matrix * 25;
	projectiles.push_back(new RebelLazer());
	projectiles.back()->Initialize( shotOrigin, shotVelocity.perpCW(), matrix);
	currentBarrel = ((currentBarrel + 1) % barrelCount);
}
void XWing::ShootMissle()
{
}
void XWing::ShootTorpedo()
{
	Vector3D shotOrigin = matrix * (Vector3D(0, 8) * scalar) + position;
	Vector3D shotVelocity = matrix * 8;
	projectiles.push_back(new RebelTorpedo());
	projectiles.back()->Initialize(shotOrigin, shotVelocity.perpCW(), matrix);
}
void XWing::ShootCannon()
{
}
void XWing::Display(float dt)
{
	scalar = 1;
	position = Vector3D(800, 450);
	rotation = 1.0f * dt;
}

void XWing::ReadyForGame()
{
	matrix = Matrix3D();
	matrix = rotate(DegreesToRadians(180));
	scalar = 0.5;
	position = Vector3D(800, 450);
	rotation = 0;
	hasAstromechDroid = true;
}