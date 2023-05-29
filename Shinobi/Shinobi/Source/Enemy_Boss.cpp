#include "Enemy_Boss.h"
#include "Enemy_green.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include <iostream>

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
	collider = App->collisions->AddCollider({ position.x+70, position.y, 29, 200 }, Collider::Type::ENEMY, (Module*)App->enemies);
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
	if (count < 1)
	{
		App->particles->AddParticle(App->particles->enemyshot, position.x, position.y, Collider::Type::ENEMY_SHOT);
		particle1 = currentParticle;
		count++;
	}
	if (count == 1)
	{
		App->particles->AddParticle(App->particles->enemyshot, position.x-20, position.y, Collider::Type::ENEMY_SHOT);
		particle2 = currentParticle;
		count++;
	}
	App->particles->particles[particle1]->position.x--;
	App->particles->particles[particle2]->position.y--;
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}

