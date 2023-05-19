#include "Enemy_green.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include <iostream>

Enemy_green::Enemy_green(int x, int y) : Enemy(x, y)
{
	//initial position

	//idle animation
	idleAnim.PushBack({ 389,74,96,72 });

	//walk animation
	walkAnim.PushBack({ 1,74,96,72 });
	walkAnim.PushBack({ 98,74,96,72 });
	walkAnim.PushBack({ 195,74,96,72 });
	walkAnim.PushBack({ 292,74,96,72 });
	walkAnim.speed = 0.1f;

	currentAnim = &walkAnim;

	//shoot animation
	hitAnim.PushBack({ 389,74,96,72 });
	hitAnim.PushBack({ 486,74,96,72 });
	hitAnim.PushBack({ 389,1,96,72 });
	hitAnim.PushBack({ 292,1,96,72 });
	hitAnim.PushBack({ 195,1,96,72 });
	hitAnim.PushBack({ 98,1,96,72 });
	hitAnim.PushBack({ 1,1,96,72 });
	hitAnim.speed = 0.14f;
	hitAnim.loop = false;

	dieAnim.PushBack({ 1,147,96,72 });
	dieAnim.PushBack({ 98,147,96,72 });
	dieAnim.PushBack({ 195,147,96,72 });
	dieAnim.speed = 0.08f;
	dieAnim.loop = false;


	//colliders
	collider = App->collisions->AddCollider({ position.x + 25, position.y + 4, 35, 62 }, Collider::Type::ENEMY, (Module*)App->enemies);
	attack = App->collisions->AddCollider({ 0, 0, 0, 0 }, Collider::Type::ENEMY_SHOT, (Module*)App->enemies);

	/*feet = App->collisions->AddCollider({ position.x, position.y + 69, 83, 1 }, Collider::Type::FEET, (Module*)App->enemies);*/

}

void Enemy_green::Update()
{
	flipPos.x = position.x + 20;
	//std::cout << position.x << std::endl;
	if (!die)
	{
		//walk right
		if (position.x - App->player->position.x <= pdistance && position.x - App->player->position.x >= 0 && App->player->position.y >= 110 && App->player->alive)
		{
			if (position.x != App->player->position.x && !shooting && !reloading)
			{
				flip = true;
				shot++;
				if (position.x - App->player->position.x >= pdistance - 175)
				{
					currentAnim = &walkAnim;
					position.x--;
				}
				else if (shot >= 100)
				{
					currentAnim = &hitAnim;
					currentAnim->Reset();
					//App->particles->AddParticle(App->particles->patada, position.x, position.y + 30, Collider::Type::ENEMY_SHOT);
					attack->rect.w = 10;
					attack->rect.h = 10;
					attack->SetPos(position.x, position.y + 30);
					App->audio->PlayFx(App->audio->shuriken);
					shot = 0;
					shooting = true;
				}
				else {
					currentAnim = &idleAnim;
					attack->rect.w = 0;
					attack->rect.h = 0;
					attack->SetPos(0, 0);
				}
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
		else if (position.x - App->player->position.x >= -pdistance && position.x - App->player->position.x <= 0 && App->player->position.y >= 110 && App->player->alive)
		{
			if (position.x != App->player->position.x && !shooting && !reloading)
			{

				shot++;

				flip = false;

				if (position.x - App->player->position.x <= -(pdistance - 140))
				{
					currentAnim = &walkAnim;
					position.x++;
				}
				else if (shot >= 100)
				{
					currentAnim = &hitAnim;
					currentAnim->Reset();
					//App->particles->AddParticle(App->particles->patada, position.x+80, position.y + 30, Collider::Type::ENEMY_SHOT);
					attack->rect.w = 10;
					attack->rect.h = 10;
					attack->SetPos(position.x + 80, position.y + 30);
					App->audio->PlayFx(App->audio->shuriken);
					shot = 0;
					shooting = true;
				}
				else {
					attack->rect.w = 0;
					attack->rect.h = 0;
					attack->SetPos(0, 0);
					currentAnim = &idleAnim;

				}
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
		collider->SetPos(position.x + 25, position.y + 4);
		//attack->SetPos(position.x + 25, position.y + 4);
	}
	else if (die) {
		currentAnim = &dieAnim;
		collider->SetPos(position.x - 10, position.y + 30);
		collider->rect.w = 37;
		collider->rect.h = 20;
		attack->rect.w = 0;
		attack->rect.h = 0;
		attack->SetPos(0, 0);
	}

	//feet->SetPos(position.x, position.y + 69);

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
