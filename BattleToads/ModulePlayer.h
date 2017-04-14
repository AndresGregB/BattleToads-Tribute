#ifndef __MODULEPLAYER_H__
#define __MODULEPLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "Point.h"
#include "Hitbox.h"

struct SDL_Texture;
enum anim_status
{
	IDLE_RIGHT,
	IDLE_LEFT,
	WALKING_RIGHT,
	WALKING_LEFT,
	JUMPING,
	ATTACKING,
	JUMPING_RIGHT,
	JUMPING_LEFT,
	DEAD,
	ATTACK1_RIGHT,
	ATTACK1_LEFT,
	ATTACK2_RIGHT,
	ATTACK2_LEFT
};
class ModulePlayer : public Module
{
public:
	ModulePlayer(bool start_enabled = true);
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	Animation idle;
	Animation walk;
	Animation attack1;
	Animation attack2;
	Animation jump;

	iPoint position;
	float speedY;
	float coordZ;
	int jumpSpeed;
	int moveSpeed;

	int playerZone;
	Hitbox* playerHitbox;

	anim_status AnimStatus;
	bool jumping, onFloor;
	float floorY;

private:
	void ModulePlayer::playCurrentAnimation();
	void ModulePlayer::checkInputs();
	SDL_Rect previousAttackFrame;
};

#endif // __MODULEPLAYER_H__