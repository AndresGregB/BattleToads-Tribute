#ifndef __MODULECONTROLENEMIES_H__
#define __MODULECONTROLENEMIES_H__
//#include "ModuleTextures.h"
//#include "Animation.h"
struct SDL_Texture;
class Enemy;
class ModuleControlEnemies 
{
public:
	ModuleControlEnemies();
	~ModuleControlEnemies();
	Enemy* test1;
	SDL_Texture* graphics;
	void ModuleControlEnemies::Update();
	void ModuleControlEnemies::Start();
	void ModuleControlEnemies::PostUpdate();
};
#endif

