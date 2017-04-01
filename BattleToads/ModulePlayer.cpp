#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "SDL/include/SDL.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA
ModulePlayer::ModulePlayer(bool start_enabled) : Module(start_enabled)
{
	position.x = 100;
	position.y = 110;

	// idle animation (arcade sprite sheet)
	idle.frames.push_back({7, 14, 60, 90});
	idle.frames.push_back({95, 15, 60, 89});
	idle.frames.push_back({184, 14, 60, 90});
	idle.frames.push_back({276, 11, 60, 93});
	idle.frames.push_back({366, 12, 60, 92});
	idle.speed = 0.2f;
	
	// walk backward animation (arcade sprite sheet)
	backward.frames.push_back({542, 131, 61, 87});
	backward.frames.push_back({628, 129, 59, 90});
	backward.frames.push_back({713, 128, 57, 90});
	backward.frames.push_back({797, 127, 57, 90});
	backward.frames.push_back({883, 128, 58, 91});
	backward.frames.push_back({974, 129, 57, 89});
	backward.speed = 0.2f;

	// TODO 8: setup the walk forward animation from ryu4.png
	walk.frames.push_back({ 9, 131, 61, 87 });
	walk.frames.push_back({ 78, 129, 61, 90 });
	walk.frames.push_back({ 160, 128, 61, 90 });
	walk.frames.push_back({ 260, 127, 61, 90 });
	walk.frames.push_back({ 351, 128, 61, 91 });
	walk.frames.push_back({ 431, 129, 61, 89 });
	walk.speed = 0.2f;
}

ModulePlayer::~ModulePlayer()
{
	// Homework : check for memory leaks
}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("ryu4.png"); // arcade version

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}

// Update
update_status ModulePlayer::Update()
{
	// TODO 9: Draw the player with its animation
	// make sure to detect player movement and change its
	// position while cycling the animation(check Animation.h)
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
		App->renderer->Blit(graphics, position.x, position.y, &(walk.GetCurrentFrame()), 1.0f);
		position.x += 2;;
	}else if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
		--position.x;
		App->renderer->Blit(graphics, position.x, position.y, &(backward.GetCurrentFrame()), 1.0f);
	}else{
		App->renderer->Blit(graphics, position.x, position.y, &(idle.GetCurrentFrame()), 1.0f);
	}
	return UPDATE_CONTINUE;
}