#include "Enemy.h"



Enemy::Enemy(iPoint pos)
{
	position = pos;
	movement.SetToZero();
	moveSpeed = 1.5;
	CoordZ = -1;
	active = true;

	SDL_Rect rec;
	rec.x = position.x;
	rec.y = position.y;
	hitBox = new Hitbox(rec,1.0f);
	hitBox->hitBox.w = 25;
	hitBox->hitBox.h = 30;

	rec.x = position.x + hitBox->hitBox.w;
	rec.y = position.y;
	attackRH = new Hitbox(rec, 1.0f);
	attackRH->hitBox.w = 15;
	attackRH->hitBox.h = 30;

	rec.x = position.x - hitBox->hitBox.w/2;
	rec.y = position.y;
	attackLH = new Hitbox(rec, 1.0f);
	attackLH->hitBox.w = 15;
	attackLH->hitBox.h = 30;

	walk.frames.push_back({120,270,44,45});
	walk.frames.push_back({ 167,268,48,50 });
	walk.frames.push_back({ 224,269,39,46 });
	walk.speed = 0.1f;

	attack.frames.push_back({297,76,37,38});
	attack.frames.push_back({ 346,72,38,43 });
	attack.frames.push_back({ 390,79,44,37 });
	attack.speed = 0.08f;

	death.frames.push_back({442,72,40,43});
	death.frames.push_back({ 489,72,40,43 });
	death.speed = 0.05f;
}


Enemy::~Enemy()
{
}
void Enemy::Clear()
{
	delete hitBox;
}
void Enemy::Update() 
{
	if (status == DYING && SDL_GetTicks() - deathTimer > 1000) 
	{
		active = false;
		LOG("Erasing enemy");
	}
	if (active && status != DYING) {
		if ( calculateDistancetoPlayer() > 25.0f)
		{
			fPoint nextMovement;
			nextMovement.x = App->player->position.x - position.x;
			nextMovement.y = App->player->coordZ - CoordZ;
			float module = sqrt((nextMovement.x*nextMovement.x + nextMovement.y*nextMovement.y));
			
			nextMovement.x = nextMovement.x / module;
			nextMovement.y = nextMovement.y / module;

			nextMovement.x *= moveSpeed;
			nextMovement.y *= moveSpeed;

			if (nextMovement.DistanceTo(movement)<= 5) // Fix enemy moving two fast between 2 round values.
			{
				movement = nextMovement;
			}
			else {
				movement.SetToZero();
			}
			//floorY = 120 + coordZ * 10;
			CoordZ += movement.y;
			position.x += round(movement.x);
			position.y = round(125 + CoordZ * 10);

			hitBox->hitBox.x = position.x;
			hitBox->hitBox.y = position.y;
			attackRH->hitBox.x = position.x + hitBox->hitBox.w;
			attackRH->hitBox.y = position.y;
			attackLH->hitBox.x = position.x - hitBox->hitBox.w/2;
			attackLH->hitBox.y = position.y;


			if (movement.x >= 0.5) 
			{
				status = WALK_RIGHT;
			}
			else {
				status = WALK_LEFT;
			}
		}
		else {
			// Enemy is close enought to attack
			if (position.x >= App->player->position.x) status = ATTACKING_L;
			if (position.x < App->player->position.x) status = ATTACKING_R;
			if (!attacking)
			{
				attackTimer = SDL_GetTicks();
				attacking = true;
			}
		}
	}
	Draw();
}
void Enemy::Draw()
{
	if (status == WALK_RIGHT) {
		App->renderer->Blit2(App->collisions->enemiesControler->graphics, position.x, position.y, &(walk.GetCurrentFrame()), 1.0f, 2);
	}else if (status == WALK_LEFT) {
		App->renderer->Blit2(App->collisions->enemiesControler->graphics, position.x, position.y, &(walk.GetCurrentFrame()), 1.0f, 2, true);
	}
	else if (status == DYING) {
		App->renderer->Blit2(App->collisions->enemiesControler->graphics, position.x, position.y, &(death.GetCurrentFrame()), 1.0f, 2);
	}
	else if (status == ATTACKING_R) {
		App->renderer->Blit2(App->collisions->enemiesControler->graphics, position.x, position.y, &(attack.GetCurrentFrame()), 1.0f, 2);
		if (SDL_GetTicks() - attackTimer > 500 && status != DYING)
		{
			if (App->collisions->checkAttackHit(attackRH, CoordZ, App->player->playerHitbox, App->player->coordZ)) App->player->takeHit();
			attacking = false;
		}

	}
	else if (status == ATTACKING_L) {
		App->renderer->Blit2(App->collisions->enemiesControler->graphics, position.x, position.y, &(attack.GetCurrentFrame()), 1.0f, 2, true);
		if (SDL_GetTicks() - attackTimer > 500 && status != DYING)
		{
			if(App->collisions->checkAttackHit(attackLH, CoordZ, App->player->playerHitbox, App->player->coordZ)) App->player->takeHit();
			attacking = false;
		}
	}
	
}
int Enemy::calculateDistancetoPlayer() 
{
	return position.DistanceTo(App->player->position);
}
void Enemy::prepareToDie() 
{
	if (status != DYING) 
	{
		deathTimer = SDL_GetTicks();
		status = DYING;
	}
	
}