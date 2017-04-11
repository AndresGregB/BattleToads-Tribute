#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "SDL/include/SDL.h"

ModulePlayer::ModulePlayer(bool start_enabled) : Module(start_enabled)
{
	position.x = 1800;
	position.y = 110;
	SDL_Rect PHitbox;

	PHitbox.x = position.x;
	PHitbox.y = position.y;
	PHitbox.w = 26;
	PHitbox.h = 34;

	playerHitbox = new Hitbox(PHitbox, 1.0f);

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
	walk.speed = 0.2f;

	jump.frames.push_back({ 415, 167, 46, 25 });
	AnimStatus = IDLE_RIGHT;
	jumping = false;
	coordZ = -1.0;
	floorY = 120 + coordZ * 10; // Mapping the floor height with the coordZ
	speedY = 0;
	jumpSpeed = -5;
	moveSpeed = 4;
	playerZone = 1;
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
	// TODO: Add colission with level layout and "grounded" boolean for the player
	floorY = 120 + coordZ * 10;
	if (position.y >= (int)floorY) 
	{
		jumping = false;
		speedY = 0;
	} 
	if (jumping) 
	{
		speedY += GRAVITY;
	} 
	// Assing Animation default status
	if (AnimStatus == WALKING_LEFT || AnimStatus == JUMPING_LEFT)
	{
		if (jumping) 
		{
			AnimStatus = JUMPING_LEFT;
		}
		else 
		{
			AnimStatus = IDLE_LEFT;
		}
		
	}
	else if (AnimStatus == WALKING_RIGHT || AnimStatus == JUMPING_RIGHT)
	{
		if (jumping)
		{
			AnimStatus = JUMPING_RIGHT;
		}
		else
		{
			AnimStatus = IDLE_RIGHT;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_SPACE)== KEY_DOWN && !jumping) {
		jumping = true;
		speedY = jumpSpeed;
	}

	// Calculating new position for the player in next frame.
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && !jumping) {
		// This if is empty so the AnimStatus does not change when pressing A and D at the same time
	}
	else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
		position.x += moveSpeed;
		if (jumping) 
		{
			AnimStatus = JUMPING_RIGHT;
		}
		else {
			AnimStatus = WALKING_RIGHT;
		}
		
	}
	else if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
		position.x -= moveSpeed;
		if (jumping)
		{
			AnimStatus = JUMPING_LEFT;
		}
		else {
			AnimStatus = WALKING_LEFT;
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT  && coordZ > -3.5/*Limit to vertical movement*/) {
		position.y -= 0.2;
		coordZ -= 0.1;
		if (AnimStatus == IDLE_LEFT)
		{
			AnimStatus = WALKING_LEFT;
		}
		else if (AnimStatus == IDLE_RIGHT)
		{
			AnimStatus = WALKING_RIGHT;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT  && coordZ < 0/*Limit to vertical movement*/) {
		position.y += 1.8;
		coordZ += 0.1;
		if (AnimStatus == IDLE_LEFT)
		{
			AnimStatus = WALKING_LEFT;
		}
		else if (AnimStatus == IDLE_RIGHT)
		{
			AnimStatus = WALKING_RIGHT;
		}
	}
	
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && !jumping) {
		if (AnimStatus == IDLE_LEFT || AnimStatus == WALKING_LEFT)
		{
			AnimStatus = IDLE_LEFT;
		}
		if (AnimStatus == IDLE_RIGHT || AnimStatus == WALKING_RIGHT)
		{
			AnimStatus = IDLE_RIGHT;
		} // Idle when pressing A and D at the same time
	}
	else if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT && !jumping) {
		if (AnimStatus == IDLE_LEFT || AnimStatus == WALKING_LEFT)
		{
			AnimStatus = IDLE_LEFT;
		}
		else if (AnimStatus == IDLE_RIGHT || AnimStatus == WALKING_RIGHT)
		{
			AnimStatus = IDLE_RIGHT;
		} // Idle when pressing S and W at the same time
	}
	
	// Apply animation depending on AnimStatus
	if (AnimStatus == JUMPING_RIGHT) {
		App->renderer->Blit(graphics, position.x, position.y, &(jump.GetCurrentFrame()), 1.0f); // Jump Right
	}
	else if (AnimStatus == JUMPING_LEFT) {
		App->renderer->Blit(graphics, position.x, position.y, &(jump.GetCurrentFrame()), 1.0f, true); // Jump Left
	}
	else if (AnimStatus == WALKING_RIGHT) {
		App->renderer->Blit(graphics, position.x, position.y, &(walk.GetCurrentFrame()), 1.0f); // Walk Right
	}
	else if (AnimStatus == WALKING_LEFT) {
		App->renderer->Blit(graphics, position.x, position.y, &(walk.GetCurrentFrame()), 1.0f,true);//Walk Left
	}
	else if (AnimStatus == IDLE_RIGHT){
		App->renderer->Blit(graphics, position.x, position.y, &(idle.GetCurrentFrame()), 1.0f); // Idle
	}
	else if (AnimStatus == IDLE_LEFT) {
		App->renderer->Blit(graphics, position.x, position.y, &(idle.GetCurrentFrame()), 1.0f,true); // Idle
	}
	position.y += (int)speedY;


	// Update player's hitbox
	playerHitbox->hitBox.x = position.x;
	playerHitbox->hitBox.y = position.y;
	playerHitbox->draw(App->renderer->renderer);

	/*SDL_Rect auxRect;
	auxRect.x = 1315;
	auxRect.y = 110;
	auxRect.w = 183;
	auxRect.h = 50;
	Hitbox auxHitBox(auxRect,1.0f);*/
	//auxHitBox.draw(App->renderer->renderer);
	/*LOG("Y calc: %f \n", 120 + coordZ*10);
	LOG("Y: %f \n", coordZ);*/
	return UPDATE_CONTINUE;
}