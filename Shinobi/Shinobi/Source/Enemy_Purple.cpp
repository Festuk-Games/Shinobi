
using namespace std;
#include "Enemy_Purple.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include <iostream>

Enemy_Purple::Enemy_Purple(int x, int y) : Enemy(x, y)
{
	//initial position

	//idle animation
	idleAnim.PushBack({ 69,15,40,50 });

	//walk animation
	walkAnim.PushBack({ 12,15,40,50 });
	walkAnim.PushBack({ 69,15,40,50 });
	walkAnim.PushBack({ 125,15,40,50 });
	walkAnim.PushBack({ 181,15,40,50 });
	walkAnim.speed = 0.05f;

	currentAnim = &walkAnim;

	//shoot animation
	hitAnim.PushBack({ 20,79,30,66 });
	hitAnim.PushBack({ 68,79,30,65 });
	hitAnim.PushBack({ 119,83,40,65 });
	hitAnim.PushBack({ 181,84,33,65 });
	hitAnim.PushBack({ 5,156,56,62 });
	hitAnim.PushBack({ 74,160,30,59 });
	hitAnim.speed = 0.14f;
	hitAnim.loop = false;

	dieAnim.PushBack({ 123,155,38,66 });
	dieAnim.PushBack({ 181,160,40,64 });
	dieAnim.PushBack({ 23,232,38,44 });
	dieAnim.speed = 0.08f;
	dieAnim.loop = false;


	//colliders
	collider = App->collisions->AddCollider({ position.x, position.y, 40, 50 }, Collider::Type::ENEMY, (Module*)App->enemies);
	attack = App->collisions->AddCollider({ 0, 0, 0, 0 }, Collider::Type::ENEMY_SHOT, (Module*)App->enemies);

	/*feet = App->collisions->AddCollider({ position.x, position.y + 69, 83, 1 }, Collider::Type::FEET, (Module*)App->enemies);*/

}

void Enemy_Purple::Update()
{
	flipPos.x = position.x;
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
			cout << position.y<<endl;
			position.y=139;
			collider->rect.h = 70;
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
		else
		{
			position.y = 159;
			collider->rect.h = 50;
			collider->SetPos(position.x, position.y);
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
		//collider->SetPos(position.x, position.y);
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
