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
class ModulePlayer:public Module
{
public:
  ModulePlayer (bool start_enabled = true);
   ~ModulePlayer ();

  bool Start ();
  update_status Update ();
  bool CleanUp ();

  SDL_Texture *graphics = nullptr;
  SDL_Texture *life = nullptr;
  SDL_Texture *endScreen = nullptr;


  iPoint position;


  int playerZone;
  int lives;
  int interfaceX;
  Hitbox *playerHitbox;
  Hitbox *rightAttack1H;
  Hitbox *leftAttack1H;
  Hitbox *rightAttack2H;
  Hitbox *leftAttack2H;

  anim_status AnimStatus;
  bool jumping, onFloor;
  float floorY;
  float coordZ;
  void takeHit ();

private:
  void playCurrentAnimation ();
  void checkInputs ();
  void drawLives ();
  void updatePlayerHitboxes ();

  Animation idle;
  Animation walk;
  Animation attack1;
  Animation attack2;
  Animation jump;
  Animation die;
  Animation end;
  SDL_Rect previousAttackFrame;
  SDL_Rect liveEmpty, liveFull;
  float speedY;
  float timeAttack1;
  float inmunityTime;
  int jumpSpeed;
  float moveSpeed;
  bool inputblock;
  unsigned int attack1SoundId;
  unsigned int attack2SoundId;
};

#endif // __MODULEPLAYER_H__
