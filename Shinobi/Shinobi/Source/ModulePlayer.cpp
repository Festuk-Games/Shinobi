#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"

#include "SDL/include/SDL_scancode.h"


ModulePlayer::ModulePlayer()
{
	position.x = 30;
	position.y = 208;

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
	forwardAnim.speed = 0.05f;

	//walk backward animation
	backwardAnim.PushBack({ 5, 112, 40 - 5, 172 - 112 });
	backwardAnim.PushBack({ 41, 112, 72 - 41, 172 - 112 });
	backwardAnim.PushBack({ 73, 112, 108 - 73, 172 - 112 });
	backwardAnim.PushBack({ 109, 112, 144 - 109, 172 - 112 });
	backwardAnim.PushBack({ 145, 112, 177 - 145, 172 - 112 });
	backwardAnim.PushBack({ 178, 112, 213 - 178, 172 - 112 });
	backwardAnim.loop = true;
	backwardAnim.speed = 0.05f;

	//jump animation
	jumpAnim1.PushBack({ 11, 410, 46 - 11, 470 - 410 });
	jumpAnim2.PushBack({ 47, 384, 82 - 47, 470 - 410 });
	jumpAnim1.loop = false;
	jumpAnim1.speed = 0.05f;
	jumpAnim2.loop = false;
	jumpAnim2.speed = 0.05f;

	//crouch animation
	crouchAnim.PushBack({15,186,37,61});
	crouchAnim.loop = false;
	crouchAnim.speed = 0.05f;

	//crouch right animation
	crouchForwardAnim.PushBack({ 180,186,43,61 });
	crouchForwardAnim.PushBack({ 229,186,31,61 });
	crouchForwardAnim.PushBack({ 266,186,37,61 });
	crouchForwardAnim.loop = true;
	crouchForwardAnim.speed = 0.02f;

	//crouch left animation
	crouchBackwardAnim.PushBack({ 180,186,43,61 });
	crouchBackwardAnim.PushBack({ 229,186,31,61 });
	crouchBackwardAnim.PushBack({ 266,186,37,61 });
	crouchBackwardAnim.loop = true;
	crouchBackwardAnim.speed = 0.02f;

	//shoot animation
	shootAnim.PushBack({ 13,283,49,60 });
	shootAnim.loop = false;
	shootAnim.speed = 0.05f;

	//die animation
	dieAnim1.PushBack({ 99,650,42,44 });
	dieAnim2.PushBack({ 147,650,42,44 });
	dieAnim2.PushBack({ 194,650,62,44 });
	dieAnim2.PushBack({ 262,650,72,44 });
	dieAnim1.loop = false;
	dieAnim1.speed = 0.01f;
	dieAnim2.loop = false;
	dieAnim2.speed = 0.03f;

	//back animation
	backAnim.PushBack({ 127,735,46,52 });
	backAnim.loop = false;
	backAnim.speed = 0.05f;
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
	if (alive)
	{

		if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_DOWN && !isJumping)
		{
			isJumping = true;
		}

		if (isJumping)
		{
			if (!jumpState)
			{
				if (position.y >= 150)
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
				if (position.y == 150)
				{
					jumpState = true;
				}
			}
			else
			{
				if (position.y >= 150 && position.y <= 208)
				{
					currentAnimation = &jumpAnim2;
					currentAnimation->Reset();
					position.y += 1.2;
					if (App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT)
					{
						position.x += speed;
					}
					if (App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT)
					{
						position.x -= speed;
					}
				}
				if (position.y == 208)
				{
					isJumping = false;
					jumpState = false;
					currentAnimation = &idleAnim;
				}
			}
			currentAnimation->Update();
			return update_status::UPDATE_CONTINUE;
		}
		if (App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT && !isCrouching)
		{
			isWalking = true;
			if (currentAnimation != &forwardAnim)
			{
				currentAnimation = &forwardAnim;
				currentAnimation->Reset();
			}
			position.x += speed;
		}
		if (App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT && !isCrouching)
		{
			isWalking = true;
			if (currentAnimation != &backwardAnim)
			{
				currentAnimation = &backwardAnim;
				currentAnimation->Reset();
			}
			position.x -= speed;
		}

		// Spawn explosion particles when pressing LALT
		if (App->input->keys[SDL_SCANCODE_LALT] == KEY_DOWN && !isWalking && !isCrouching)
		{
			isShooting = true;
			if (currentAnimation != &shootAnim)
			{
				currentAnimation = &shootAnim;
				currentAnimation->Reset();
			}
			App->particles->AddParticle(App->particles->explosion, position.x + 20, position.y - 50);
		}

		if (App->input->keys[SDL_SCANCODE_W] == KEY_REPEAT && !isWalking && !isCrouching)
		{
			if (currentAnimation != &backAnim)
			{
				currentAnimation = &backAnim;
				currentAnimation->Reset();
			}
		}

		//crouch animation
		if (App->input->keys[SDL_SCANCODE_LCTRL] == KEY_REPEAT)
		{
			isCrouching = true;
			if (App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT)
			{
				if (currentAnimation != &crouchForwardAnim)
				{
					currentAnimation = &crouchForwardAnim;
					currentAnimation->Reset();
				}
				position.x += speed;
			}
			else if (App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT)
			{
				if (currentAnimation != &crouchBackwardAnim)
				{
					currentAnimation = &crouchBackwardAnim;
					currentAnimation->Reset();
				}
				position.x -= speed;
			}
			else
			{
				if (currentAnimation != &crouchAnim)
				{
					currentAnimation = &crouchAnim;
					currentAnimation->Reset();
				}
			}

		}
		if (isCrouching && App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT
			&& App->input->keys[SDL_SCANCODE_LCTRL] == KEY_IDLE
			|| isCrouching && App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT
			&& App->input->keys[SDL_SCANCODE_LCTRL] == KEY_IDLE)
		{
			isCrouching = false;
			currentAnimation = &idleAnim;
		}

		if (App->input->keys[SDL_SCANCODE_D] == KEY_IDLE
			&& App->input->keys[SDL_SCANCODE_A] == KEY_IDLE
			&& App->input->keys[SDL_SCANCODE_LALT] == KEY_IDLE
			&& App->input->keys[SDL_SCANCODE_W] == KEY_IDLE
			&& App->input->keys[SDL_SCANCODE_LCTRL] == KEY_IDLE)
		{
			isWalking = false;
			isShooting = false;
			isCrouching = false;
			currentAnimation = &idleAnim;
		}
	}
	else
	{
		if (!diePos)
		{
			diePosition = position;
			diePos = true;
		}
		if (position.x >= diePosition.x - 20 )
		{
			if (currentAnimation != &dieAnim1)
			{
				currentAnimation = &dieAnim1;
				currentAnimation->Reset();
			}
			position.x -= speed;
			App->render->camera.x -= speed;
		}
		else if (position.x <= diePosition.x - 20)
		{
			if (currentAnimation != &dieAnim2)
			{
				currentAnimation = &dieAnim2;
				currentAnimation->Reset();
			}
		}
	}

	currentAnimation->Update();

	return update_status::UPDATE_CONTINUE;
}

update_status ModulePlayer::PostUpdate()
{
	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	App->render->Blit(texture, position.x, position.y - rect.h, &rect);

	return update_status::UPDATE_CONTINUE;
}