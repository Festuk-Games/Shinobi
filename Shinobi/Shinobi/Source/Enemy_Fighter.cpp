#include "Enemy_Fighter.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include "ModuleScene.h"
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

	jumpAnim.PushBack({ 326,29,68,66 });
	jumpAnim.PushBack({ 259,29,68,66 });
	jumpAnim.speed = 0.1f;
	jumpAnim.loop = false;

	dieAnim.PushBack({ 29,217,68,66 });
	dieAnim.PushBack({ 96,217,68,66 });
	dieAnim.PushBack({ 164,217,68,66 });
	dieAnim.PushBack({ 164,217,68,66 });
	dieAnim.PushBack({ 0,0,0,0 });

	dieAnim.speed = 0.1f;
	dieAnim.loop = false;


	//colliders
	collider = App->collisions->AddCollider({ position.x + 25, position.y+3, 35, 64}, Collider::Type::ENEMY, (Module*)App->enemies);
	attack = App->collisions->AddCollider({ 0, 0, 0, 0 }, Collider::Type::ENEMY_SHOT, (Module*)App->enemies);

	/*feet = App->collisions->AddCollider({ position.x, position.y + 69, 83, 1 }, Collider::Type::FEET, (Module*)App->enemies);*/
}
void Enemy_Fighter::Update()
{
	flipPos.x = position.x + 20;
	//std::cout << position.y << std::endl;
	if (!die)
	{
		//walk right
		if (position.x - App->player->position.x <= pdistance && position.x - App->player->position.x >= 0 && App->player->alive && !isCollidingRight
			&& ((position.y <= 100 && App->player->L2 || position.y >= 100 && !App->player->L2) || !App->scene->IsEnabled()) && App->player->alive
			&& (App->player->currentAnimation != &App->player->jumpDownFloorAnim || App->player->currentAnimation != &App->player->jumpUpFloorAnim))
		{
			spawnPos.x = position.x - 100;
			isCollidingLeft = false;
			if (position.x != App->player->position.x && !shooting && !reloading)
			{
				flip = true;
				shot++;
				if (position.x - App->player->position.x >= pdistance - 175)
				{
					if (jump && currentAnim != &jumpAnim)
					{
						currentAnim = &jumpAnim;
						currentAnim->Reset();
					}
					else if (jump || (!jump && !ground)) currentAnim = &jumpAnim;
					else currentAnim = &walkAnim;
					if(ground) position.x--;
				}
				else if (shot >= 100)
				{
					currentAnim = &hitAnim;
					currentAnim->Reset();
					//App->particles->AddParticle(App->particles->patada, position.x, position.y + 30, Collider::Type::ENEMY_SHOT);
					attack = App->collisions->AddCollider({ position.x, position.y+30, 10, 10 }, Collider::Type::ENEMY_SHOT, (Module*)App->enemies);
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

		////walk left
		else if (position.x - App->player->position.x >= -pdistance && position.x - App->player->position.x <= 0 && App->player->alive && !isCollidingLeft
			&& ((position.y <= 100 && App->player->L2 || position.y >= 100 && !App->player->L2) || !App->scene->IsEnabled()) && App->player->alive
			&& (App->player->currentAnimation != &App->player->jumpDownFloorAnim || App->player->currentAnimation != &App->player->jumpUpFloorAnim))
		{
			spawnPos.x = position.x + 50;
			isCollidingRight = false;
			if (position.x != App->player->position.x && !shooting && !reloading)
			{

				shot++;
				flip = false;

				if (position.x - App->player->position.x <= -(pdistance - 140))
				{
					if (jump && currentAnim != &jumpAnim)
					{
						currentAnim = &jumpAnim;
						currentAnim->Reset();
					}
					else if (jump || (!jump && !ground)) currentAnim = &jumpAnim;
					else currentAnim = &walkAnim;
					if(ground) position.x++;
				}
				else if (shot >= 100)
				{
					currentAnim = &hitAnim;
					currentAnim->Reset();
					//App->particles->AddParticle(App->particles->patada, position.x+80, position.y + 30, Collider::Type::ENEMY_SHOT);
					attack = App->collisions->AddCollider({ position.x+80, position.y+30, 10, 10 }, Collider::Type::ENEMY_SHOT, (Module*)App->enemies);
					//attack->SetPos(position.x+80, position.y+30);
					App->audio->PlayFx(App->audio->shuriken);
					shot = 0;
					shooting = true;
				}
				else {
					attack->rect.w = 0;
					attack->rect.h = 0;
					attack->pendingToDelete=true;
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
		else if (!pl && !reloading && !shooting )
		{
			if ((jump || !jump && !ground) && currentAnim != &jumpAnim)
			{
				currentAnim = &jumpAnim;
				currentAnim->Reset();
			}
			else if (jump || (!jump && !ground)) currentAnim = &jumpAnim;
			else currentAnim = &walkAnim;
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
				if(ground) position.x--;
			}
			else
			{
				flip = false;
				if(ground) position.x++;
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
		collider->SetPos(position.x + 25, position.y+3);
		
		//attack->SetPos(position.x + 25, position.y + 4);
	}
	else if (die) {
		currentAnim = &dieAnim;
		collider->SetPos(position.x-10, position.y + 30);
		collider->rect.w = 37;
		collider->rect.h = 20;
		attack->rect.w = 0;
		attack->rect.h = 0;
		attack->SetPos(0, 0);
	}
	jump = false;

	if (isCollidingLeft) std::cout << "colision izquierda" << std::endl;
	if (isCollidingRight) std::cout << "colision derecha" << std::endl;
	//feet->SetPos(position.x, position.y + 69);

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
