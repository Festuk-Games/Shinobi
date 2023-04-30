#include "Enemy.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "Enemy_Gunner.h"
#include "ModuleUI.h"

Enemy::Enemy(int x, int y) : position(x, y)
{
	spawnPos.x = position.x;
}

Enemy::~Enemy()
{
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

const Collider* Enemy::GetCollider() const
{
	return collider;
}

void Enemy::Update()
{
	if (currentAnim != nullptr)
		currentAnim->Update();

	//if (collider != nullptr)
	//	collider->SetPos(position.x, position.y);

	if (!ground)
	{
		position.y++;
	}

	ground = false;
}

void Enemy::Draw()
{
	if (currentAnim != nullptr)
	{
		if (flip)
		{
			App->render->Blit(texture, position.x, position.y, SDL_FLIP_NONE, &(currentAnim->GetCurrentFrame()));
		}
		else
		{
			App->render->Blit(texture, position.x, position.y, SDL_FLIP_HORIZONTAL, &(currentAnim->GetCurrentFrame()));
		}
	}

}

void Enemy::OnCollision(Collider* collider)
{
	if (collider->type == Collider::Type::PLAYER_SHOT)
	{
		die = true;
		App->ui->scoreCounter+= 200;
	}
}