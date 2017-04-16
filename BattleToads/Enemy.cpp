#include "Enemy.h"



Enemy::Enemy(iPoint pos)
{
	position = pos;
	SDL_Rect rec;
	rec.x = position.x;
	rec.y = position.y;
	movement.SetToZero();
	moveSpeed = 1.5;
	CoordZ = -1;
	active = true;
	hitBox = new Hitbox(rec,1.0f);
	hitBox->hitBox.w = 25;
	hitBox->hitBox.h = 30;

	walk.frames.push_back({120,270,44,45});
	walk.frames.push_back({ 167,268,48,50 });
	walk.frames.push_back({ 224,269,39,46 });
	walk.speed = 0.1f;
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
	if (active) {
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

			if (movement.x >= 0.5) 
			{
				status = WALK_RIGHT;
			}
			else {
				status = WALK_LEFT;
			}
		}
		Draw();
	}
}
void Enemy::Draw()
{
	if (status == WALK_RIGHT) {
		App->renderer->Blit2(App->collisions->enemiesControler->graphics, position.x, position.y, &(walk.GetCurrentFrame()), 1.0f, 2);
	}else if (status == WALK_LEFT) {
		App->renderer->Blit2(App->collisions->enemiesControler->graphics, position.x, position.y, &(walk.GetCurrentFrame()), 1.0f, 2, true);
	}
	
}
int Enemy::calculateDistancetoPlayer() 
{
	return position.DistanceTo(App->player->position);
}