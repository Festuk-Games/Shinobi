
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
	idleAnim.PushBack({ 6,19,54,72 });

	//walk animation
	walkAnim.PushBack({ 6,19,54,72 });
	walkAnim.PushBack({ 61,19,54,72 });
	walkAnim.PushBack({ 116,19,54,72 });
	walkAnim.PushBack({ 171,19,54,72 });
	walkAnim.speed = 0.08f;

	currentAnim = &walkAnim;

	//shoot animation
	hitAnim.PushBack({ 6,92,54,72 });
	hitAnim.PushBack({ 61,92,54,72 });
	hitAnim.PushBack({ 116,92,54,72 });
	hitAnim.PushBack({ 171,92,54,72 });
	hitAnim.PushBack({ 6,165,54,72 });
	hitAnim.PushBack({ 61,165,54,72 });
	hitAnim.speed = 0.14f;
	hitAnim.loop = false;

	dieAnim.PushBack({ 171,165,54,72 });
	dieAnim.PushBack({ 6,238,54,72 });
	dieAnim.PushBack({ 6,238,54,72 });
	dieAnim.PushBack({ 0,0,0,0 });
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
	//std::cout << "x:" << collider->rect.x << std::endl;
	//std::cout << "y:" << collider->rect.y << std::endl;
	//std::cout << "h:" << collider->rect.h << std::endl;
	//std::cout << "w:" << collider->rect.w << std::endl;
	if (!die)
	{
		//walk right
		if (position.x - App->player->position.x <= pdistance && position.x - App->player->position.x >= 0 && App->player->alive && !isCollidingRight
			&& (position.y <= 100 && App->player->L2 || position.y >= 100 && !App->player->L2))
		{
			isCollidingLeft = false;
			if (position.x != App->player->position.x && !shooting && !reloading)
			{
				flip = true;
				shot++;
				if (position.x - App->player->position.x >= 50)
				{
					currentAnim = &walkAnim;
					position.x--;
				}
				else if (shot >= 100 && position.x - App->player->position.x <= 35)
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
		else if (position.x - App->player->position.x >= -pdistance && position.x - App->player->position.x <= 0 && App->player->alive && !isCollidingLeft
			&& (position.y <= 100 && App->player->L2 || position.y >= 100 && !App->player->L2) && 
			(App->player->currentAnimation != &App->player->jumpDownFloorAnim || App->player->currentAnimation != &App->player->jumpUpFloorAnim))
		{
			isCollidingRight = false;
			if (position.x != App->player->position.x && !shooting && !reloading)
			{

				shot++;

				flip = false;

				if (position.x - App->player->position.x <= -50)
				{
					currentAnim = &walkAnim;
					position.x++;
				}
				else if (shot >= 100 && position.x - App->player->position.x >= -35)
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
			if (position.x >= spawnPos.x || isCollidingLeft)
			{
				isCollidingLeft = false;
				changedirection = true;
				flip = true;
			}
			else if (position.x <= spawnPos.x || isCollidingRight)
			{
				isCollidingRight = false;
				changedirection = false;
				flip = false;
			}

			if (changedirection && position.x != spawnPos.x)
			{
				flip = true;
				position.x--;
			}
			else if (position.x != spawnPos.x)
			{
				flip = false;
				position.x++;
			}
			else currentAnim = &idleAnim;

			shooting = false;
			reloading = false;
		}
		else pl = false;

		if (shooting)
		{
			cout << position.y<<endl;
			position.y=135;
			collider->rect.h = 65;
			collider->SetPos(position.x+5, position.y+8);
			time++;
			if (time >= 50)
			{
				shooting = false;
				time = 0;

			}
		}
		else
		{
			position.y = 135;
			collider->rect.h = 50;
			collider->SetPos(position.x+6, position.y+23);
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
		//collider->SetPos(position.x, position.y+2);
		//attack->SetPos(position.x + 25, position.y + 4);
	}
	else if (die) {
		currentAnim = &dieAnim;
		collider->SetPos(position.x , position.y);
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
