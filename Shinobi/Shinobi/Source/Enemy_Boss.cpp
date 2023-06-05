#include "Enemy_Boss.h"
#include "Enemy_green.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include "BossScene.h"

#include <iostream>
using namespace std;
#include "ModuleInput.h"

Enemy_Boss::Enemy_Boss(int x, int y) : Enemy(x, y)
{
	

	headAnim.PushBack({ 22,228,30,29 });
	headAnim.PushBack({ 51,228,30,29 });
	headAnim.PushBack({ 80,228,30,29 });
	headAnim.PushBack({ 109,228,30,29 });
	headAnim.loop = true;
	headAnim.speed = 0.06f;

	dieAnim.PushBack({ 22,8,109,92 });
	dieAnim.PushBack({ 130,8,109,92 });
	dieAnim.PushBack({ 238,8,109,92 });
	dieAnim.PushBack({ 346,8,109,92 });
	dieAnim.PushBack({ 22,109,109,92 });
	dieAnim.PushBack({ 130,109,109,92 });
	dieAnim.PushBack({ 238,109,109,92 });
	dieAnim.PushBack({ 346,109,109,92 });
	dieAnim.loop = false;
	dieAnim.speed = 0.06f;

	hitAnim.PushBack({ 22,8,109,92 });

	idleAnim.PushBack({93,410,70,60});
	idleAnim.loop = false;
	idleAnim.speed = 0.03f;

	dieHeadAnim.PushBack({ 0,0,0,0 });
	dieLegsAnim.PushBack({ 0,0,0,0 });

	attackAnim1.PushBack({ 93,473,70,60 });
	attackAnim1.PushBack({ 93,410,70,60 });
	attackAnim1.PushBack({ 24,282,70,60 });
	attackAnim1.PushBack({ 93,282,70,60 });
	attackAnim1.PushBack({ 93,282,70,60 });
	attackAnim1.PushBack({ 93,282,70,60 });
	attackAnim1.PushBack({ 93,282,70,60 });
	attackAnim1.PushBack({ 24,282,70,60 });
	attackAnim1.PushBack({ 93,410,70,60 });
	attackAnim1.loop = false;
	attackAnim1.speed = 0.04f;

	legsAnim.PushBack({79,617,55,60});
	legsAnim.loop = false;
	legsAnim.speed = 0.03f;

	//colliders
	collider = App->collisions->AddCollider({ position.x+30, position.y+103, 29, 2 }, Collider::Type::ENEMY, (Module*)App->enemies);
	head = App->collisions->AddCollider({ position.x + 28, position.y + 10, 20, 26 }, Collider::Type::ENEMY, (Module*)App->enemies);
	/*attack = App->collisions->AddCollider({ 0, 0, 0, 0 }, Collider::Type::ENEMY_SHOT, (Module*)App->enemies);*/
	/*feet = App->collisions->AddCollider({ position.x, position.y + 69, 83, 1 }, Collider::Type::FEET, (Module*)App->enemies);*/
	isBoss = true;
	currentAnim = &idleAnim;
}

