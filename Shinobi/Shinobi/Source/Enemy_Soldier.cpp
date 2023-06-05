#include "Enemy_Soldier.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include <iostream>

Enemy_Soldier::Enemy_Soldier(int x, int y) : Enemy(x, y)
{
	//initial position

	//idle animation
	idleAnim.PushBack({ 123,29,48,62 });

	//walk animation
	walkAnim.PushBack({ 29,29,48,62 });
	walkAnim.PushBack({ 123,29,48,62 });
	walkAnim.PushBack({ 76,29,48,62 });
	walkAnim.PushBack({ 123,29,48,62 });
	walkAnim.speed = 0.1f;

	currentAnim = &walkAnim;

	//shoot animation
	hitAnim.PushBack({ 29,119,48,62 });
	hitAnim.PushBack({ 181,119,48,62 });
	hitAnim.PushBack({ 29,119,48,62 });
	hitAnim.speed = 0.14f;
	hitAnim.loop = false;

	dieAnim.PushBack({ 199,29,48,62 });
	dieAnim.PushBack({ 246,29,48,62 });
	dieAnim.PushBack({ 246,29,48,62 });
	dieAnim.PushBack({ 0,0,0,0 });
	dieAnim.speed = 0.08f;
	dieAnim.loop = false;


	//colliders
	collider = App->collisions->AddCollider({ position.x-3, position.y, 30, 63}, Collider::Type::ENEMY, (Module*)App->enemies);
	attack = App->collisions->AddCollider({ 0, 0, 0, 0 }, Collider::Type::ENEMY_SHOT, (Module*)App->enemies);
	/*feet = App->collisions->AddCollider({ position.x, position.y + 69, 83, 1 }, Collider::Type::FEET, (Module*)App->enemies);*/

}

void Enemy_Soldier::Update()
{
	flipPos.x = position.x -15;
	//std::cout << position.x << std::endl;
	if (!die)
	{
		//walk right
		if (position.x - App->player->position.x <= pdistance && position.x - App->player->position.x >= 0 && App->player->position.y >= 110 && !isCollidingRight)
		{
			if (position.x != App->player->position.x && !shooting && !reloading)
			{
				flip = true;
				shot++;

				if (position.x - App->player->position.x >= pdistance - 160)
				{
					currentAnim = &walkAnim;
					position.x--;
					position.x--;
				}
				else if (shot >= 100)
				{
					currentAnim = &hitAnim;
					currentAnim->Reset();
					//App->particles->AddParticle(App->particles->patada, position.x, position.y + 30, Collider::Type::ENEMY_SHOT);
					attack = App->collisions->AddCollider({ position.x-5, position.y + 30, 10, 10 }, Collider::Type::ENEMY_SHOT, (Module*)App->enemies);
					//attack->SetPos(position.x, position.y + 30);
					App->audio->PlayFx(App->audio->shuriken);
					shot = 0;
					shooting = true;
				}
				else {
					currentAnim = &idleAnim;
					/*attack->rect.w = 0;
					attack->rect.h = 0;*/
					attack->pendingToDelete = true;
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
		else if (position.x - App->player->position.x >= -pdistance && position.x - App->player->position.x <= 0 && App->player->position.y >= 110 && !isCollidingLeft)
		{
			if (position.x != App->player->position.x && !shooting && !reloading)
			{

				shot++;

				flip = false;

				if (position.x - App->player->position.x <= -(pdistance - 180))
				{
					currentAnim = &walkAnim;
					position.x++;
					position.x++;
				}
				else if (shot >= 100)
				{
					currentAnim = &hitAnim;
					currentAnim->Reset();
					//App->particles->AddParticle(App->particles->patada, position.x+80, position.y + 30, Collider::Type::ENEMY_SHOT);
					attack = App->collisions->AddCollider({ position.x + 25, position.y + 30, 10, 10 }, Collider::Type::ENEMY_SHOT, (Module*)App->enemies);
					//attack->SetPos(position.x+80, position.y+30);
					App->audio->PlayFx(App->audio->shuriken);
					shot = 0;
					shooting = true;
				}
				else {
					attack->rect.w = 0;
					attack->rect.h = 0;
					attack->pendingToDelete = true;
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
			if (time >= 20)
			{
				shooting = false;
				time = 0;
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
		collider->SetPos(position.x, position.y);
	}
	else if (die) {
	currentAnim = &dieAnim;
	/*collider->SetPos(position.x-10, position.y + 30);
	collider->rect.w = 37;
	collider->rect.h = 20;*/
	attack->rect.w = 0;
	attack->rect.h = 0;
	attack->SetPos(0, 0);
	attack->pendingToDelete = true;
	}

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
