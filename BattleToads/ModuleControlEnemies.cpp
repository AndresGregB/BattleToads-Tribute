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

		}
		if (spawns[i].enemiesDefeated == spawns[i].numEnemies) // Deactivates spawns
		{
			spawns[i].active = false;
			spawns[i].trigered = false;
			spawns[i].cleared = true;
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
