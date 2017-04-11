#ifndef __MODULECOLLISIONS_H__
#define __MODULECOLLISIONS_H__

#include "SDL/include/SDL.h"
#include "Globals.h"
#include "Module.h"
#include "Hitbox.h"
#include <list>

class ModuleCollisions: public Module
{
public:
	ModuleCollisions();
	~ModuleCollisions();

	// Zones
	std::list<Hitbox*> zone1;

	void ModuleCollisions::drawHitboxes();
	bool ModuleCollisions::CleanUp();
	update_status ModuleCollisions::Update();

};
#endif
