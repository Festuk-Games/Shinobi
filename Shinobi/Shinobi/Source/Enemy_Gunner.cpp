#include "Enemy_Gunner.h"
using namespace std;
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include <iostream>

Enemy_Gunner::Enemy_Gunner(int x, int y) : Enemy(x, y)
{
	//initial position

	//idle animation
	idleAnim.PushBack({ 30,30,83,69 });

	//walk animation
	walkAnim.PushBack({30,224,83,69});
	walkAnim.PushBack({ 112,224,83,69 });
	walkAnim.PushBack({ 30,224,83,69 });
	walkAnim.PushBack({ 195,224,83,69 });
	walkAnim.speed = 0.05f;

	currentAnim = &walkAnim;

	//shoot animation
	shootAnim.PushBack({ 30,30,83,69 });
	shootAnim.PushBack({ 112,30,83,69 });
	shootAnim.PushBack({ 30,30,83,69 });
	shootAnim.speed = 0.1f;
	shootAnim.loop = false;

	preshootAnim.PushBack({ 389,30,83,69 });
	preshootAnim.speed = 0.1f;
	preshootAnim.loop = false;

	//reload animation
	reloadAnim.PushBack({ 225,30,83,69 });
	reloadAnim.PushBack({ 307,30,83,69 });
	reloadAnim.speed = 0.05f;

	dieAnim.PushBack({ 30,418,83,69 });
	dieAnim.PushBack({ 112,418,83,69 });
	dieAnim.speed = 0.05f;
	dieAnim.loop = false;


	//colliders
	collider = App->collisions->AddCollider({position.x+20, position.y+8, 45, 61}, Collider::Type::ENEMY, (Module*)App->enemies);
	/*feet = App->collisions->AddCollider({ position.x, position.y + 69, 83, 1 }, Collider::Type::FEET, (Module*)App->enemies);*/
}
void Enemy_Gunner::Update()
{
	flipPos.x = position.x;
	//std::cout << position.x << std::endl;
	if (!die)
	{
		//walk right
		if (position.x - App->player->position.x <= pdistance && position.x - App->player->position.x >= 0 && App->player->position.y >= 110)
		{
			
			shot++;
			if (shot >= 100 && !reloading && bullets >= 1)
			{
				currentAnim = &shootAnim;
				currentAnim->Reset();
				App->audio->PlayFx(App->audio->shuriken);
				App->particles->enemyshot.speed = iPoint(-5, 0);
				App->particles->AddParticle(App->particles->enemyshot, position.x, position.y + 25, Collider::Type::ENEMY_SHOT);
				shot = 0;
				shooting = true;
				bullets--;
			}
			else if (position.x != App->player->position.x && !shooting && !reloading)
			{
				flip = true;

				if (position.x - App->player->position.x >= pdistance - 40)
				{
					currentAnim = &walkAnim;
					position.x--;
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
		else if (position.x - App->player->position.x >= -pdistance && position.x - App->player->position.x <= 0 && App->player->position.y >= 110)
		{
			shot++;
			if (shot >= 100 && !reloading && bullets >= 1)
			{
				currentAnim = &shootAnim;
				currentAnim->Reset();
				App->audio->PlayFx(App->audio->shuriken);
				App->particles->enemyshot.speed = iPoint(5, 0);
				App->particles->AddParticle(App->particles->enemyshot, position.x +69, position.y + 25, Collider::Type::ENEMY_SHOT);
				shot = 0;
				shooting = true;
				bullets--;
			}
			else if (position.x != App->player->position.x && !shooting && !reloading)
			{
				flip = false;

				if (position.x - App->player->position.x <= -(pdistance - 40))
				{
					currentAnim = &walkAnim;
					position.x++;
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

				//reload
				if (bullets <= 0)
				{
					currentAnim = &reloadAnim;
					reloading = true;
					bullets = 3;
				}
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
		collider->SetPos(position.x+20, position.y + 8);
	}
	else if (die) currentAnim = &dieAnim;

	//feet->SetPos(position.x, position.y + 69);

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
