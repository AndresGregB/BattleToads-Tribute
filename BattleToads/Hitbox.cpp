#include "Hitbox.h"
#include "Application.h"


Hitbox::Hitbox (SDL_Rect Rect, float s)
{
  hitBox = Rect;
  speed = s;
}


Hitbox::~Hitbox ()
{
}

bool
Hitbox::checkIntersection (const SDL_Rect target)
{
  if (target.x + target.w < hitBox.x ||	// Target hitbox is left of this hitbox
      hitBox.x + hitBox.w < target.x ||	// Target hitbox is right of this hitbox
      target.y + target.h < hitBox.y ||	// Target hitbox is above this hitbox
      hitBox.y + hitBox.h < target.y	// Target hitbox is below this hitbox
    )
    {
      return false;
    }
  return true;
}

void
Hitbox::draw (SDL_Renderer * renderer)
{

  if (checkIntersection (App->player->playerHitbox->hitBox))
    {
      if (!(hitBox.x == App->player->playerHitbox->hitBox.x))
	{
	  SDL_SetRenderDrawColor (renderer, 255, 0, 0, 255);

	}
    }
  else
    {
      SDL_SetRenderDrawColor (renderer, 255, 255, 255, 255);
    }

  SDL_Rect aux;
  aux.x = (int) (App->renderer->camera.x * speed) + hitBox.x * SCREEN_SIZE;
  aux.y = (int) (App->renderer->camera.y * speed) + hitBox.y * SCREEN_SIZE;
  aux.w = hitBox.w * SCREEN_SIZE;
  aux.h = hitBox.h * SCREEN_SIZE;
  //SDL_RenderFillRect(renderer, &App->player->playerHitbox->hitBox);
  SDL_RenderDrawRect (renderer, &aux);
}
