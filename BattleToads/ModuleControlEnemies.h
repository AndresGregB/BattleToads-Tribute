#ifndef __MODULECONTROLENEMIES_H__
#define __MODULECONTROLENEMIES_H__
//#include "ModuleTextures.h"
struct SDL_Texture;

class ModuleControlEnemies 
{
public:
	ModuleControlEnemies();
	~ModuleControlEnemies();

	SDL_Texture* graphics;
	void ModuleControlEnemies::Update();
	void ModuleControlEnemies::Start();
};
#endif

