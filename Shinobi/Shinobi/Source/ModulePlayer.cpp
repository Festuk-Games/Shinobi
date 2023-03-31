#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"

#include "SDL/include/SDL_scancode.h"


ModulePlayer::ModulePlayer()
{
	position.x = 100;
	position.y = 220;

	// idle animation
	idleAnim.PushBack({13, 39, 48 - 13, 99 - 39 });

	// walk forward animation
	forwardAnim.PushBack({5, 112, 40 - 5, 172 - 112});
	forwardAnim.PushBack({ 41, 112, 72 - 41, 172 - 112 });
	forwardAnim.PushBack({ 73, 112, 108 - 73, 172 - 112 });
	forwardAnim.PushBack({ 109, 112, 144 - 109, 172 - 112 });
	forwardAnim.PushBack({ 145, 112, 177 - 145, 172 - 112 });
	forwardAnim.PushBack({ 178, 112, 213 - 178, 172 - 112 });
	forwardAnim.loop = true;
	forwardAnim.speed = 0.1f;

	//walk backward animation
	backwardAnim.PushBack({ 5, 112, 40 - 5, 172 - 112 });
	backwardAnim.PushBack({ 41, 112, 72 - 41, 172 - 112 });
	backwardAnim.PushBack({ 73, 112, 108 - 73, 172 - 112 });
	backwardAnim.PushBack({ 109, 112, 144 - 109, 172 - 112 });
	backwardAnim.PushBack({ 145, 112, 177 - 145, 172 - 112 });
	backwardAnim.PushBack({ 178, 112, 213 - 178, 172 - 112 });
	backwardAnim.loop = true;
	backwardAnim.speed = 0.1f;

	//jump animation
	jumpAnim1.PushBack({ 11, 410, 46 - 11, 470 - 410 });
	jumpAnim2.PushBack({ 47, 384, 82 - 47, 470 - 410 });
	jumpAnim1.loop = false;
	jumpAnim1.speed = 0.1f;
	jumpAnim2.loop = false;
	jumpAnim2.speed = 0.1f;
}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Assets/main.png"); // arcade version

	return ret;
} 

update_status ModulePlayer::Update()
{

	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN && !isJumping)
	{
		isJumping = true;
	}

	if (isJumping)
	{
		if (!jumpState)
		{
			if (position.y >= 180)
			{
				currentAnimation = &jumpAnim1;
				currentAnimation->Reset();
				position.y -= speed;
				if (App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT)
				{
					position.x += speed;
				}
				if (App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT)
				{
					position.x -= speed;
				}
			}
			if (position.y == 180)
			{
				jumpState = true;
			}
		}
		else
		{
			if (position.y >= 180 && position.y <= 220)
			{
				currentAnimation = &jumpAnim2;
				currentAnimation->Reset();
				position.y += speed;
				if (App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT)
				{
					position.x += speed;
				}
				if (App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT)
				{
					position.x -= speed;
				}
			}
			if (position.y == 220)
			{
				isJumping = false;
				jumpState = false;
				currentAnimation = &idleAnim;
			}
		}
		currentAnimation->Update();
		return update_status::UPDATE_CONTINUE;
	}
	if (App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT)
	{
		if (currentAnimation != &forwardAnim)
		{
			currentAnimation = &forwardAnim;
			currentAnimation->Reset();
		}
		position.x += speed;
	}
	if (App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT)
	{
		if (currentAnimation != &backwardAnim)
		{
			currentAnimation = &backwardAnim; 
			currentAnimation->Reset();
		}
		position.x -= speed;
	}

	// Spawn explosion particles when pressing LALT
	if (App->input->keys[SDL_SCANCODE_LALT] == KEY_DOWN)
	{
		App->particles->AddParticle(App->particles->explosion, position.x, position.y);
	}

	if (App->input->keys[SDL_SCANCODE_LCTRL] == KEY_REPEAT)
	{
		//if (currentAnimation != &Anim)
		//{
		//	currentAnimation = &Anim;
		//	currentAnimation->Reset();
		//}
	}

	if (App->input->keys[SDL_SCANCODE_D] == KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_A] == KEY_IDLE)
		currentAnimation = &idleAnim;

	currentAnimation->Update();

	return update_status::UPDATE_CONTINUE;
}

update_status ModulePlayer::PostUpdate()
{
	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	App->render->Blit(texture, position.x, position.y - rect.h, &rect);

	return update_status::UPDATE_CONTINUE;
}