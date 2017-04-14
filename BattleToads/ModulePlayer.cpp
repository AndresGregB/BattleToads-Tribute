#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "SDL/include/SDL.h"

ModulePlayer::ModulePlayer(bool start_enabled) : Module(start_enabled)
{
	inputblock = false;

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

	attack1.frames.push_back({ 99, 25, 26, 29 });
	attack1.frames.push_back({ 128, 25, 38, 31 });
	attack1.frames.push_back({ 168, 26, 34, 31 });
	attack1.frames.push_back({ 285, 24, 51, 32 });
	attack1.frames.push_back({ 345, 2, 44, 55 });
	attack1.speed = 0.08f;

	attack2.frames.push_back({ 367, 120, 29, 37 });
	attack2.frames.push_back({ 464, 166, 41, 37 });
	attack2.speed = 0.02f;

	walk.frames.push_back({ 437, 26, 28, 33 });
	walk.frames.push_back({ 467, 26, 25, 33 });
	walk.frames.push_back({ 499, 30, 33, 30 });
	walk.frames.push_back({ 536, 26, 20, 36 });
	walk.frames.push_back({ 561, 30, 33, 29 });
	walk.speed = 0.2f;

	jump.frames.push_back({ 415, 167, 46, 25 });
	AnimStatus = IDLE_RIGHT;
	jumping = false;
	onFloor = true;
	coordZ = -1.0;
	floorY = 120 + coordZ * 10; // Mapping the floor height with the coordZ
	speedY = 0;
	jumpSpeed = -7;
	moveSpeed = 2.1;
	playerZone = 1;
	previousAttackFrame.w = 0;
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
	if (AnimStatus != DEAD) {
		
		if (!inputblock) 
		{
			checkInputs();
		}
		playCurrentAnimation();

		position.y += (int)speedY;
		// Update player's hitbox
		playerHitbox->hitBox.x = position.x;
		playerHitbox->hitBox.y = position.y;
		playerHitbox->draw(App->renderer->renderer);

		
		if (position.y > floorY)
		{
			// Player died for falling over
			AnimStatus = DEAD;
		}
	}
	else // If player is dead
	{
		if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_REPEAT ) 
		{
			position.x = 1800;
			position.y = 110;
			jumping = false;
			onFloor = true;
			coordZ = -1.0;
			AnimStatus = IDLE_RIGHT;
		}
		
	}
	return UPDATE_CONTINUE;
}
void ModulePlayer::playCurrentAnimation() 
{

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
		App->renderer->Blit(graphics, position.x, position.y, &(walk.GetCurrentFrame()), 1.0f, true);//Walk Left
	}
	else if (AnimStatus == IDLE_RIGHT) {
		App->renderer->Blit(graphics, position.x, position.y, &(idle.GetCurrentFrame()), 1.0f); // Idle
	}
	else if (AnimStatus == IDLE_LEFT) {
		App->renderer->Blit(graphics, position.x, position.y, &(idle.GetCurrentFrame()), 1.0f, true); // Idle
	}
	else if (AnimStatus == ATTACK1_RIGHT) {
		SDL_Rect auxRect;
		auxRect = attack1.GetCurrentFrame();
		auxRect.x -= attack1.frames[attack1.frames.size() - 1].x;
		auxRect.y -= attack1.frames[attack1.frames.size() - 1].y;
		auxRect.w -= attack1.frames[attack1.frames.size() - 1].w;
		auxRect.h -= attack1.frames[attack1.frames.size() - 1].h;

		if (auxRect.x == 0 && auxRect.y == 0 && auxRect.w == 0 && auxRect.h == 0)
		{
			App->renderer->Blit(graphics, position.x, position.y - 20, &(attack1.GetCurrentFrame()), 1.0f); // Punches
		}
		else
		{
			App->renderer->Blit(graphics, position.x, position.y, &(attack1.GetCurrentFrame()), 1.0f); // Punches
		}
			
	}
	else if (AnimStatus == ATTACK1_LEFT)
	{
		int correctionX = 0;
		SDL_Rect auxRect;
		auxRect = attack1.GetCurrentFrame();
		auxRect.x -= attack1.frames[attack1.frames.size() - 1].x;
		auxRect.y -= attack1.frames[attack1.frames.size() - 1].y;
		auxRect.w -= attack1.frames[attack1.frames.size() - 1].w;
		auxRect.h -= attack1.frames[attack1.frames.size() - 1].h;

		correctionX = attack1.GetCurrentFrame().w - attack1.frames[0].w; // This line corrects the sprites position when the character is facing left

		if (auxRect.x == 0 && auxRect.y == 0 && auxRect.w == 0 && auxRect.h == 0)
		{
			App->renderer->Blit(graphics, position.x - correctionX, position.y - 20, &(attack1.GetCurrentFrame()), 1.0f, true); // Punches
		}
		else
		{
			App->renderer->Blit(graphics, position.x - correctionX, position.y, &(attack1.GetCurrentFrame()), 1.0f, true); // Punches
		}
	}
	else if (AnimStatus == ATTACK2_RIGHT) {
		SDL_Rect auxRect;
		auxRect = attack2.GetCurrentFrame();
		auxRect.x -= attack2.frames[attack2.frames.size() - 1].x;
		auxRect.y -= attack2.frames[attack2.frames.size() - 1].y;
		auxRect.w -= attack2.frames[attack2.frames.size() - 1].w;
		auxRect.h -= attack2.frames[attack2.frames.size() - 1].h;

		if (auxRect.x == 0 && auxRect.y == 0 && auxRect.w == 0 && auxRect.h == 0)
		{
			App->renderer->Blit(graphics, position.x, position.y, &(attack2.GetCurrentFrame()), 1.0f); // Punches
		}
		else
		{
			App->renderer->Blit(graphics, position.x, position.y, &(attack2.GetCurrentFrame()), 1.0f); // Punches
		}
		position.x += 2.8;
		if (SDL_GetTicks() - timeAttack1 >= 500)
		{
			inputblock = false;
		}

	}
	else if (AnimStatus == ATTACK2_LEFT)
	{
		int correctionX = 0;
		SDL_Rect auxRect;
		auxRect = attack2.GetCurrentFrame();
		auxRect.x -= attack2.frames[attack2.frames.size() - 1].x;
		auxRect.y -= attack2.frames[attack2.frames.size() - 1].y;
		auxRect.w -= attack2.frames[attack2.frames.size() - 1].w;
		auxRect.h -= attack2.frames[attack2.frames.size() - 1].h;

		correctionX = attack2.GetCurrentFrame().w - attack2.frames[0].w; // This line corrects the sprites position when the character is facing left

		if (auxRect.x == 0 && auxRect.y == 0 && auxRect.w == 0 && auxRect.h == 0)
		{
			App->renderer->Blit(graphics, position.x - correctionX, position.y, &(attack2.GetCurrentFrame()), 1.0f, true); // Punches
		}
		else
		{
			App->renderer->Blit(graphics, position.x - correctionX, position.y, &(attack2.GetCurrentFrame()), 1.0f, true); // Punches
		}
		position.x -= 0.8;
		if (SDL_GetTicks()-timeAttack1 >= 500) 
		{
			inputblock = false;
		}
	}
}
void ModulePlayer::checkInputs() 
{
	floorY = 120 + coordZ * 10;
	//Calculate colission with level layout
	if (!App->collisions->checkIfOnFloor())
	{
		onFloor = false;
		if (!jumping) {
			position.y += 2.5;
			coordZ += 0.2;
		}
	}
	else
	{
		if (position.y <= (int)floorY) {
			onFloor = true;
		}
	}


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
	if (AnimStatus == WALKING_LEFT || AnimStatus == JUMPING_LEFT || AnimStatus == ATTACK1_LEFT || AnimStatus == ATTACK2_LEFT)
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
	else if (AnimStatus == WALKING_RIGHT || AnimStatus == JUMPING_RIGHT || AnimStatus == ATTACK1_RIGHT || AnimStatus == ATTACK2_RIGHT)
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
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && !jumping) {
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
		floorY = 120 + coordZ * 10;
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
		floorY = 120 + coordZ * 10;
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
	if (!jumping) {
		if (App->input->GetKey(SDL_SCANCODE_K) == KEY_REPEAT) {
			if (AnimStatus == IDLE_LEFT || AnimStatus == WALKING_LEFT)
			{
				AnimStatus = ATTACK1_LEFT;
			}
			else if (AnimStatus == IDLE_RIGHT || AnimStatus == WALKING_RIGHT)
			{
				AnimStatus = ATTACK1_RIGHT;
			}
		}
		if (App->input->GetKey(SDL_SCANCODE_L) == KEY_REPEAT) {
			if (AnimStatus == IDLE_LEFT || AnimStatus == WALKING_LEFT)
			{
				AnimStatus = ATTACK2_LEFT;
			}
			else if (AnimStatus == IDLE_RIGHT || AnimStatus == WALKING_RIGHT)
			{
				AnimStatus = ATTACK2_RIGHT;
			}
			timeAttack1 = SDL_GetTicks();
			inputblock = true;
		}
	}
}