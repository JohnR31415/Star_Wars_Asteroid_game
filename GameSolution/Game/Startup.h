#pragma once
#ifndef STARTUP
#define STARTUP

#include "Core.h"
#include "Global.h"
#include "RebelShips\XWing\XWing.h"
#include "Obstacles\Asteroid\Asteroid.h"

#include "Profiling\Profiler.h"
#include "Profiling\Profile.h"

int screenWidth;
int screenHeight;
int score;
int finalScore;
GameState state;

const char* message;
bool isValidShip;
bool keepSpawningEnemies;
int obstacleRespawnCounter;

std::stringstream stream;

Timer t;


Ship* playerShip;
std::vector<Ship*> enemies;

std::vector<Projectile*> projectiles;
std::vector<Projectile*> enemyProjectiles;

std::vector<Obstacle*> obstacles;
std::vector<Obstacle*> chunks;

std::vector<ParticleEffects*> explosions;

class Startup
{
public:
	Startup() { }

	void Initialize()
	{
		screenWidth = 1600;
		screenHeight = 900;

		score = 0;
		finalScore = 0;
		state = MENU;

		playerShip = new XWing();
		playerShip->Initialize();
		isValidShip = true;

		message = "";
		keepSpawningEnemies = false;
		obstacleRespawnCounter = 0;
	}

	void ShipSelection()
	{
		if(Core::Input::IsPressed(49) && playerShip->type != AW)
		{
			//LOG(Info, "Switching ships to AWing");
			//delete playerShip;
			//playerShip = new AWing();
			playerShip->type = AW;
			message = "A-Wing currently unavailable.";
			isValidShip = false;
		}
		else if(Core::Input::IsPressed(50) && playerShip->type != XW)
		{
			//LOG(Info, "Switching ships to XWing");
			delete playerShip;
			playerShip = new XWing();
			playerShip->Initialize();
			message = "";
			isValidShip = true;
		}
		else if(Core::Input::IsPressed(51) && playerShip->type != BW)
		{
			//LOG(Info, "Switching ships to AWing");
			//delete playerShip;
			//playerShip = new AWing();
			playerShip->type = BW;
			message = "B-Wing currently unavailable.";
			isValidShip = false;
		}
		else if(Core::Input::IsPressed(52) && playerShip->type != YW)
		{
			//LOG(Info, "Switching ships to AWing");
			//delete playerShip;
			//playerShip = new AWing();
			playerShip->type = YW;
			message = "Y-Wing currently unavailable.";
			isValidShip = false;
		}
		else if(Core::Input::IsPressed(53) && playerShip->type != TF)
		{
			//LOG(Info, "Switching ships to AWing");
			//delete playerShip;
			//playerShip = new AWing();
			playerShip->type = TF;
			message = "TIE Fighter currently unavailable.";
			isValidShip = false;
		}
	}

	void spawnObstacles()
	{
		obstacleRespawnCounter = (obstacleRespawnCounter++ % 75);
		if(obstacleRespawnCounter == 1)
		{
			obstacles.push_back(new Asteroid());
			obstacles.back()->Initialize();
		}
		for(unsigned int i=0;i<obstacles.size();i++)
		{
			if(!obstacles[i]->isSpawned)
			{
				obstacles[i]->Spawn();
			}
		}
	}

	void spawnShips()
	{

	}

	void spawnEnemies()
	{
		spawnObstacles();
		spawnShips();
	}

	void DrawMenu(Core::Graphics& g)
	{
		g;
		PrintString(10, 10, "Press a number to switch ships.\n1: A-Wing\n2: X-Wing\n3: B-Wing\n4: Y-Wing", g);
		PrintString(10, 100, "To move press WSAD or the arrow keys.\nClick the left mouse button to fire.", g);
		PrintStringString(725, 10, "Current ship: ", playerShip->entityName, g);
		PrintString(10, 80, "Press enter to start.", g);

		if(isValidShip)
			playerShip->Draw(g);

		ShipSelection();
		if(strcmp(message, "") != 0)
			g.DrawString(725, 450, message);

		if(Core::Input::IsPressed(13))
		{
			if(!isValidShip)
			{
				delete playerShip;
				playerShip = new XWing();
				playerShip->Initialize();
			}

			playerShip->isPlayer = true;
			playerShip->ReadyForGame();
			keepSpawningEnemies = true;
			state = GAME;
		}
	}

