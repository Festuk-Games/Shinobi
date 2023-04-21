#include "ModuleHostage.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"

#include "ModuleAudio.h"
#include "ModuleScene.h"
#include "ModulePlayer.h"
#include "ModuleUI.h"
#include "ModuleCollisions.h"

#include "SDL/include/SDL_scancode.h"


ModuleHostage::ModuleHostage(bool startEnabled) : Module(startEnabled)
{
	for (int i = 0; i < 2; i++)
	{
		h[i].hostageposition.x = 200 + i * 100;
		h[i].hostageposition.y = 208;

		// idle animation

		h[i].idleAnim.PushBack({ 7, 12, 24, 29 });
		h[i].idleAnim.PushBack({ 36, 12, 24, 29 });
		h[i].idleAnim.loop = true;
		h[i].idleAnim.speed = 0.1f;

		h[i].exitAnim.PushBack({ 7, 64, 26, 48 });
		h[i].exitAnim.PushBack({ 36, 64, 26, 48 });
		h[i].exitAnim.PushBack({ 66, 64, 26, 48 });
		h[i].exitAnim.PushBack({ 96, 64, 26, 48 });
		h[i].exitAnim.loop = true;
		h[i].exitAnim.speed = 0.1f;

		h[i].exitAnim.PushBack({ 7, 12, 24, 29 });
		h[i].exitAnim.loop = false;
		h[i].exitAnim.speed = 0.2f;

	}

}

ModuleHostage::~ModuleHostage()
{

}

bool ModuleHostage::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Assets/hostage.png");


	h[0].collider = App->collisions->AddCollider({ 200, 180, 24, 28 }, Collider::Type::HOSTAGE);
	h[1].collider = App->collisions->AddCollider({ 300, 180, 24, 28 }, Collider::Type::HOSTAGE);

	return ret;
}

Update_Status ModuleHostage::Update()
{
	for (int i = 0; i < 2; i++)
	{
		if (!h[i].col)
		{
			h[i].currentAnimation = &h[i].idleAnim;
		}
		else h[i].currentAnimation = &h[i].exitAnim;
		h[i].currentAnimation->Update();
	}

	if (App->player->position.x == 180 && App->player->position.y == 208)
	{
		if (!h[0].col)
		{
			App->ui->hostages--;
			h[0].col = true;
			h[0].currentAnimation = &h[0].exitAnim;
			h[0].currentAnimation->Update();
		}
	}

	if (App->player->position.x == 300 && App->player->position.y == 208)
	{
		if (!h[1].col)
		{
			App->ui->hostages--;
			h[1].col = true;
			h[1].currentAnimation = &h[1].exitAnim;
			h[1].currentAnimation->Update();
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleHostage::PostUpdate()
{
	for (int i = 0; i < 2; i++)
	{
	
			if (!h[i].col)
			{
				SDL_Rect rect = h[i].currentAnimation->GetCurrentFrame();
				App->render->Blit(texture, h[i].hostageposition.x, h[i].hostageposition.y - rect.h, SDL_FLIP_NONE, &rect, 1.0f);
			}
			else
			{
				time++;
				if (time <= 18)
				{
					SDL_Rect rect = h[i].currentAnimation->GetCurrentFrame();
					h[i].hostageposition.y-=2;
					App->render->Blit(texture, h[i].hostageposition.x, h[i].hostageposition.y - rect.h, SDL_FLIP_NONE, &rect, 1.0f);
				}
			}
			

	}

	return Update_Status::UPDATE_CONTINUE;
}
