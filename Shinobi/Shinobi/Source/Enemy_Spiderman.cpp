#include "Enemy_Spiderman.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include <iostream>

Enemy_Spiderman::Enemy_Spiderman(int x, int y) : Enemy(x, y)
{
	//initial position

	//idle animation
	idleAnim.PushBack({ 7,10,45,54 });

	//walk animation
	walkAnim.PushBack({ 7,10,45,54 });
	walkAnim.PushBack({ 53,10,45,54 });
	walkAnim.PushBack({ 99,10,45,54 });
	walkAnim.PushBack({ 7,73,45,54 });
	walkAnim.speed = 0.1f;

	currentAnim = &walkAnim;

	//shoot animation
	hitAnim.PushBack({ 7,138,45,54 });
	hitAnim.PushBack({ 53,138,45,54 });
	hitAnim.speed = 0.14f;
	hitAnim.loop = false;

	jumpAnim.PushBack({ 53,73,45,54 });
	jumpAnim.PushBack({ 99,73,45,54 });
	jumpAnim.PushBack({ 145,73,45,54 });
	jumpAnim.speed = 0.1f;
	jumpAnim.loop = false;

	dieAnim.PushBack({ 7,198,45,54 });
	dieAnim.PushBack({ 53,198,45,54 });
	dieAnim.PushBack({ 99,198,45,54 });
	dieAnim.speed = 0.1f;
	dieAnim.loop = false;


	//colliders
	collider = App->collisions->AddCollider({ position.x + 25, position.y + 3, 35, 50 }, Collider::Type::ENEMY, (Module*)App->enemies);
	attack = App->collisions->AddCollider({ 0, 0, 0, 0 }, Collider::Type::ENEMY_SHOT, (Module*)App->enemies);
	isSpiderman = true;

	/*feet = App->collisions->AddCollider({ position.x, position.y + 69, 83, 1 }, Collider::Type::FEET, (Module*)App->enemies);*/

}

void Enemy_Spiderman::Update()
{
	flipPos.x = position.x + 20;
	std::cout << position.y << std::endl;
	if (!die)
	{
		//walk right
		if (position.x - App->player->position.x <= 50 && position.x - App->player->position.x >= 0 && App->player->alive && !isCollidingRight)
		{
			spawnPos.x = position.x - 100;
			isCollidingLeft = false;
			if (position.x != App->player->position.x && !shooting && !reloading)
			{

				flip = true;
				shot++;
				if (position.x - App->player->position.x >= -10 && position.x - App->player->position.x <= 10)
				{
					isSpiderman = false;
				}
				if (position.x - App->player->position.x >= pdistance - 175)
				{
					if (jump && currentAnim != &jumpAnim)
					{
						currentAnim = &jumpAnim;
						currentAnim->Reset();
					}
					else if (jump || (!jump && !ground)) currentAnim = &jumpAnim;
					else currentAnim = &walkAnim;
					position.x--;
				}
				pl = true;

				if (position.x <= pos2)
				{
					changedirection = true;
					flip = true;
				}
				else changedirection = false;

				if (!isSpiderman && ground)
				{
					if (position.x - App->player->position.x <= 1000 && position.x - App->player->position.x >= 0)
					{
						currentAnim = &hitAnim;
						currentAnim->Reset();
						int posicion = App->player->position.x;
						position.x = posicion;
						reloading = true;
					}
				}
			}

		}

		//walk left
		else if (position.x - App->player->position.x >= -50 && position.x - App->player->position.x <= 0 && App->player->alive && !isCollidingLeft)
		{
			spawnPos.x = position.x + 50;
			isCollidingRight = false;
			if (position.x != App->player->position.x && !shooting && !reloading)
			{
				shot++;
				flip = false;

				if (position.x - App->player->position.x <= 10 && position.x - App->player->position.x >= -10)
				{
					isSpiderman = false;
				}

				if (position.x - App->player->position.x <= -(pdistance - 140) && isSpiderman && !reloading)
				{
					if (jump && currentAnim != &jumpAnim)
					{
						currentAnim = &jumpAnim;
						currentAnim->Reset();
					}
					else if (jump || (!jump && !ground)) currentAnim = &jumpAnim;
					else currentAnim = &walkAnim;
					position.x++;
				}
				pl = true;

				if (position.x >= pos2) changedirection = true;
				else
				{
					changedirection = false;
					flip = false;
				}
				if (!isSpiderman && ground)
				{
					if (App->player->position.x - position.x >= -1000 && position.x - App->player->position.x <= 0)
					{
						currentAnim = &hitAnim;
						currentAnim->Reset();
						int posicion = App->player->position.x;

						position.x = posicion;
						reloading = true;
					}
				}
			}
		}

		//walk path
		if (!pl && !reloading && !shooting)
		{
			if (!jump) currentAnim = &walkAnim;
			if (position.x >= spawnPos.x + 100 || isCollidingLeft)
			{
				isCollidingLeft = false;
				changedirection = true;
				flip = true;
			}
			else if (position.x <= spawnPos.x - 50 || isCollidingRight)
			{
				isCollidingRight = false;
				changedirection = false;
				flip = false;
			}

			if (changedirection)
			{
				flip = true;
				position.x--;
			}
			else
			{
				flip = false;
				position.x++;
			}

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
		collider->SetPos(position.x + 25, position.y + 3);

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
	jump = false;
	//feet->SetPos(position.x, position.y + 69);

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}