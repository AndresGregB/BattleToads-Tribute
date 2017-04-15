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
	test1->Draw();
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
}
