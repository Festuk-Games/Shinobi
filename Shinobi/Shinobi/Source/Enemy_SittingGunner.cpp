#include "Enemy_SittingGunner.h"
using namespace std;
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include <iostream>

Enemy_SittingGunner::Enemy_SittingGunner(int x, int y) : Enemy(x, y)
{
	//initial position

	//idle animation
	idleAnim.PushBack({ 225,127,83,69 });

	//walk animation

	currentAnim = &walkAnim;

	//shoot animation
	shootAnim.PushBack({ 225,127,83,69 });
	shootAnim.PushBack({ 307,127,83,69 });
	shootAnim.speed = 0.1f;
	shootAnim.loop = false;

	dieAnim.PushBack({ 30,418,83,69 });
	dieAnim.PushBack({ 112,418,83,69 });
	dieAnim.PushBack({ 112,418,83,69 });
	dieAnim.PushBack({ 0,0,0,0 });
	dieAnim.speed = 0.05f;
	dieAnim.loop = false;


	//colliders
	collider = App->collisions->AddCollider({ position.x, position.y + 47, 84, 22 }, Collider::Type::ENEMY, (Module*)App->enemies);
	/*feet = App->collisions->AddCollider({ position.x, position.y + 69, 83, 1 }, Collider::Type::FEET, (Module*)App->enemies);*/
}
void Enemy_SittingGunner::Update()
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
				App->particles->AddParticle(App->particles->enemyshot, position.x, position.y+50, Collider::Type::ENEMY_SHOT);
				shot = 0;
				shooting = true;
				bullets--;
			}
			else if (position.x != App->player->position.x && !shooting && !reloading)
			{
				flip = true;

				currentAnim = &idleAnim;

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
				App->particles->AddParticle(App->particles->enemyshot, position.x + 69, position.y + 50, Collider::Type::ENEMY_SHOT);
				shot = 0;
				shooting = true;
				bullets--;
			}
			else if (position.x != App->player->position.x && !shooting && !reloading)
			{
				flip = false;
				currentAnim = &idleAnim;

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

			shooting = false;
		}
		else pl = false;

		if (shooting)
		{
			time++;
			if (time >= 50)
			{
				shooting = false;
				time = 0;
				bullets= bullets+1;
			}
		}

		collider->SetPos(position.x, position.y + 47);
	}
	else if (die) currentAnim = &dieAnim;

	//feet->SetPos(position.x, position.y + 69);

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}