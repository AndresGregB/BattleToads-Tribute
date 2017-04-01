#include "Globals.h"
#include "Application.h"
#include "ModuleSceneHonda.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleSceneHonda::ModuleSceneHonda(bool start_enabled) : Module(start_enabled)
{
	// ground
	ground.x = 8;
	ground.y = 391;
	ground.w = 896;
	ground.h = 72;

	// TODO 2 : setup the foreground (red ship) with
	// coordinates x,y,w,h from ken_stage.png
	ship.w = 525;
	ship.h = 180;
	ship.x = 8;
	ship.y = 25;
	// Background / sky
	background.x = 72;
	background.y = 208;
	background.w = 768;
	background.h = 176;

	// flag animation
	flag.frames.push_back({ 848, 208, 40, 40 });
	flag.frames.push_back({ 848, 256, 40, 40 });
	flag.frames.push_back({ 848, 304, 40, 40 });
	flag.speed = 0.08f;



	// TODO 4: Setup Girl Animation from coordinates from ken_stage.png
	// girl animation
	girl.frames.push_back({ 624, 16, 32, 56 });
	girl.frames.push_back({ 624, 80, 32, 56 });
	girl.frames.push_back({ 624, 144, 32, 56 });
	girl.speed = 0.08f;

}

ModuleSceneHonda::~ModuleSceneHonda()
{}

// Load assets
bool ModuleSceneHonda::Start()
{
	LOG("Loading ken scene");

	graphics = App->textures->Load("honda_stage.png");
	// TODO 7: Enable the player module
	App->player->Enable();
	// TODO 0: trigger background music
	App->audio->PlayMusic("ken.ogg");
	frames = 0;
	boatH = 0;
	signo = 1;
	return true;
}

// UnLoad assets
bool ModuleSceneHonda::CleanUp()
{
	LOG("Unloading ken scene");

	App->textures->Unload(graphics);
	App->player->Disable();

	return true;
}

// Update: draw background
update_status ModuleSceneHonda::Update()
{
	// TODO 5: make sure the ship goes up and down
	if (frames > 30) {
		boatH = boatH + signo;
		frames = 0;
		if (boatH >= 5) {
			signo = -signo;
		}
		if (boatH <= -4) {
			signo = -signo;
		}

	}
	// Draw everything --------------------------------------
	// TODO 1: Tweak the movement speed of the sea&sky + flag to your taste
	App->renderer->Blit(graphics, 0, 0, &background, 0.75f); // sea and sky

	App->renderer->Blit(graphics, 560, 8, &(flag.GetCurrentFrame()), 0.75f); // flag animation
	App->renderer->Blit(graphics, 0, boatH, &ship, 0.75f);
	App->renderer->Blit(graphics, 192, boatH + 103, &(girl.GetCurrentFrame()), 0.75f);

	// TODO 6: Draw the girl. Make sure it follows the ship movement!

	App->renderer->Blit(graphics, 0, 170, &ground, 1.0f);
	// TODO 10: Build an entire new scene "honda", you can find its
	// and music in the Game/ folder

	// TODO 11: Make that pressing space triggers a switch to honda logic module
	// using FadeToBlack module
	++frames;
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
		
		App->fade->FadeToBlack((Module*)(App->scene_ken), (Module*)(App->scene_honda), 3.0f);
		
	return UPDATE_CONTINUE;
}
