#ifndef __ENEMY_H__
#define __ENEMY_H__


#include "Globals.h"
#include "Application.h"
#include "ModuleControlEnemies.h"
#include "Point.h"
#include "Hitbox.h"
#include "Animation.h"

class Enemy
{
public:
	Enemy(iPoint pos);
	~Enemy();
	Animation walk;
	Animation attack;
	iPoint position;
	float CoordZ;
	Hitbox* hitBox;
	void Enemy::Update();
	void Enemy::Draw();
	int Enemy::calculateDistancetoPlayer();

private:
	float coordZ;
	int jumpSpeed;
	int moveSpeed;


};
#endif
