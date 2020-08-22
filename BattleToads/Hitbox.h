#ifndef __HITBOX_H__
#define __HITBOX_H__

#include "SDL.h"
#include "Globals.h"


class Hitbox
{
public:
  Hitbox (SDL_Rect Rect, float s);
   ~Hitbox ();

  SDL_Rect hitBox;

  bool checkIntersection (const SDL_Rect target);
  void draw (SDL_Renderer * renderer);
  float speed;
};
#endif
