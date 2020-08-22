#ifndef __MODULECOLLISIONS_H__
#define __MODULECOLLISIONS_H__

#include "SDL.h"
#include "Globals.h"
#include "Module.h"
#include "Hitbox.h"
#include <list>
#include "ModuleControlEnemies.h"
class Enemy;


class ModuleCollisions:public Module
{
public:
  ModuleCollisions ();
  ~ModuleCollisions ();

  // Zones
  std::list < Hitbox * >levelLayout;
  std::list < Enemy * >enemies;

  void drawHitboxes ();
  bool CleanUp ();
  update_status Update ();
  bool Start ();
  void drawEnemiesBehind ();
  void addHitbox (Hitbox * hitBox);
  void addEnemy (Enemy * enemy);
  bool checkIfOnFloor ();
  update_status PostUpdate ();
  bool checkAttackHit (Hitbox * attackHitbox, const float attackerCoordZ,
		       const Hitbox * targetHitbox, const float targetCoordZ);
  void checkAttackVsEnemies (Hitbox * attackHitbox,
			     const float attackerCoordZ);
  ModuleControlEnemies *enemiesControler;

};
#endif
