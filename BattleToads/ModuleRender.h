#ifndef __MODULERENDER_H__
#define __MODULERENDER_H__

#include "Module.h"
#include "Globals.h"

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;

class ModuleRender : public Module
{
public:
	ModuleRender();
	~ModuleRender();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	bool Blit(SDL_Texture* texture, int x, int y, SDL_Rect* section, float speed, bool flipH = false);
	bool Blit2(SDL_Texture* texture, int x, int y, SDL_Rect* section, float speed,int scale, bool flipH = false);


public:
	SDL_Renderer* renderer = nullptr;
	SDL_Rect camera;
	bool cameraLocked;
};

#endif // __MODULERENDER_H__