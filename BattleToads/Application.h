#ifndef __APPLICATION_CPP__
#define __APPLICATION_CPP__

#include<list>
#include "Globals.h"
#include "Module.h"
#include "ModulePlayer.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"

class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleAudio;
class ModuleFadeToBlack;
class ModuleSceneKen;
class ModuleSceneInferno;

class Application
{
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

public:
	ModuleRender* renderer;
	ModuleWindow* window;
	ModuleTextures* textures;
	ModuleInput* input;
	ModuleAudio* audio;
	ModuleFadeToBlack* fade;
	ModulePlayer* player;
	ModuleSceneKen* scene_ken;
	ModuleSceneInferno* scene_inferno;
	ModuleCollisions* collisions;

private:

	std::list<Module*> modules;

};

extern Application* App;

#endif // __APPLICATION_CPP__