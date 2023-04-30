#include "Enemy_Fighter.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include <iostream>

Enemy_Fighter::Enemy_Fighter(int x, int y) : Enemy(x, y)
{
	//initial position

	//idle animation
	idleAnim.PushBack({ 96,29,68,66 });

	//walk animation
	walkAnim.PushBack({ 96,29,68,66 });
	walkAnim.PushBack({ 29,29,68,66 });
	walkAnim.PushBack({ 163,29,68,66 });
	walkAnim.PushBack({ 29,29,68,66 });
	walkAnim.speed = 0.1f;

	currentAnim = &walkAnim;

	//shoot animation
	hitAnim.PushBack({ 29,123,68,66 });
	hitAnim.PushBack({ 96,123,68,66 });
	hitAnim.PushBack({ 163,123,68,66 });
	hitAnim.PushBack({ 163,123,68,66 });
	hitAnim.PushBack({ 96,123,68,66 });
	hitAnim.PushBack({ 29,123,68,66 });
	hitAnim.speed = 0.14f;
	hitAnim.loop = false;

	dieAnim.PushBack({ 29,217,68,66 });
	dieAnim.PushBack({ 96,217,68,66 });
	dieAnim.PushBack({ 164,217,68,66 });
	dieAnim.speed = 0.08f;
	dieAnim.loop = false;


	//colliders
	collider = App->collisions->AddCollider({ position.x + 25, position.y + 8, 30, 61 }, Collider::Type::ENEMY, (Module*)App->enemies);
	/*feet = App->collisions->AddCollider({ position.x, position.y + 69, 83, 1 }, Collider::Type::FEET, (Module*)App->enemies);*/

}

void Enemy_Fighter::Update()
{
	std::cout << position.x << std::endl;
	if (!die)
	{
		//walk right
		if (position.x - App->player->position.x <= pdistance && position.x - App->player->position.x >= 0)
		{
			if (position.x != App->player->position.x && !shooting && !reloading)
			{
				flip = true;
				shot++;

				if (position.x - App->player->position.x >= pdistance - 170)
				{
					currentAnim = &walkAnim;
					position.x--;
				}
				else if (shot >= 100)
				{
					currentAnim = &hitAnim;
					currentAnim->Reset();
					App->audio->PlayFx(App->audio->shuriken);
					shot = 0;
					shooting = true;
				}
				else currentAnim = &idleAnim;

				pl = true;

				if (position.x <= pos2)
				{
					changedirection = true;
					flip = true;
				}
				else changedirection = false;

			}

		}
		//walk left
		else if (position.x - App->player->position.x >= -pdistance && position.x - App->player->position.x <= 0)
		{
			 if (position.x != App->player->position.x && !shooting && !reloading)
			{

				shot++;

				flip = false;

				if (position.x - App->player->position.x <= -(pdistance - 170))
				{
					currentAnim = &walkAnim;
					position.x++;
				}
				else if (shot >= 100)
				{
					currentAnim = &hitAnim;
					currentAnim->Reset();
					App->audio->PlayFx(App->audio->shuriken);
					shot = 0;
					shooting = true;
				}
				else currentAnim = &idleAnim;

				pl = true;

				if (position.x >= pos2) changedirection = true;
				else
				{
					changedirection = false;
					flip = false;
				}
			}

		}
		//walk path
		else if (!pl && !reloading && !shooting)
		{
			currentAnim = &walkAnim;
			if (position.x >= spawnPos.x + 100)
			{
				changedirection = true;
				flip = true;
			}
			else if (position.x <= spawnPos.x - 50)
			{
				changedirection = false;
				flip = false;
			}

			if (changedirection) position.x--;
			else position.x++;

			shooting = false;
			reloading = false;
		}
		else pl = false;

		if (shooting)
		{
			time++;
			if (time >= 50)
			{
				shooting = false;
				time = 0;

				////reload
				//if (bullets <= 0)
				//{
				//	currentAnim = &reloadAnim;
				//	reloading = true;
				//	bullets = 3;
				//}
			}
		}

		//reload delay
		if (reloading)
		{
			time++;
			if (time >= 100)
			{
				reloading = false;
				time = 0;
			}
		}
		collider->SetPos(position.x + 25, position.y + 8);
	}
	else if (die) currentAnim = &dieAnim;

	//feet->SetPos(position.x, position.y + 69);

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
