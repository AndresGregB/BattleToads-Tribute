#include "ModuleCollisions.h"
#include "Application.h"



ModuleCollisions::ModuleCollisions()
{
	// Level Layout
	SDL_Rect auxRect;
	auxRect.x = 1315;
	auxRect.y = 110;
	auxRect.w = 183;
	auxRect.h = 50;
	Hitbox* auxHitBox = new Hitbox(auxRect,1.0f);
	zone1.push_back(auxHitBox);

	auxRect.x = 1575;
	auxRect.y = 110;
	auxRect.w = 183;
	auxRect.h = 50;
	auxHitBox = new Hitbox(auxRect, 1.0f);
	zone1.push_back(auxHitBox);

	auxRect.x = 1060;
	auxRect.y = 110;
	auxRect.w = 183;
	auxRect.h = 50;
	auxHitBox = new Hitbox(auxRect, 1.0f);
	zone1.push_back(auxHitBox);
}


ModuleCollisions::~ModuleCollisions()
{
}
bool ModuleCollisions::CleanUp()
{
	LOG("Unloading hitboxes");

	zone1.clear();

	return true;
}
update_status ModuleCollisions::Update()
{
	drawHitboxes();
	std::list<Hitbox*>::const_iterator it;

	for (it = zone1.begin(); it != zone1.end(); ++it)
	{
		(*it)->checkIntersection(App->player->playerHitbox->hitBox);
	}

	return UPDATE_CONTINUE;
}
void ModuleCollisions::drawHitboxes()
{
	std::list<Hitbox*>::const_iterator it;

	for (it = zone1.begin();it != zone1.end(); ++it) 
	{
		(*it)->draw(App->renderer->renderer);
	}
}