void Enemy_Boss::Update()
{

	/*cout << (App->player->position.x - position.x) << endl;*/
	
	if (!die)
	{
		cout << position.y << endl;
		if (hit && hitCount <= 10)
		{
			currentAnim = &hitAnim;
			currentHeadAnim = &dieHeadAnim;
			currentLegsAnim = &dieLegsAnim;
			position.x = 326;
			position.y = 117;
			hitCount++;
			timer = 0;
		}
		if (hit && hitCount == 10)
		{
			position.x = 360;
			position.y = 104;
			hit = false;
		}
		if(!hit)
		{
			hitCount = 0;
			currentAnim = &idleAnim;
			currentHeadAnim = &headAnim;
			currentLegsAnim = &legsAnim;
			timer++;
		}
		if (timer >= 300 && !hit)
		{
			for (int i = 7; i >= 0; i--)
			{
				if ((App->player->position.x - position.x) > -200 && (App->player->position.x - position.x) < -120)
				{
					/*currentAnim = &attackAnim1;
					currentAnim->Reset();*/
					particle1[i].alive = true;
					particle1[i].centerY = 100;
					particle1[i].radius = 40.0f;
					particle1[i].angularVelocity = 0.16f;
					particle1[i].angularStep = 0.012f;
					particle1[i].time = 0.0f;
					particle1[i].left = true;
					App->particles->AddParticle(App->particles->fireBoss[i], position.x - 25 + (i * 2), static_cast<int>(particle1[i].centerY + particle1[i].radius * cos(particle1[i].angularStep * particle1[i].time)), Collider::Type::ENEMY_SHOT);
					particle1[i].particle = currentParticle;
					App->particles->particles[particle1[i].particle]->lifetime = 200;
				}
				if ((App->player->position.x - position.x) > -120)
				{
					particle2[i].alive = true;
					particle2[i].centerY = 140;
					particle2[i].radius = 40.0f;
					particle2[i].angularVelocity = 0.16f;
					particle2[i].angularStep = 0.012f;
					particle2[i].time = 0.0f;
					particle2[i].left = true;
					App->particles->AddParticle(App->particles->fireBoss[i], position.x - 25 + (i * 2), static_cast<int>(particle2[i].centerY + particle2[i].radius * sin(particle2[i].angularStep * particle2[i].time)), Collider::Type::ENEMY_SHOT);
					particle2[i].particle = currentParticle;
					App->particles->particles[particle2[i].particle]->lifetime = 120;
				}
				else if ((App->player->position.x - position.x) < -200)
				{
					App->particles->AddParticle(App->particles->fireBoss[i], position.x - 25 + (i * 2), position.y + 70, Collider::Type::ENEMY_SHOT);
					particle3[i].particle = currentParticle;
					particle3[i].alive = true;
					App->particles->particles[particle3[i].particle]->lifetime = 120;
				}
				if (i == 0) timer = 0;
			}
			isShooting = true;
			delay = 0;
		}


		if (isShooting) delay++;
		for (int i = 0; i <= 7; i++)
		{

			//particle1
			if (App->particles->particles[particle1[i].particle] != nullptr && particle1[i].alive && particle1[i].radius >= 0 && delay >= i * 2)
			{

				particle1[i].time += 3;
				App->particles->particles[particle1[i].particle]->position.y = static_cast<int>(particle1[i].centerY + particle1[i].radius * cos(particle1[i].angularStep * particle1[i].time));
				if (particle1[i].left)
				{
					App->particles->particles[particle1[i].particle]->position.x -= 2;
				}
				if (App->particles->particles[particle1[i].particle]->position.x <= 60 && particle1[i].left)
				{
					particle1[i].left = false;
					particle1[i].centerY = 106;
					App->particles->particles[particle1[i].particle]->fliph = true;
				}
				if (!particle1[i].left && App->particles->particles[particle1[i].particle]->position.x <= 70)
				{
					particle1[i].radius += particle1[i].angularVelocity * 8;
					App->particles->particles[particle1[i].particle]->position.x += 2;
				}
				if (!particle1[i].left && App->particles->particles[particle1[i].particle]->position.x >= 70)
				{
					particle1[i].radius += particle1[i].angularVelocity * 4;
					App->particles->particles[particle1[i].particle]->position.x += 2;
				}

			}
			else if (App->particles->particles[particle1[i].particle] == nullptr)
			{
				particle1[i].alive = false;
			}

			//particle2
			if (App->particles->particles[particle2[i].particle] != nullptr && particle2[i].alive && particle2[i].radius >= 0 && delay >= i * 2)
			{

				particle2[i].time += 3;

				App->particles->particles[particle2[i].particle]->position.y = static_cast<int>(particle2[i].centerY + particle2[i].radius * sin(particle2[i].angularStep * particle2[i].time));

				App->particles->particles[particle2[i].particle]->position.x -= 2;
				cout << "-2" << endl;

			}
			else if (App->particles->particles[particle2[i].particle] == nullptr)
			{
				particle2[i].alive = false;
			}

			//particle3
			if (App->particles->particles[particle3[i].particle] != nullptr && particle3[i].alive && delay >= i * 2)
			{

				if (particle3[i].left)
				{
					App->particles->particles[particle3[i].particle]->position.x -= 2;
				}
			}
			else if (App->particles->particles[particle3[i].particle] == nullptr)
			{
				particle3[i].alive = false;
			}

			if (App->particles->particles[particle1[i].particle] == nullptr
				&& App->particles->particles[particle2[i].particle] == nullptr
				&& App->particles->particles[particle3[i].particle] == nullptr && !hit)
			{
				currentAnim = &idleAnim;
			}
		}
	}
	collider->SetPos(position.x + 30, position.y+103);
	head->SetPos(position.x + 28, position.y + 10);
	if (die)
	{
		currentAnim = &dieAnim;
		currentHeadAnim = &dieHeadAnim;
		currentLegsAnim = &dieLegsAnim;
		position.y = 117;
		position.x = 330;
		if (count >= 80)
		{
			App->sceneboss->nextStage = true;
			count = 0;
		}
		else {
			count++;
		}
		
	}
	currentAnim->Update();
	currentHeadAnim->Update();
	currentLegsAnim->Update();
	

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}