	void DrawGame(Core::Graphics& g)
	{
		g;

		PrintStringAndNum(725, 10, "Health: ", playerShip->health, g);
		PrintStringAndNum(725, 25, "Score: ", (float)score, g);

		if(!playerShip->isDead)
			playerShip->Draw(g);
		//Profile ed("Enemy Draw");
		//PROFILE("Enemy Draw");
		for(unsigned int i=0;i<enemies.size();i++)
			enemies[i]->Draw(g);
		//Profile pd("Projectiles Draw");
		for(unsigned int i=0;i<projectiles.size();i++)
			projectiles[i]->Draw(g);
		//Profile epd("Enemy Projectiles Draw");
		for(unsigned int i=0;i<enemyProjectiles.size();i++)
			enemyProjectiles[i]->Draw(g);
		//Profile od("Obstacles Draw");
		for(unsigned int i=0;i<obstacles.size();i++)
			obstacles[i]->Draw(g);
		//Profile cd("Chunks Draw");
		for(unsigned int i=0;i<chunks.size();i++)
			chunks[i]->Draw(g);
		//Profile exd("Explosions Draw");
		for(unsigned int i=0;i<explosions.size();i++)
			explosions[i]->Draw(g);
		//Profile cpb("Chunks Pushback");
		for(unsigned int i = 0; i < chunks.size(); i++)
		{
			obstacles.push_back(new Asteroid());
			obstacles.back()->Initialize2(chunks[i]->position, chunks[i]->velocity, chunks[i]->scalar);
		}

		while(chunks.size() > 0)
		{
			delete chunks[0];
			chunks.erase(chunks.begin());
		}

		if(keepSpawningEnemies)
			spawnEnemies();
		//Profile end("End");
	}

	void DrawEnd(Core::Graphics& g)
	{
		PrintStringAndNum(725, 10, "Health: ", playerShip->health, g);
		PrintString(725, 450, "Game Over!", g);
		PrintStringAndNum(725, 465, "Final Score: ", (float)finalScore, g);
		PrintString(725, 480, "Press backspace to go back to the menu.", g);
		for(unsigned int i=0;i<enemies.size();i++)
			enemies[i]->Draw(g);
		for(unsigned int i=0;i<projectiles.size();i++)
			projectiles[i]->Draw(g);
		for(unsigned int i=0;i<enemyProjectiles.size();i++)
			enemyProjectiles[i]->Draw(g);
		for(unsigned int i=0;i<obstacles.size();i++)
			obstacles[i]->Draw(g);
		for(unsigned int i=0;i<chunks.size();i++)
			chunks[i]->Draw(g);
		for(unsigned int i=0;i<explosions.size();i++)
			explosions[i]->Draw(g);
		for(unsigned int i = 0; i < chunks.size(); i++)
		{
			obstacles.push_back(new Asteroid());
			obstacles.back()->Initialize2(chunks[i]->position, chunks[i]->velocity, chunks[i]->scalar);
		}

		while(chunks.size() > 0)
		{
			delete chunks[0];
			chunks.erase(chunks.begin());
		}
		if(Core::Input::IsPressed(8))
		{
			DeleteAll();
			Initialize();
			state = MENU;
			
		}
	}

	void UpdateMenu(float dt)
	{
		dt;
		playerShip->Display(dt);
		playerShip->Update(dt);
	}

	void UpdateGame(float dt)
	{
		dt;
		//Profiler.newFrame();
		//Profile psu("PlayerShip Update");
		if(!playerShip->isDead)
			playerShip->Update(dt);
		//Profile eu("Enemy Update");
		for(unsigned int i=0;i<enemies.size();i++)
			enemies[i]->Update(dt);
		//Profile pu("Projectiles Update");
		for(unsigned int i=0;i<projectiles.size();i++)
			projectiles[i]->Update(dt);
		//Profile epu("Enemy Projectiles Update");
		for(unsigned int i=0;i<enemyProjectiles.size();i++)
			enemyProjectiles[i]->Update(dt);
		//Profile ou("Obstacles Update");
		for(unsigned int i=0;i<obstacles.size();i++)
			obstacles[i]->Update(dt);
		//Profile cu("Chunks Update");
		for(unsigned int i=0;i<chunks.size();i++)
			chunks[i]->Update(dt);
		//Profile exu("Explosions Update");
		for(unsigned int i=0;i<explosions.size();i++)
			explosions[i]->Update(dt);
		//Profile cv("Clean Vectors");
		CleanVectors();
	}

	void UpdateEnd(float dt)
	{
		dt;
		if(!playerShip->isDead)
			playerShip->Update(dt);
		for(unsigned int i=0;i<enemies.size();i++)
			enemies[i]->Update(dt);
		for(unsigned int i=0;i<projectiles.size();i++)
			projectiles[i]->Update(dt);
		for(unsigned int i=0;i<enemyProjectiles.size();i++)
			enemyProjectiles[i]->Update(dt);
		for(unsigned int i=0;i<obstacles.size();i++)
			obstacles[i]->Update(dt);
		for(unsigned int i=0;i<chunks.size();i++)
			chunks[i]->Update(dt);
		for(unsigned int i=0;i<explosions.size();i++)
			explosions[i]->Update(dt);
		CleanVectors();
	}

