#ifndef __MODULESCENEINFERNO_H__
#define __MODULESCENEINFERNO_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

struct movingPlantform
{
  Hitbox *platformHitbox;
  float speed = 1.0f;
  float amplitude;
  float variation;
  iPoint position;
};

class ModuleSceneInferno:public Module
{
public:
  ModuleSceneInferno (bool start_enabled = true);
   ~ModuleSceneInferno ();

  bool Start ();
  update_status Update ();
  bool CleanUp ();
  void updatePlatform (movingPlantform * plat);

public:

    SDL_Texture * graphics = nullptr;
  SDL_Texture *objects = nullptr;
  SDL_Rect background;
  SDL_Rect platformVisual;
  Animation flag;
  Animation girl;
  int boatH;
  int frames;
  int signo;
  movingPlantform *platform1, *platform2, *platform3;
};

#endif
