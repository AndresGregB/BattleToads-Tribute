#include "Enemy.h"



Enemy::Enemy(iPoint pos)
{
	position = pos;
	SDL_Rect rec;
	rec.x = position.x;
	rec.y = position.y;
	hitBox = new Hitbox(rec,1.0f);
	walk.frames.push_back({120,270,44,45});
	walk.frames.push_back({ 167,268,48,50 });
	walk.frames.push_back({ 224,269,39,46 });
	walk.speed = 0.1f;
}


Enemy::~Enemy()
{
}
void Enemy::Update() 
{

}
void Enemy::Draw()
{
	App->renderer->Blit2(App->collisions->enemiesControler->graphics,position.x,position.y,&(walk.GetCurrentFrame()),1.0f,2);
}
int Enemy::calculateDistancetoPlayer() 
{
	return 1;
}