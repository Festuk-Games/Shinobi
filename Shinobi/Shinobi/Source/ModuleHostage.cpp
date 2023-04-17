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


ModuleHostage::ModuleHostage()
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

		h[i].exitAnim.PushBack({ 7, 12, 24, 29 });
		h[i].exitAnim.loop = true;
		h[i].exitAnim.speed = 0.1f;

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

update_status ModuleHostage::Update()
{
	for (int i = 0; i < 2; i++)
	{
		currentAnimation = &h[i].idleAnim;
		currentAnimation->Update();
	}

	if (App->player->position.x == 198 && App->player->position.y == 208)
	{
		if (!h[0].col)
		{
			App->ui->hostages--;
			h[0].col = true;
		}
	}

	if (App->player->position.x == 300 && App->player->position.y == 208)
	{
		if (!h[1].col)
		{
			App->ui->hostages--;
			h[1].col = true;
		}
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleHostage::PostUpdate()
{
	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	for (int i = 0; i < 2; i++)
	{
		if (!h[i].col)
		{
			App->render->Blit(texture, h[i].hostageposition.x, h[i].hostageposition.y - rect.h, &rect, 1.0f);
		}
	}

	return update_status::UPDATE_CONTINUE;
}
