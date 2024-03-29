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
	shootAnim.PushBack({ 389,1,96,72 });
	shootAnim.PushBack({ 292,1,96,72 });
	shootAnim.PushBack({ 195,1,96,72 });
	shootAnim.PushBack({ 98,1,96,72 });
	shootAnim.PushBack({ 1,1,96,72 });
	shootAnim.speed = 0.14f;
	shootAnim.loop = false;


	dieAnim.PushBack({ 195,147,96,72 });
	dieAnim.PushBack({ 98,147,96,72 });
	dieAnim.PushBack({ 1,147,96,72 });
	dieAnim.PushBack({ 1,147,96,72 });
	dieAnim.PushBack({ 0,0,0,0 });
	dieAnim.speed = 0.08f;
	dieAnim.loop = false;


	//colliders
	collider = App->collisions->AddCollider({ position.x + 25, position.y + 12, 38, 68 }, Collider::Type::ENEMY, (Module*)App->enemies);
	attack = App->collisions->AddCollider({ 0, 0, 0, 0 }, Collider::Type::ENEMY_SHOT, (Module*)App->enemies);

	/*feet = App->collisions->AddCollider({ position.x, position.y + 69, 83, 1 }, Collider::Type::FEET, (Module*)App->enemies);*/

}

void Enemy_green::Update()
{
		flipPos.x = position.x;
	//std::cout << position.x << std::endl;
	if (!die)
	{
		//walk right
		if (position.x - App->player->position.x <= pdistance && position.x - App->player->position.x >= 0 && App->player->position.y >= 110)
		{
			idle = false;
			shot++;
			if (shot >= 100 && !reloading && bullets >= 1)
			{
				if (currentAnim != &shootAnim)
				{
					currentAnim = &shootAnim;
					currentAnim->Reset();
				}
				currentAnim->Update();
				App->audio->PlayFx(App->audio->shuriken);
				App->particles->espada.speed = iPoint(-5, 0);
				if (shot >= 112)
				{
					shooting = true;
					App->particles->AddParticle(App->particles->espada, position.x+20, position.y + 15, Collider::Type::ENEMY_SHOT);
					shot = 0;
					
				}
			}
			else if (position.x != App->player->position.x && !shooting && !reloading)
			{
				flip = true;

				if (position.x - App->player->position.x >= pdistance - 40)
				{
					currentAnim = &walkAnim;
					idle = false;
					position.x--;
				}
				else {
					currentAnim = &idleAnim;
					idle = true;
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
		else if (position.x - App->player->position.x >= -pdistance && position.x - App->player->position.x <= 0 && App->player->position.y >= 110)
		{
			idle = false;
			shot++;
			if (shot >= 100 && !reloading && bullets >= 1)
			{
				if (currentAnim != &shootAnim)
				{
					currentAnim = &shootAnim;
					currentAnim->Reset();
				}
				currentAnim->Update();
				App->audio->PlayFx(App->audio->shuriken);
				App->particles->espada.speed = iPoint(5, 0);
				if (shot >= 112)
				{
					shooting = true;
					App->particles->AddParticle(App->particles->espada, position.x+69, position.y + 15, Collider::Type::ENEMY_SHOT);
					shot = 0;
					
				}
			}
			else if (position.x != App->player->position.x && !shooting && !reloading)
			{
				flip = false;

				if (position.x - App->player->position.x <= -(pdistance - 40))
				{
					currentAnim = &walkAnim;
					idle = false;
					position.x++;
				}
				else {
					currentAnim = &idleAnim;
					idle = true;
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
			idle = false;
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

		if (shooting || idle)
		{
			/*cout << position.y<<endl;
			position.y=135;*/

			collider->rect.h = 65;
			collider->SetPos(position.x + 25, position.y + 8);
			time++;
			if (time >= 50)
			{
				shooting = false;
				time = 0;

			}
		}
		else if (currentAnim==&walkAnim)
		{
			/*position.y = 135;*/
			collider->rect.h = 51;
			collider->SetPos(position.x + 28, position.y + 23);
		}
		
		
		//collider->SetPos(position.x+28, position.y + 6);
	}
	else if (die) currentAnim = &dieAnim;

	//feet->SetPos(position.x, position.y + 69);

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
