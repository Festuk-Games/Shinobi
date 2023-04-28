#include "Enemy_Fighter.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"

Enemy_Fighter::Enemy_Fighter(int x, int y) : Enemy(x, y)
{
	//idle animation
	idleAnim.PushBack({ 0,6,54,59 });

	//walk animation
	walkAnim.PushBack({ 11,165,36,59 });
	walkAnim.PushBack({ 68,165,36,59 });
	walkAnim.PushBack({ 143,165,36,59 });
	walkAnim.PushBack({ 68,165,36,59 });
	walkAnim.speed = 0.05f;

	currentAnim = &walkAnim;

	//shoot animation
	shootAnim.PushBack({ 0,6,54,59 });
	shootAnim.PushBack({ 64,6,54,59 });
	shootAnim.PushBack({ 0,6,54,59 });
	shootAnim.speed = 0.1f;
	shootAnim.loop = false;

	//reload animation
	reloadAnim.PushBack({ 143,6,54,59 });
	reloadAnim.PushBack({ 206,6,54,59 });
	reloadAnim.speed = 0.05f;

	//colliders
	collider = App->collisions->AddCollider({ 0, 0, 36, 59 }, Collider::Type::ENEMY, (Module*)App->enemies);
	feet = App->collisions->AddCollider({ position.x, position.y, 35, 1 }, Collider::Type::FEET, (Module*)App->enemies);

	//initial position
	position.x = 550;
	position.y = 148;
}

void Enemy_Fighter::Update()
{

	//waveRatio += waveRatioSpeed;
	//position.x = spawnPos.x + (waveHeight * sinf(waveRatio));

	//walk right
	if (position.x - App->player->position.x <= pdistance && position.x - App->player->position.x >= 0)
	{
		shot++;
		if (shot >= 100 && !reloading && bullets >= 1)
		{
			currentAnim = &shootAnim;
			currentAnim->Reset();
			App->audio->PlayFx(App->audio->shuriken);
			App->particles->enemyshot.speed = iPoint(-5, 0);
			App->particles->AddParticle(App->particles->enemyshot, position.x, position.y + 10, Collider::Type::ENEMY_SHOT);
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
	else if (position.x - App->player->position.x >= -pdistance && position.x - App->player->position.x <= 0)
	{
		shot++;
		if (shot >= 100 && !reloading && bullets >= 1)
		{
			currentAnim = &shootAnim;
			currentAnim->Reset();
			App->audio->PlayFx(App->audio->shuriken);
			App->particles->enemyshot.speed = iPoint(5, 0);
			App->particles->AddParticle(App->particles->enemyshot, position.x, position.y + 10, Collider::Type::ENEMY_SHOT);
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
		if (position.x >= pos2)
		{
			changedirection = true;
			flip = true;
		}
		else if (position.x <= pos1)
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

	//if (!shooting && !reloading && !walking)
	//{
	//	currentAnim = &idleAnim;
	//}


	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
