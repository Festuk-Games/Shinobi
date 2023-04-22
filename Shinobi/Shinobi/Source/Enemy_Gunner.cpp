#include "Enemy_Gunner.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"

Enemy_Gunner::Enemy_Gunner(int x, int y) : Enemy(x, y)
{
	idleAnim.PushBack({11,165,36,59});
	idleAnim.PushBack({ 68,165,36,59 });
	idleAnim.PushBack({ 143,165,36,59 });
	idleAnim.PushBack({ 68,165,36,59 });
	idleAnim.speed = 0.05f;

	currentAnim = &idleAnim;

	collider = App->collisions->AddCollider({0, 0, 36, 59}, Collider::Type::NONE, (Module*)App->enemies);

	position.x = 550;
	position.y = 148;
}

void Enemy_Gunner::Update()
{

	//waveRatio += waveRatioSpeed;
	//position.x = spawnPos.x + (waveHeight * sinf(waveRatio));
	
	if (position.x - App->player->position.x <= pdistance && position.x - App->player->position.x >= 0)
	{
		if (position.x != App->player->position.x)
		{
			flip = true;
			position.x--;
			pl = true;
			if (position.x <= pos2)
			{
				changedirection = true;
				flip = true;
			}
			else changedirection = false;

		}
		
	}
	else if (position.x - App->player->position.x >= -pdistance && position.x - App->player->position.x <= 0)
	{
		if (position.x != App->player->position.x)
		{
			flip = false;
			position.x++;
			pl = true;
			if (position.x >= pos2) changedirection = true;
			else
			{
				changedirection = false;
				flip = false;
			}
		}

	}
	else if (!pl)
	{
		if (position.x >= pos2)
		{
			changedirection = true;
			flip = true;
		}
		else if (position.x <= pos1)
		{
			changedirection = false;
			flip = false;
		}

		if (changedirection) position.x--;
		else position.x++;
	}
	else 
	{
		pl = false;
		/*if (position.x - App->player->position.x >= pdistance) flip = false;
		else if(position.x - App->player->position.x <= 0) flip = true;*/
	}


	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
