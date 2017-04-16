#include "ModuleControlEnemies.h"
#include "Application.h"
#include "Enemy.h"




ModuleControlEnemies::ModuleControlEnemies()
{
}


ModuleControlEnemies::~ModuleControlEnemies()
{
}
void ModuleControlEnemies::Update() 
{
	
	if (SDL_GetTicks()-spawnTimer > 1000) 
	{
		iPoint testPos;
		testPos.x = 250;
		testPos.y = 105;
		Enemy* test = new Enemy(testPos);
		App->collisions->addEnemy(test);
		spawnTimer = SDL_GetTicks();
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
	App->collisions->addEnemy(test);
	//test->Draw();
	test1 = test;
	spawnTimer = SDL_GetTicks();
}
