#include "Hitbox.h"



Hitbox::Hitbox(SDL_Rect Rect)
{
	hitBox = Rect;
}


Hitbox::~Hitbox()
{
}
bool Hitbox::checkIntersection(const SDL_Rect target) 
{
	if (
		target.x + target.w < hitBox.x ||	// Target hitbox is left of this hitbox
		hitBox.x + hitBox.w < target.x ||			// Target hitbox is right of this hitbox
		target.y + target.h < hitBox.y ||	// Target hitbox is above this hitbox
		hitBox.y + hitBox.h < target.y				// Target hitbox is below this hitbox
		) 
	{
		return false;
	}
	return true;
}
void Hitbox::draw(SDL_Renderer* renderer)
{
	SDL_RenderDrawRect(renderer, &hitBox);
}
