#ifndef __HITBOX_H__
#define __HITBOX_H__

#include "SDL/include/SDL.h"
#include "Point.h"
#include "Globals.h"

class Hitbox
{
public:
	Hitbox(iPoint coord, float w, float h);
	~Hitbox();

	SDL_Rect hitBox;

	bool Hitbox::checkIntersection(const SDL_Rect target);
	void Hitbox::draw(SDL_Renderer* renderer);
};
#endif
