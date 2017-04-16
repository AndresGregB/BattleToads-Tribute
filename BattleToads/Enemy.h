#ifndef __ENEMY_H__
#define __ENEMY_H__


#include "Globals.h"
#include "Application.h"
#include "ModuleControlEnemies.h"
#include "Point.h"
#include "Hitbox.h"
#include "Animation.h"
enum enemyAnim
{
	WALK_RIGHT,
	WALK_LEFT,
	DYING,
	ATTACKING_L,
	ATTACKING_R
};
class Enemy
{
public:
	Enemy(iPoint pos);
	~Enemy();
	Animation walk;
	Animation attack;
	Animation death;
	iPoint position;
	fPoint movement;
	float CoordZ;
	float deathTimer;
	float attackTimer;
	Hitbox* hitBox;
	Hitbox* attackLH;
	Hitbox* attackRH;
	bool active;
	bool attacking;
	void Enemy::Update();
	void Enemy::Clear();
	void Enemy::Draw();
	void Enemy::prepareToDie();
	int Enemy::calculateDistancetoPlayer();

private:
	int moveSpeed;
	enemyAnim status;


};
#endif
