#ifndef __MODULECONTROLENEMIES_H__
#define __MODULECONTROLENEMIES_H__
//#include "ModuleTextures.h"
//#include "Animation.h"
struct SDL_Texture;
class Enemy;
struct SpawnPoint
{
  bool active = true;
  bool trigered = false;
  bool cleared = false;
  int numEnemies = 12;
  int enemiesSpawned = 0;
  int enemiesDefeated = 0;
  int spawnTime;
  int coordX;
};
class ModuleControlEnemies
{
public:
  ModuleControlEnemies ();
  ~ModuleControlEnemies ();
  SDL_Texture *graphics;
  float spawnTimer;
  void Update ();
  void Start ();
  void Clear ();
  bool checkSpawningPoints ();
  void PostUpdate ();
  void enemyDefeated ();
  void restoreSpawnpoints ();

private:
    SpawnPoint spawns[6];
  void spawnEnemies (int spawningPoint);
  int spawningPoint;
};
#endif
