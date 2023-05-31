#include "Enemy.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "Enemy_Gunner.h"
#include "ModuleUI.h"
#include "ModuleEnemies.h"
#include "Enemy_Purple.h"
#include "Enemy_Spiderman.h"

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

const Collider* Enemy::GetAttackCollider() const
{
	return attack;
}

void Enemy::Update()
{
	if (currentAnim != nullptr)
		currentAnim->Update();

	//if (collider != nullptr)
	//	collider->SetPos(position.x, position.y);

	if (!ground && !isSpiderman)
	{
		position.y++;
	}
	
	if (!die) ground = false;
	else ground = true;
	
}

void Enemy::Draw()
{
	if (currentAnim != nullptr)
	{
		if (isBoss)
		{
			if (flip)
			{
				App->render->Blit(texture, position.x + 19, position.y+11, SDL_FLIP_NONE, &(currentHeadAnim->GetCurrentFrame()));
				App->render->Blit(texture, position.x + 20, position.y + 44, SDL_FLIP_NONE, &(currentLegsAnim->GetCurrentFrame()));
			}
			else
			{
				App->render->Blit(texture, flipPos.x + 19, position.y+11, SDL_FLIP_HORIZONTAL, &(currentHeadAnim->GetCurrentFrame()));
				App->render->Blit(texture, flipPos.x + 20, position.y + 44, SDL_FLIP_HORIZONTAL, &(currentLegsAnim->GetCurrentFrame()));
			}
		}
		if (flip)
		{
			App->render->Blit(texture, position.x, position.y, SDL_FLIP_NONE, &(currentAnim->GetCurrentFrame()));
		}
		else
		{
			App->render->Blit(texture, flipPos.x, position.y, SDL_FLIP_HORIZONTAL, &(currentAnim->GetCurrentFrame()));
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
	if (collider->type==Collider::Type::WALL)
	{
		collision = true;
	}
}
