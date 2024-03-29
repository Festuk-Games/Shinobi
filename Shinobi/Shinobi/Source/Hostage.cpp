#include "Hostage.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleUI.h"
#include "Hostage_Hostage.h"
#include "ModuleHostage.h"

Hostage::Hostage(int x, int y) : position(x, y)
{
	currentAnimation = &idleAnim;
}

Hostage::~Hostage()
{
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

const Collider* Hostage::GetCollider() const
{
	return collider;
}

void Hostage::Update()
{
	if (currentAnimation != nullptr)
		currentAnimation->Update();

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
	
}

void Hostage::Draw()
{
	if (!col)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, SDL_FLIP_NONE, &rect, 1.0f);
	}
	else
	{
		if (time <= 18)
		{
			SDL_Rect rect = currentAnimation->GetCurrentFrame();
			App->render->Blit(texture, position.x, position.y, SDL_FLIP_NONE, &rect, 1.0f);
			time++;
		}
		if (time == 18 && App->hostage->powerup != 1)
		{
			App->particles->AddParticle(App->particles->bonus500, position.x - 20, position.y - 10, Collider::Type::NONE);
			time++;
			App->hostage->powerup++;
		}
		if (time == 18 && App->hostage->powerup == 1)
		{
			App->particles->AddParticle(App->particles->pow, position.x - 20, position.y - 10, Collider::Type::NONE);
			time++;
			App->hostage->powerup++;
			App->player->isPowerUp = true;
		}

	}

}

void Hostage::OnCollision(Collider* collider)
{
	App->ui->scoreCounter += 500;
	App->ui->hostages--;
	col = true;
	App->audio->PlayFx(App->audio->hostage);
}

