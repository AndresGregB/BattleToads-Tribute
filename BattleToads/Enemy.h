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
	WALK_LEFT
};
class Enemy
{
public:
	Enemy(iPoint pos);
	~Enemy();
	Animation walk;
	Animation attack;
	iPoint position;
	fPoint movement;
	float CoordZ;
	Hitbox* hitBox;
	bool active;
	void Enemy::Update();
	void Enemy::Clear();
	void Enemy::Draw();
	int Enemy::calculateDistancetoPlayer();

private:
	int moveSpeed;
	enemyAnim status;


};
#endif
