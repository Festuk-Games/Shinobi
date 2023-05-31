#include "Enemy_Boss.h"
#include "Enemy_green.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include <iostream>
using namespace std;
#include "ModuleInput.h"

Enemy_Boss::Enemy_Boss(int x, int y) : Enemy(x, y)
{
	

	headAnim.PushBack({ 23,194,29,27 });
	headAnim.PushBack({ 80,194,29,27 });
	headAnim.PushBack({ 51,194,29,27 });
	headAnim.PushBack({ 135,194,29,27 });
	headAnim.loop = true;
	headAnim.speed = 0.06f;

	dieAnim.PushBack({ 10,3,107,93 });
	dieAnim.PushBack({ 116,3,107,93 });
	dieAnim.PushBack({ 222,3,107,93 });
	dieAnim.PushBack({ 328,3,107,93 });
	dieAnim.PushBack({ 10,95,107,93 });
	dieAnim.PushBack({ 116,95,107,93 });
	dieAnim.PushBack({ 222,95,107,93 });
	dieAnim.PushBack({ 328,95,107,93 });
	dieAnim.loop = false;
	dieAnim.speed = 0.08f;

	idleAnim.PushBack({76,225,66,47});
	idleAnim.loop = false;
	idleAnim.speed = 0.03f;

	legsAnim.PushBack({273,224,53,61});
	legsAnim.loop = false;
	legsAnim.speed = 0.03f;

	//colliders
	collider = App->collisions->AddCollider({ position.x+30, position.y+79, 29, 20 }, Collider::Type::ENEMY, (Module*)App->enemies);
	/*attack = App->collisions->AddCollider({ 0, 0, 0, 0 }, Collider::Type::ENEMY_SHOT, (Module*)App->enemies);*/
	/*feet = App->collisions->AddCollider({ position.x, position.y + 69, 83, 1 }, Collider::Type::FEET, (Module*)App->enemies);*/
	isBoss = true;
}

void Enemy_Boss::Update()
{
	currentAnim = &idleAnim;
	currentHeadAnim = &headAnim;
	currentLegsAnim = &legsAnim;
	currentAnim->Update();
	currentHeadAnim->Update();
	currentLegsAnim->Update();

	

	if (App->input->keys[SDL_SCANCODE_H] == KEY_DOWN)
	{
		count = 0;
		for (int i = 7; i >= 0; i--)
		{
			if (count < 1)
			{
				App->particles->AddParticle(App->particles->fireBoss[i], position.x-50+(i*2), position.y, Collider::Type::ENEMY_SHOT);
				particle1[i].particle = currentParticle;
				particle1[i].alive = true;
				particle1[i].centerY = 100;
				particle1[i].radius = 40.0f;
				particle1[i].angularVelocity = 0.16f;
				particle1[i].angularStep = 0.012f;
				particle1[i].time = 0.0f;
				particle1[i].left = true;
			 	App->particles->particles[particle1[i].particle]->lifetime = 200;
			}
			if (count < 1)
			{
				App->particles->AddParticle(App->particles->fireBoss[i], position.x - 50 + (i * 2), position.y, Collider::Type::ENEMY_SHOT);
				particle2[i].particle = currentParticle;
				particle2[i].alive = true;
				particle2[i].centerY = 140;
				particle2[i].radius = 40.0f;
				particle2[i].angularVelocity = 0.16f;
				particle2[i].angularStep = 0.012f;
				particle2[i].time = 0.0f;
				particle2[i].left = true;
				App->particles->particles[particle2[i].particle]->lifetime = 120;
			}
			if (count < 1)
			{
				App->particles->AddParticle(App->particles->fireBoss[i], position.x - 50 + (i * 2), position.y+70, Collider::Type::ENEMY_SHOT);
				particle3[i].particle = currentParticle;
				particle3[i].alive = true;
				App->particles->particles[particle3[i].particle]->lifetime = 120;
			}
			if (i == 0) count++;
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
			if (particle2[i].left)
			{
				App->particles->particles[particle2[i].particle]->position.x -= 2;
			}
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
	}
	collider->SetPos(position.x + 30, position.y+79);

	

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}

