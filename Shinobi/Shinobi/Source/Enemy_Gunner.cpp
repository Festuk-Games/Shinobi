#include "Enemy_Gunner.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_Gunner::Enemy_Gunner(int x, int y) : Enemy(x, y)
{
	idleAnim.PushBack({11,165,36,59});
	idleAnim.PushBack({ 68,165,36,59 });
	idleAnim.PushBack({ 143,165,36,59 });
	idleAnim.PushBack({ 68,165,36,59 });
	idleAnim.speed = 0.05f;

	currentAnim = &idleAnim;

	collider = App->collisions->AddCollider({0, 0, 36, 59}, Collider::Type::NONE, (Module*)App->enemies);

	spawnPos.x = 200;
	position.y = 148;
}

void Enemy_Gunner::Update()
{
	waveRatio += waveRatioSpeed;
	position.x = spawnPos.x + (waveHeight * sinf(waveRatio));

	/*if (position.x == 650) changedirection = true;
	else if (position.x == 500) changedirection = false;

	if (changedirection) position.x--;
	else position.x++;*/


	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
