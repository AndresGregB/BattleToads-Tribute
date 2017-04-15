#include "ModuleControlEnemies.h"
#include "Application.h"




ModuleControlEnemies::ModuleControlEnemies()
{
}


ModuleControlEnemies::~ModuleControlEnemies()
{
}
void ModuleControlEnemies::Update() 
{

}
void ModuleControlEnemies::Start()
{
	graphics = App->textures->Load("./Sprites/rash.png");
}
