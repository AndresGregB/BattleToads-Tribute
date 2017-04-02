#ifndef __MODULESCENEINFERNO_H__
#define __MODULESCENEINFERNO_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleSceneInferno : public Module
{
public:
	ModuleSceneInferno(bool start_enabled = true);
	~ModuleSceneInferno();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	SDL_Rect ground;
	SDL_Rect background;
	SDL_Rect ship;
	Animation flag;
	Animation girl;
	int boatH;
	int frames;
	int signo;
};

#endif
