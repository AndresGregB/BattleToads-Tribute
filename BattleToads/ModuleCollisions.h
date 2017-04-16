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
	void drawEnemiesBehind();
	void ModuleCollisions::addHitbox(Hitbox* hitBox);
	void ModuleCollisions::addEnemy(Enemy* enemy);
	bool ModuleCollisions::checkIfOnFloor();
	update_status ModuleCollisions::PostUpdate();
	bool ModuleCollisions::checkAttackHit(Hitbox* attackHitbox, const float attackerCoordZ, const Hitbox* targetHitbox, const float targetCoordZ);
	void ModuleCollisions::checkAttackVsEnemies(Hitbox* attackHitbox, const float attackerCoordZ);
	ModuleControlEnemies* enemiesControler;

};
#endif
