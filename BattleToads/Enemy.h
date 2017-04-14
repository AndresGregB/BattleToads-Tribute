#ifndef __ENEMY_H__
#define __ENEMY_H__


#include "Globals.h"
#include "Point.h"
#include "Hitbox.h"

class Enemy
{
public:
	Enemy(iPoint pos);
	~Enemy();

	iPoint position;
	Hitbox* hitBox;

private:
	float coordZ;
	int jumpSpeed;
	int moveSpeed;


};
#endif
