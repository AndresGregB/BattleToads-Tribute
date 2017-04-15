#ifndef __ENEMY_H__
#define __ENEMY_H__


#include "Globals.h"
#include "Application.h"
#include "ModuleControlEnemies.h"
#include "Point.h"
#include "Hitbox.h"

class Enemy
{
public:
	Enemy(iPoint pos);
	~Enemy();

	iPoint position;
	float CoordZ;
	Hitbox* hitBox;
	void Enemy::Update();
	int Enemy::calculateDistancetoPlayer();

private:
	float coordZ;
	int jumpSpeed;
	int moveSpeed;


};
#endif
