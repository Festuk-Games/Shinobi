#include "Hostage_Hostage.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"

Hostage_Hostage::Hostage_Hostage(int x, int y) : Hostage(x, y)
{
	// idle animation
	idleAnim.PushBack({ 7, 12, 24, 29 });
	idleAnim.PushBack({ 36, 12, 24, 29 });
	idleAnim.PushBack({ 7, 12, 24, 29 });
	idleAnim.PushBack({ 36, 12, 24, 29 });
	idleAnim.PushBack({ 65, 12, 24, 29 });
	idleAnim.PushBack({ 94, 12, 24, 29 });
	idleAnim.PushBack({ 65, 12, 24, 29 });
	idleAnim.PushBack({ 94, 12, 24, 29 });
	idleAnim.PushBack({ 36, 12, 24, 29 });
	idleAnim.loop = true;
	idleAnim.speed = 0.08f;

	// exit animation
	exitAnim.PushBack({ 7, 64, 24, 48 });
	exitAnim.PushBack({ 36, 64, 24, 48 });
	exitAnim.PushBack({ 66, 64, 24, 48 });
	exitAnim.PushBack({ 96, 64, 24, 48 });
	exitAnim.loop = false;
	exitAnim.speed = 0.1f;

	currentAnimation = &idleAnim;

	collider = App->collisions->AddCollider({ 0, 0, 24, 28 }, Collider::Type::HOSTAGE, (Module*)App->hostage);

}

void Hostage_Hostage::Update()
{


	if (!col)
	{
		currentAnimation = &idleAnim;
	}
	else if (col && time < 1) position.y -= 20;
	else if (col && time <= 18)
	{
		position.y -= 2;
		currentAnimation = &exitAnim;
	}
	currentAnimation->Update();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Hostage::Update();
}
