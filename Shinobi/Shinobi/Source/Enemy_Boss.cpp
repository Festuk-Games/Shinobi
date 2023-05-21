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
	headAnim.PushBack({ 79,194,29,27 });
	headAnim.PushBack({ 51,194,29,27 });
	headAnim.PushBack({ 135,194,29,27 });
	headAnim.loop = true;
	headAnim.speed = 0.1;

	dieAnim.PushBack({ 10,3,107,93 });
	dieAnim.PushBack({ 116,3,107,93 });
	dieAnim.PushBack({ 222,3,107,93 });
	dieAnim.PushBack({ 328,3,107,93 });
	dieAnim.PushBack({ 10,95,107,93 });
	dieAnim.PushBack({ 116,95,107,93 });
	dieAnim.PushBack({ 222,95,107,93 });
	dieAnim.PushBack({ 328,95,107,93 });
	dieAnim.loop = false;
	dieAnim.speed = 0.03;


	//colliders
	collider = App->collisions->AddCollider({ position.x+70, position.y, 29, 200 }, Collider::Type::ENEMY, (Module*)App->enemies);
	/*attack = App->collisions->AddCollider({ 0, 0, 0, 0 }, Collider::Type::ENEMY_SHOT, (Module*)App->enemies);*/
	/*feet = App->collisions->AddCollider({ position.x, position.y + 69, 83, 1 }, Collider::Type::FEET, (Module*)App->enemies);*/

}

void Enemy_Boss::Update()
{
	currentAnim = &dieAnim;
	currentHeadAnim = &dieAnim;
	currentLegsAnim = &dieAnim;
	currentAnim->Update();
	currentHeadAnim->Update();
	currentLegsAnim->Update();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}

