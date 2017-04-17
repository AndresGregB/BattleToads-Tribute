#include "ModuleControlEnemies.h"
#include "Application.h"
#include "Enemy.h"




ModuleControlEnemies::ModuleControlEnemies()
{
	int SpawnCoordX[] = { 200,620,920,1900,2190,2475};
	for (int i = 0; i < 6 ; i++) 
	{
		spawns[i].coordX = SpawnCoordX[i];
	}
}


ModuleControlEnemies::~ModuleControlEnemies()
{
}
void ModuleControlEnemies::Clear() 
{
	App->textures->Unload(graphics);
}
void ModuleControlEnemies::Update() 
{
	// Update Spawnpoints
	for (int i = 0; i < 6; i++)
	{
		if (App->player->position.x >= spawns[i].coordX && spawns[i].active && !spawns[i].trigered) // Activates Spawnpoints
		{
			spawns[i].trigered = true;
			App->renderer->lockCamera();
			spawns[i].spawnTime = SDL_GetTicks();

		}else if (spawns[i].enemiesDefeated == spawns[i].numEnemies && !spawns[i].cleared) // Deactivates spawns that are cleared
		{
			spawns[i].active = false;
			spawns[i].trigered = false;
			spawns[i].cleared = true;
			App->renderer->cameraLocked = false;
		}
		else if (spawns[i].active && spawns[i].trigered && !spawns[i].cleared) {
			spawningPoint = i;
			spawnEnemies(i);
		}

	}

	
}
void ModuleControlEnemies::PostUpdate()
{
	
}
void ModuleControlEnemies::Start()
{
	graphics = App->textures->Load("./Sprites/enemies.gif");
	iPoint testPos;
	testPos.x = 250;
	testPos.y = 105;
	Enemy* test = new Enemy(testPos);
	//App->collisions->addEnemy(test);
	//test->Draw();
	//test1 = test;
	spawnTimer = SDL_GetTicks();
}
bool ModuleControlEnemies::checkSpawningPoints() 
{
	for (int i = 0; i < 6; i++)
	{
		if (spawns[i].active && spawns[i].trigered && !spawns[i].cleared) // Check if there are spawnpoints spawning enemies
		{
			return true;
		}
	}
	return false;
}
void ModuleControlEnemies::spawnEnemies(int spawningPoint) 
{
	if (SDL_GetTicks() - spawns[spawningPoint].spawnTime >= 2000 && spawns[spawningPoint].enemiesSpawned < spawns[spawningPoint].numEnemies)
	{
		spawns[spawningPoint].spawnTime = SDL_GetTicks();

		iPoint enemyPos;
		enemyPos.x = spawns[spawningPoint].coordX - 200;
		enemyPos.y = 105;
		Enemy* spawnedEnemy = new Enemy(enemyPos);
		App->collisions->addEnemy(spawnedEnemy);
		enemyPos.x = spawns[spawningPoint].coordX + 200;
		spawnedEnemy = new Enemy(enemyPos);
		App->collisions->addEnemy(spawnedEnemy);

		spawns[spawningPoint].enemiesSpawned += 2;

	}
}
void ModuleControlEnemies::enemyDefeated() 
{
	++spawns[spawningPoint].enemiesDefeated;
}
void ModuleControlEnemies::restoreSpawnpoints()
{
	for (int i = 0; i < 6; i++)
	{
		spawns[i].active = true;
		spawns[i].trigered = false;
		spawns[i].cleared = false;
		spawns[i].numEnemies = 12;
		spawns[i].enemiesSpawned = 0;
		spawns[i].enemiesDefeated = 0;
	}
}
