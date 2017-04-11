#include "Globals.h"
#include "Application.h"
#include "ModuleSceneInferno.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL.h"
#include <math.h>


ModuleSceneInferno::ModuleSceneInferno(bool start_enabled) : Module(start_enabled)
{
	// Background / sky
	background.x = 528;
	background.y = 17;
	background.w = 2820;
	background.h = 176;

	

}

ModuleSceneInferno::~ModuleSceneInferno()
{}

// Load assets
bool ModuleSceneInferno::Start()
{
	LOG("Loading Inferno scene");

	graphics = App->textures->Load("./Sprites/Part_1.png");
	App->player->Enable();
	App->audio->PlayMusic("ken.ogg");
	frames = 0;
	boatH = 0;
	signo = 1;

	// Platform 1
	SDL_Rect auxRect;
	auxRect.x = 1150;
	auxRect.y = 110;
	auxRect.w = 20;
	auxRect.h = 50;
	platform1 = new movingPlantform;
	platform1->platformHitbox = new Hitbox(auxRect, 1.0f);
	platform1->speed = 1.0f;
	platform1->amplitude = 100.0f;
	App->collisions->addHitbox(platform1->platformHitbox);
	platform1->position.x = 1150;
	platform1->position.y = 110;
	platform1->variation = 7.0f;

	// Platform 2
	auxRect.x = 1400;
	platform2 = new movingPlantform;
	platform2->platformHitbox = new Hitbox(auxRect, 1.0f);
	platform2->speed = 1.0f;
	platform2->amplitude = 100.0f;
	App->collisions->addHitbox(platform2->platformHitbox);
	platform2->position.x = 1400;
	platform2->position.y = 110;
	platform2->variation = 5.0f;

	// Platform 3
	auxRect.x = 1650;
	platform3 = new movingPlantform;
	platform3->platformHitbox = new Hitbox(auxRect, 1.0f);
	platform3->speed = 100.0f;
	platform3->amplitude = 1.0f;
	App->collisions->addHitbox(platform3->platformHitbox);
	platform3->position.x = 1650;
	platform3->position.y = 110;
	platform3->variation = 3.0f;
	
	return true;
}

// UnLoad assets
bool ModuleSceneInferno::CleanUp()
{
	LOG("Unloading Inferno scene");

	App->textures->Unload(graphics);
	App->player->Disable();

	return true;
}

// Update: draw background
update_status ModuleSceneInferno::Update()
{
	updatePlatform(platform1);
	updatePlatform(platform2);
	updatePlatform(platform3);

	App->renderer->Blit(graphics, 0, 0, &background, 1.0f); // sea and sky
	++frames;	
	return UPDATE_CONTINUE;
}
void ModuleSceneInferno::updatePlatform(movingPlantform* plat)
{
	plat->platformHitbox->hitBox.x = plat->position.x + 80 * sin((double)(SDL_GetTicks()/10)*0.01 + plat->variation);
}
