#ifndef __MODULECOLLISIONS_H__
#define __MODULECOLLISIONS_H__

#include "SDL/include/SDL.h"
#include "Globals.h"
#include "Module.h"
#include "Hitbox.h"
#include <list>
#include "ModuleControlEnemies.h"
class Enemy;


class ModuleCollisions: public Module
{
public:
	ModuleCollisions();
	~ModuleCollisions();

	// Zones
	std::list<Hitbox*> levelLayout;
	std::list<Enemy*> enemies;

	void ModuleCollisions::drawHitboxes();
	bool ModuleCollisions::CleanUp();
	update_status ModuleCollisions::Update();
	bool ModuleCollisions::Start();
	void ModuleCollisions::addHitbox(Hitbox* hitBox);
	bool ModuleCollisions::checkIfOnFloor();
	ModuleControlEnemies* enemiesControler;

};
#endif
