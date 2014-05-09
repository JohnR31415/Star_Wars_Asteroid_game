#ifndef GLOBAL
#define GLOBAL

#include <vector>
#include <sstream>

#include "Core.h"
#include "Particle\ParticleEffects.h"
#include "Timing\Timer.h"
#include "Base\Ship.h"
#include "Base\Projectile.h"
#include "Base\Obstacle.h"

#include "Debug\DebugMemory.h"

enum GameState
{
	MENU,
	GAME,
	END
};

extern int screenWidth;
extern int screenHeight;
extern int score;
extern int finalScore;
extern GameState state;

extern const char* message;
extern bool isValidShip;
extern bool keepSpawningEnemies;
extern int obstacleRespawnCounter;

extern std::stringstream stream;

extern Timer t;


extern Ship* playerShip;
extern std::vector<Ship*> enemies;

extern std::vector<Projectile*> projectiles;
extern std::vector<Projectile*> enemyProjectiles;

extern std::vector<Obstacle*> obstacles;
extern std::vector<Obstacle*> chunks;

extern std::vector<ParticleEffects*> explosions;

static Vector3D topSpawn[] =
{
	Vector3D(100.0f, -100.0f),
	Vector3D(200.0f, -100.0f),
	Vector3D(300.0f, -100.0f),
	Vector3D(400.0f, -100.0f),
	Vector3D(500.0f, -100.0f),
	Vector3D(600.0f, -100.0f),
	Vector3D(700.0f, -100.0f),
	Vector3D(800.0f, -100.0f),
	Vector3D(900.0f, -100.0f),
	Vector3D(1000.0f, -100.0f),
	Vector3D(1100.0f, -100.0f),
	Vector3D(1200.0f, -100.0f),
	Vector3D(1300.0f, -100.0f),
	Vector3D(1400.0f, -100.0f),
	Vector3D(1500.0f, -100.0f),

};
static Vector3D bottomSpawn[] =
{
	Vector3D(100.0f, 900.0f),
	Vector3D(200.0f, 900.0f),
	Vector3D(300.0f, 900.0f),
	Vector3D(400.0f, 900.0f),
	Vector3D(500.0f, 900.0f),
	Vector3D(600.0f, 900.0f),
	Vector3D(700.0f, 900.0f),
	Vector3D(800.0f, 900.0f),
	Vector3D(900.0f, 900.0f),
	Vector3D(1000.0f, 900.0f),
	Vector3D(1100.0f, 900.0f),
	Vector3D(1200.0f, 900.0f),
	Vector3D(1300.0f, 900.0f),
	Vector3D(1400.0f, 900.0f),
	Vector3D(1500.0f, 900.0f),
};
static Vector3D leftSpawn[] =
{
	Vector3D(-100.0f, 100.0f),
	Vector3D(-100.0f, 200.0f),
	Vector3D(-100.0f, 300.0f),
	Vector3D(-100.0f, 400.0f),
	Vector3D(-100.0f, 500.0f),
	Vector3D(-100.0f, 600.0f),
	Vector3D(-100.0f, 700.0f),
	Vector3D(-100.0f, 800.0f),
};
static Vector3D rightSpawn[] =
{
	Vector3D(1700.0f, 100.0f),
	Vector3D(1700.0f, 200.0f),
	Vector3D(1700.0f, 300.0f),
	Vector3D(1700.0f, 400.0f),
	Vector3D(1700.0f, 500.0f),
	Vector3D(1700.0f, 600.0f),
	Vector3D(1700.0f, 700.0f),
	Vector3D(1700.0f, 800.0f),
};

#endif