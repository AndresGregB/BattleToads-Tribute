#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "SDL/include/SDL.h"
#include "ModuleAudio.h"

ModulePlayer::ModulePlayer(bool start_enabled) : Module(start_enabled)
{
	inputblock = false;
	lives = 5;
	liveEmpty.x = 0;
	liveEmpty.y = 0;
	liveEmpty.w = 8;
	liveEmpty.h = 11;

	liveFull.x = 11;
	liveFull.y = 0;
	liveFull.w = 8;
	liveFull.h = 11;

	position.x = 200;//200
	position.y = 110;
	SDL_Rect PHitbox;

	PHitbox.x = position.x;
	PHitbox.y = position.y;
	PHitbox.w = 26;
	PHitbox.h = 34;

	playerHitbox = new Hitbox(PHitbox, 1.0f);

	PHitbox.x = position.x + playerHitbox->hitBox.w;
	PHitbox.y = position.y - 5;
	PHitbox.w = 26;
	PHitbox.h = 20;

	rightAttack1H = new Hitbox(PHitbox, 1.0f);

	PHitbox.x = position.x - playerHitbox->hitBox.w;
	PHitbox.y = position.y - 5;
	PHitbox.w = 26;
	PHitbox.h = 20;

	leftAttack1H = new Hitbox(PHitbox, 1.0f);

	PHitbox.x = position.x + playerHitbox->hitBox.w/2;
	PHitbox.y = position.y;
	PHitbox.w = 26;
	PHitbox.h = 25;

	rightAttack2H = new Hitbox(PHitbox, 1.0f);

	PHitbox.x = position.x - playerHitbox->hitBox.w/2;
	PHitbox.y = position.y;
	PHitbox.w = 26;
	PHitbox.h = 25;

	leftAttack2H = new Hitbox(PHitbox, 1.0f);

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

	die.frames.push_back({549,118,38,34});
	die.speed = 0.1;

	end.frames.push_back({0,0,480,360});
	end.speed = 0.0f;

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
	interfaceX = position.x;

}

ModulePlayer::~ModulePlayer()
{
	// Homework : check for memory leaks
}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");
	attack1SoundId = App->audio->LoadFx("./Music/attack1.ogg");
	attack2SoundId = App->audio->LoadFx("./Music/attack2.ogg");
	graphics = App->textures->Load("./Sprites/rash.png");
	endScreen = App->textures->Load("./Sprites/ending.png");
	life = App->textures->Load("./Sprites/lifeSprite.png");

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);
	//delete playerHitbox;
	/*delete leftAttack1H;
	delete leftAttack2H;
	delete rightAttack1H;
	delete rightAttack2H;*/

	return true;
}

// Update
update_status ModulePlayer::Update()
{
	
		if (AnimStatus != DEAD)
		{

			if (!inputblock)
			{
				checkInputs();
			}
			position.y += (int)speedY;
			// Update player's hitboxes
			ModulePlayer::updatePlayerHitboxes();
			if (position.y > floorY || lives <= 0)
			{
				// Player died
				lives = 0;
				AnimStatus = DEAD;
			}
		}
		else // If player is dead
		{
			if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_REPEAT)
			{
				position.x = 200;
				position.y = 110;
				App->renderer->camera.x = -3 * position.x + 400;
				jumping = false;
				onFloor = true;
				inputblock = false;
				coordZ = -1.0;
				floorY = 120 + coordZ * 10;
				lives = 5;
				AnimStatus = IDLE_RIGHT;
				App->renderer->cameraLocked = false;
				App->collisions->enemies.clear();
				App->collisions->enemiesControler->restoreSpawnpoints();
			}

		}
		playCurrentAnimation();
		drawLives();
	if(position.x > 2600 && !App->collisions->enemiesControler->checkSpawningPoints()) 
	{
		lives = 0;
		App->renderer->Blit(endScreen, interfaceX-160, -30, &(end.GetCurrentFrame()), 1.0,2,false);
	}
	return UPDATE_CONTINUE;
}
void ModulePlayer::playCurrentAnimation() 
{
	App->collisions->drawEnemiesBehind();
	// Apply animation depending on AnimStatus
	if (AnimStatus == DEAD)
	{
		if (!onFloor) {
			position.y += 1.2;
		}
		App->renderer->Blit(graphics, position.x, position.y, &(die.GetCurrentFrame()), 1.0f);
	}
	else if (AnimStatus == JUMPING_RIGHT) {
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
		App->collisions->checkAttackVsEnemies(rightAttack1H, coordZ);
		App->audio->PlayFx(attack1SoundId,0);
			
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
		App->collisions->checkAttackVsEnemies(leftAttack1H, coordZ);
		App->audio->PlayFx(attack1SoundId, 0);
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
		App->collisions->checkAttackVsEnemies(rightAttack2H, coordZ);
		App->audio->PlayFx(attack2SoundId, 0);

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
		position.x -= 1.9;
		if (SDL_GetTicks()-timeAttack1 >= 500) 
		{
			inputblock = false;
		}
		App->collisions->checkAttackVsEnemies(leftAttack2H, coordZ);
		App->audio->PlayFx(attack2SoundId, 0);
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
void ModulePlayer::updatePlayerHitboxes() 
{
	playerHitbox->hitBox.x = position.x;
	playerHitbox->hitBox.y = position.y;
	//playerHitbox->draw(App->renderer->renderer);

	rightAttack1H->hitBox.x = position.x + playerHitbox->hitBox.w;
	rightAttack1H->hitBox.y = position.y - 5;
	//rightAttack1H->draw(App->renderer->renderer);

	leftAttack1H->hitBox.x = position.x - playerHitbox->hitBox.w;
	leftAttack1H->hitBox.y = position.y - 5;
	//leftAttack1H->draw(App->renderer->renderer);

	leftAttack2H->hitBox.x = position.x - playerHitbox->hitBox.w / 2;
	leftAttack2H->hitBox.y = position.y;
	//leftAttack2H->draw(App->renderer->renderer);

	rightAttack2H->hitBox.x = position.x + playerHitbox->hitBox.w / 2;
	rightAttack2H->hitBox.y = position.y;
	//rightAttack2H->draw(App->renderer->renderer);


}
void ModulePlayer::drawLives() 
{
	for (int i = 0; i < 5;i++) 
	{
		if (App->renderer->cameraLocked) 
		{
			App->renderer->Blit(life, (interfaceX - 120) + i * 10, 5, &liveEmpty, 1.0f);
		}
		else 
		{
			App->renderer->Blit(life, (position.x - 120) + i * 10, 5, &liveEmpty, 1.0f);
		}
		
	}
	for (int i = 0; i < lives; i++)
	{
		if (App->renderer->cameraLocked)
		{
			App->renderer->Blit(life, (interfaceX - 120) + i * 10, 5, &liveFull, 1.0f);
		}
		else
		{
			App->renderer->Blit(life, (position.x - 120) + i * 10, 5, &liveFull, 1.0f);
		}
	}
}
void ModulePlayer::takeHit()
{
	if (SDL_GetTicks()-inmunityTime > 1000) 
	{
		lives--;
		inmunityTime = SDL_GetTicks();
	}
	
}