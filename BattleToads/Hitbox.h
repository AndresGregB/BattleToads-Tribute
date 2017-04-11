#ifndef __HITBOX_H__
#define __HITBOX_H__

#include "SDL/include/SDL.h"
#include "Globals.h"


class Hitbox
{
public:
	Hitbox(SDL_Rect Rect, float s);
	~Hitbox();

	SDL_Rect hitBox;

	bool Hitbox::checkIntersection(const SDL_Rect target);
	void Hitbox::draw(SDL_Renderer* renderer);
	float speed;
};
#endif
