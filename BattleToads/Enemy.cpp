#include "Enemy.h"



Enemy::Enemy(iPoint pos)
{
	position = pos;
	SDL_Rect rec;
	rec.x = position.x;
	rec.y = position.y;
	hitBox = new Hitbox(rec,1.0f);
}


Enemy::~Enemy()
{
}