	void PrintString(int x, int y, const char* string, Core::Graphics& g)
	{
		g.SetColor(RGB(255, 255, 255));
		stream.str("");
		stream << string;
		g.DrawString(x, y, stream.str().c_str());
	}

	void PrintStringString(int x, int y, const char* string1, const char* string2, Core::Graphics& g)
	{
		g.SetColor(RGB(255, 255, 255));
		stream.str("");
		stream << string1 << string2;
		g.DrawString(x, y, stream.str().c_str());
	}

	void PrintStringAndNum(int x, int y, const char* string, float num, Core::Graphics& g)
	{
		g.SetColor(RGB(255, 255, 255));
		stream.str("");
		stream << string << num;
		g.DrawString(x, y, stream.str().c_str());
	}

	void CleanVectors()
	{
		if(enemies.size() > 20)
		{
			for(unsigned int i=0;i<enemies.size();i++)
			{
				if(enemies[i]->lifetime < 0)
				{
					delete enemies[i];
					enemies.erase(enemies.begin() + i);
					i--;
				}
			}
		}
		if(projectiles.size() > 35)
		{
			for(unsigned int i=0;i<projectiles.size();i++)
			{
				if(projectiles[i]->lifetime < 0)
				{
					delete projectiles[i];
					projectiles.erase(projectiles.begin() + i);
					i--;
				}
			}
		}
		if(enemyProjectiles.size() > 25)
		{
			for(unsigned int i=0;i<enemyProjectiles.size();i++)
			{
				if(enemyProjectiles[i]->lifetime < 0)
				{
					delete enemyProjectiles[i];
					enemyProjectiles.erase(enemyProjectiles.begin() + i);
					i--;
				}
			}
		}
		if(obstacles.size() > 20)
		{
			for(unsigned int i=0;i<obstacles.size();i++)
			{
				if(obstacles[i]->lifetime < 0)
				{
					delete obstacles[i];
					obstacles.erase(obstacles.begin() + i);
					i--;
				}
			}
		}
		/*if(chunks.size() > 20)
		{
			for(unsigned int i=0;i<chunks.size();i++)
			{
				if(chunks[i]->lifetime < 0)
				{
					delete chunks[i];
					chunks.erase(chunks.begin() + i);
					i--;
				}
			}
		}*/
		if(explosions.size() > 15)
		{
			for(unsigned int i=0;i<explosions.size();i++)
			{
				if(explosions[i]->lifetime < 0)
				{
					delete explosions[i];
					explosions.erase(explosions.begin() + i);
					i--;
				}
			}
		}


	}

	void DeleteAll()
	{
		delete playerShip;

		while(projectiles.size() > 0)
		{
			delete projectiles[0];
			projectiles.erase(projectiles.begin());
		}

		while(explosions.size() > 0)
		{
			delete explosions[0];
			explosions.erase(explosions.begin());
		}

		while(obstacles.size() > 0)
		{
			delete obstacles[0];
			obstacles.erase(obstacles.begin());
		}
	}
};

static Startup instance;

void InitializeInstance()
{
	instance.Initialize();
	/*obstacles.push_back(new Asteroid());
	obstacles.back()->Initialize(Vector3D(100, 100), Vector3D(0, 0), 16);*/
}

void DrawFunction(Core::Graphics& g)
{
	g;
	float time = 1/t.lastLapTime();
	instance.PrintStringAndNum(10, 10, "FPS: ", time, g);
	profiler.newFrame();
	Profile p("Draw");
#if _DEBUG
	_CrtMemState a;
	_CrtMemCheckpoint (&a);
	instance.PrintStringAndNum(10, 500, "Allocations: ", (float)a.lCounts[_CLIENT_BLOCK], g);
	instance.PrintStringAndNum(10, 510, "Memory: ", (float)a.lSizes[_CLIENT_BLOCK], g);
	instance.PrintStringAndNum(10, 520, "Max Memory: ", (float)a.lHighWaterCount, g);
#endif
	if(state == MENU)
	{
		instance.DrawMenu(g);
	}
	else if(state == GAME)
	{
		instance.DrawGame(g);
	}
	else if(state == END)
	{
		instance.DrawEnd(g);
	}
}

bool UpdateFunction(float dt)
{
	dt;
	if(Core::Input::IsPressed(27))
		return true;
	t.lap();
	Profile p("Update");
	if(state == MENU)
	{
		instance.UpdateMenu(dt);
	}
	else if(state == GAME)
	{
		instance.UpdateGame(dt);
	}
	else
	{
		instance.UpdateEnd(dt);
	}

	return false;
}

#endif