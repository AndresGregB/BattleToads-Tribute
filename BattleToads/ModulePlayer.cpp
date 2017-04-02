#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "SDL/include/SDL.h"

ModulePlayer::ModulePlayer(bool start_enabled) : Module(start_enabled)
{
	position.x = 3300;
	position.y = 110;

	idle.frames.push_back({36, 23, 26, 34});
	idle.frames.push_back({69, 23, 26, 34 });
	idle.frames.push_back({ 36, 23, 26, 34 });
	idle.frames.push_back({ 36, 23, 26, 34 });
	idle.frames.push_back({ 69, 23, 26, 34 });
	idle.speed = 0.04f;
	
	backward.frames.push_back({542, 131, 61, 87});
	backward.frames.push_back({628, 129, 59, 90});
	backward.frames.push_back({713, 128, 57, 90});
	backward.frames.push_back({797, 127, 57, 90});
	backward.frames.push_back({883, 128, 58, 91});
	backward.frames.push_back({974, 129, 57, 89});
	backward.speed = 0.2f;

	walk.frames.push_back({ 437, 26, 28, 33 });
	walk.frames.push_back({ 467, 26, 25, 33 });
	walk.frames.push_back({ 499, 30, 33, 30 });
	walk.frames.push_back({ 536, 26, 20, 36 });
	walk.frames.push_back({ 561, 30, 33, 29 });
	walk.speed = 0.1f;
}

ModulePlayer::~ModulePlayer()
{
	// Homework : check for memory leaks
}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("./Sprites/rash.png");

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
	// Calculate next position
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
		position.x += 2;
	}
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
		position.x -= 2;
	}

	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT && position.y > 85) {
		position.y -= 0.2;
		LOG("Position: %d\n", position.y);
	}
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT && position.y < 120) {
		position.y += 1.8;
		LOG("Position: %d\n", position.y);
	}
	// make sure to detect player movement and change its
	// position while cycling the animation(check Animation.h)
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
		App->renderer->Blit(graphics, position.x, position.y, &(idle.GetCurrentFrame()), 1.0f); // Idle when pression A and D at the same time
	}
	else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
		App->renderer->Blit(graphics, position.x, position.y, &(walk.GetCurrentFrame()), 1.0f); // Walk Right
	}
	else if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
		App->renderer->Blit(graphics, position.x, position.y, &(walk.GetCurrentFrame()), 1.0f,true);//Walk Left
	}
	else if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) {
		App->renderer->Blit(graphics, position.x, position.y, &(walk.GetCurrentFrame()), 1.0f);// Walk Up
	}
	else if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {
		App->renderer->Blit(graphics, position.x, position.y, &(walk.GetCurrentFrame()), 1.0f); // Walk down
	}
	else{
		App->renderer->Blit(graphics, position.x, position.y, &(idle.GetCurrentFrame()), 1.0f); // Idle
	}
	return UPDATE_CONTINUE;
}