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
	// Draw everything --------------------------------------
	//// TODO 1: Tweak the movement speed of the sea&sky + flag to your taste
	App->renderer->Blit(graphics, 0, 0, &background, 0.75f); // sea and sky
	//App->renderer->Blit(graphics, 560, 8, &(flag.GetCurrentFrame()), 0.75f); // flag animation
	//App->renderer->Blit(graphics, 0, boatH, &ship, 0.75f);
	//App->renderer->Blit(graphics, 192, boatH + 103, &(girl.GetCurrentFrame()), 0.75f);

	// TODO 6: Draw the girl. Make sure it follows the ship movement!

	//App->renderer->Blit(graphics, 0, 170, &ground, 1.0f);
	// TODO 10: Build an entire new scene "honda", you can find its
	// and music in the Game/ folder

	// TODO 11: Make that pressing space triggers a switch to honda logic module
	// using FadeToBlack module
	++frames;
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
		
		App->fade->FadeToBlack((Module*)(App->scene_ken), (Module*)(App->scene_inferno), 3.0f);
		
	return UPDATE_CONTINUE;
}
