#include "ModulePlayer.h"
#include <iostream>
using namespace std;

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"

#include "ModuleAudio.h"
#include "ModuleScene.h"

#include "ModuleCollisions.h"

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
	forwardAnim.speed = 0.2f;

	//walk backward animation
	backwardAnim.PushBack({ 5, 112, 40 - 5, 172 - 112 });
	backwardAnim.PushBack({ 41, 112, 72 - 41, 172 - 112 });
	backwardAnim.PushBack({ 73, 112, 108 - 73, 172 - 112 });
	backwardAnim.PushBack({ 109, 112, 144 - 109, 172 - 112 });
	backwardAnim.PushBack({ 145, 112, 177 - 145, 172 - 112 });
	backwardAnim.PushBack({ 178, 112, 213 - 178, 172 - 112 });
	backwardAnim.loop = true;
	backwardAnim.speed = 0.2f;

	//jump animation
	jumpAnim1.PushBack({ 11, 410, 46 - 11, 470 - 410 });
	jumpAnim2.PushBack({ 47, 384, 82 - 47, 470 - 410 });
	jumpAnim1.loop = false;
	jumpAnim1.speed = 0.1f;
	jumpAnim2.loop = false;
	jumpAnim2.speed = 0.1f;

	//jump up animation
	jumpUpAnim.PushBack({ 172, 745, 45, 42});
	jumpUpAnim.PushBack({ 216, 745, 46, 42});
	jumpUpAnim.loop = false;
	jumpUpAnim.speed = 0.03f;

	//crouch animation
	crouchAnim.PushBack({15,186,37,61});
	crouchAnim.loop = false;
	crouchAnim.speed = 0.1f;

	//crouch right animation
	crouchForwardAnim.PushBack({ 180,186,43,61 });
	crouchForwardAnim.PushBack({ 229,186,31,61 });
	crouchForwardAnim.PushBack({ 266,186,37,61 });
	crouchForwardAnim.loop = true;
	crouchForwardAnim.speed = 0.1f;

	//crouch left animation
	crouchBackwardAnim.PushBack({ 180,186,43,61 });
	crouchBackwardAnim.PushBack({ 229,186,31,61 });
	crouchBackwardAnim.PushBack({ 266,186,37,61 });
	crouchBackwardAnim.loop = true;
	crouchBackwardAnim.speed = 0.1f;

	//crouch attack animation
	crouchAttackAnim.PushBack({ 760,186,53,61 });
	crouchAttackAnim.loop = false;
	crouchAttackAnim.speed = 0.1f;

	//crouch kick animation
	crouchKickAnim.PushBack({ 380,654,45,40 });
	crouchKickAnim.PushBack({ 431,654,67,40 });
	crouchKickAnim.PushBack({ 504,654,45,40 });
	crouchKickAnim.loop = false;
	crouchKickAnim.speed = 0.1f;

	//crouch katana animation
	crouchKatanaAnim.PushBack({ 15,825,50,52 });
	crouchKatanaAnim.PushBack({ 64,825,55,52 });
	crouchKatanaAnim.PushBack({ 118,825,66,52 });
	crouchKatanaAnim.PushBack({ 183,825,77,52 });
	crouchKatanaAnim.PushBack({ 259,825,48,52 });
	crouchKatanaAnim.PushBack({ 306,825,50,52 });
	crouchKatanaAnim.PushBack({ 355,825,38,52 });
	crouchKatanaAnim.loop = false;
	crouchKatanaAnim.speed = 0.2f;

	//shoot animation
	shootAnim.PushBack({ 13,283,49,60 });
	shootAnim.loop = false;
	shootAnim.speed = 0.1f;

	//die animation
	dieAnim1.PushBack({ 99,650,42,44 });
	dieAnim2.PushBack({ 147,650,42,44 });
	dieAnim2.PushBack({ 194,650,62,44 });
	dieAnim2.PushBack({ 262,650,72,44 });
	dieAnim1.loop = false;
	dieAnim1.speed = 0.1f;
	dieAnim2.loop = false;
	dieAnim2.speed = 0.1f;

	//back animation
	backAnim.PushBack({ 127,735,46,52 });
	backAnim.loop = false;
	backAnim.speed = 0.1f;
}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Assets/main.png"); 
	collider = App->collisions->AddCollider({ position.x, position.y-58, 35, 58 }, Collider::Type::PLAYER, this);
	feet = App->collisions->AddCollider({ position.x, position.y, 35, 1 }, Collider::Type::FEET, this);

	return ret;
} 

update_status ModulePlayer::Update()
{
	if (alive)
	{

		if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_DOWN && !isJumping && !isJumpingUp1 && !isJumpingDown1)
		{
			isJumping = true;
			jumpPosition.y = position.y;
		}

		if (isJumping)
		{
			if (!jumpState)
			{
				if (position.y >= jumpPosition.y-72)
				{
					currentAnimation = &jumpAnim1;
					currentAnimation->Reset();
					position.y -= 4;
					collider->SetPos(position.x, position.y - 58);
					feet->SetPos(position.x, position.y-1);
					if (App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT)
					{
						position.x += speed;
					}
					if (App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT)
					{
						position.x -= speed;
					}
					if (position.y <= 90)
					{
						App->render->camera.y+=speed;
					}
				}
				if (position.y == jumpPosition.y - 72)
				{
					jumpState = true;
				}
			}
			else
			{
				if (position.y >= jumpPosition.y - 72 && position.y <= 208)
				{
					currentAnimation = &jumpAnim2;
					currentAnimation->Reset();
					position.y += 4.2;
					collider->SetPos(position.x, position.y - 58);
					feet->SetPos(position.x, position.y-1);
					if (App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT)
					{
						position.x += speed;
					}
					if (App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT)
					{
						position.x -= speed;
					}
					if (position.y <= 90)
					{
						App->render->camera.y-=speed;
					}
				}
				//if (position.y == 208)
				//{
				//	isJumping = false;
				//	jumpState = false;
				//	currentAnimation = &idleAnim;
				//}
			}
			currentAnimation->Update();
			return update_status::UPDATE_CONTINUE;
		}
		if (App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT && !isCrouching && !isColliding && position.x < 2010)
		{
			isWalking = true;
			if (currentAnimation != &forwardAnim)
			{
				currentAnimation = &forwardAnim;
				currentAnimation->Reset();
			}
			position.x += speed;
		}
		if (App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT && !isCrouching && !isColliding && position.x > 20 )
		{
			isWalking = true;
			if (currentAnimation != &backwardAnim)
			{
				currentAnimation = &backwardAnim;
				currentAnimation->Reset();
			}
			position.x -= speed;
		}

		// Spawn shuriken particles when pressing LALT
		if (App->input->keys[SDL_SCANCODE_LALT] == KEY_DOWN && !isWalking && !isCrouching)
		{
			isShooting = true;
			if (currentAnimation != &shootAnim)
			{
				currentAnimation = &shootAnim;
				currentAnimation->Reset();
			}
			App->audio->PlayFx(App->audio->shuriken);
			App->particles->AddParticle(App->particles->shuriken, position.x + 35, position.y - 50, Collider::Type::PLAYER_SHOT);
		
		}

		if (App->input->keys[SDL_SCANCODE_W] == KEY_REPEAT && !isWalking && !isCrouching)
		{
			isJumpingUp1 = true;
			if (currentAnimation != &backAnim)
			{
				currentAnimation = &backAnim;
				currentAnimation->Reset();
			}
		}

		if (App->input->keys[SDL_SCANCODE_S] == KEY_REPEAT && !isWalking && !isCrouching)
		{
			isJumpingDown1 = true;
			if (currentAnimation != &backAnim)
			{
				currentAnimation = &backAnim;
				currentAnimation->Reset();
			}
		}

		if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_DOWN && !isJumping && isJumpingUp1 && App->scene->stage1)
		{
			isJumpingUp2 = true;
			jumpPosition.y = position.y;
		}

		if (isJumpingUp2)
		{
			if (!jumpState)
			{
				if (position.y >= 70)
				{

					currentAnimation = &jumpUpAnim;
					currentAnimation->Update();
					position.y -= speed;
					collider->SetPos(position.x, position.y - 58);
					feet->SetPos(position.x, position.y - 1);
				}
				if (position.y == 70)
				{
					jumpState = true;
				}
			}
			else
			{
				L2 = true;
				if (position.y >= 70 && position.y <= 96)
				{
					currentAnimation = &jumpUpAnim;
					currentAnimation->Update();
					position.y += 1.2;
					collider->SetPos(position.x, position.y - 58);
					feet->SetPos(position.x, position.y - 1);
				}
				if (position.y == 96)
				{
					isJumpingUp1 = false;
					isJumpingUp2 = false;
					jumpState = false;
					currentAnimation = &idleAnim;
				}
			}
			currentAnimation->Update();
			return update_status::UPDATE_CONTINUE;
		}

		if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_DOWN && !isJumping && isJumpingDown1)
		{
			isJumpingDown2 = true;
			jumpPosition.y = position.y;
		}

		if (isJumpingDown2)
		{
			if (!jumpState)
			{
				if (position.y >= 69)
				{
					currentAnimation = &jumpUpAnim;
					currentAnimation->Update();
					position.y -= speed;
					collider->SetPos(position.x, position.y - 58);
					feet->SetPos(position.x, position.y - 1);
				}
				if (position.y == 69)
				{
					jumpState = true;
				}
			}
			else
			{
				L2 = false;
				if (position.y >= 69 && position.y <= 208)
				{
					currentAnimation = &jumpUpAnim;
					currentAnimation->Update();
					position.y += 1.2;
					collider->SetPos(position.x, position.y - 58);
					feet->SetPos(position.x, position.y - 1);
				}
				if (position.y == 208)
				{
					isJumpingDown1 = false;
					isJumpingDown2 = false;
					jumpState = false;
					currentAnimation = &idleAnim;
				}
			}
			currentAnimation->Update();
			return update_status::UPDATE_CONTINUE;
		}

		//crouch animation
		if (App->input->keys[SDL_SCANCODE_LCTRL] == KEY_REPEAT)
		{
			isCrouching = true;
			if (App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT)
			{
				isWalking = true;
				if (currentAnimation != &crouchForwardAnim)
				{
					currentAnimation = &crouchForwardAnim;
					currentAnimation->Reset();
				}
				position.x += speed;
			}
			else if (App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT)
			{
				isWalking = true;
				if (currentAnimation != &crouchBackwardAnim)
				{
					currentAnimation = &crouchBackwardAnim;
					currentAnimation->Reset();
				}
				position.x -= speed;
			}
			else if (App->input->keys[SDL_SCANCODE_LALT] == KEY_DOWN && !isWalking)
			{
				isShooting = true;
				if (currentAnimation != &crouchAttackAnim)
				{
					currentAnimation = &crouchAttackAnim;
					currentAnimation->Reset();
				}
				App->audio->PlayFx(App->audio->shuriken);
				App->particles->AddParticle(App->particles->shuriken, position.x + 35 , position.y - 30, Collider::Type::PLAYER_SHOT);
			}
			else if (App->input->keys[SDL_SCANCODE_LSHIFT] == KEY_DOWN && !isWalking)
			{
				isKicking = true;
				if (currentAnimation != &crouchKatanaAnim)
				{
					currentAnimation = &crouchKatanaAnim;
					currentAnimation->Reset();
				}
			}
			else if (App->input->keys[SDL_SCANCODE_RSHIFT] == KEY_DOWN && !isWalking)
			{
				isKicking = true;
				if (currentAnimation != &crouchKickAnim)
				{
					currentAnimation = &crouchKickAnim;
					currentAnimation->Reset();
				}
			}
			else if(!isShooting && !isWalking && !isKicking)
			{
				if (currentAnimation != &crouchAnim)
				{
					currentAnimation = &crouchAnim;
					currentAnimation->Reset();
				}
			}

		}

		//key conditions
		if (isCrouching && App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT
			&& App->input->keys[SDL_SCANCODE_LCTRL] == KEY_IDLE
			|| isCrouching && App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT
			&& App->input->keys[SDL_SCANCODE_LCTRL] == KEY_IDLE)
		{
			isCrouching = false;
			currentAnimation = &idleAnim;
		}
		if (isCrouching && App->input->keys[SDL_SCANCODE_D] == KEY_IDLE
			&& App->input->keys[SDL_SCANCODE_LCTRL] == KEY_REPEAT
			|| isCrouching && App->input->keys[SDL_SCANCODE_A] == KEY_IDLE
			&& App->input->keys[SDL_SCANCODE_LCTRL] == KEY_REPEAT)
		{
			isWalking = false;
		}
		if (isCrouching && App->input->keys[SDL_SCANCODE_LALT] == KEY_IDLE
			&& App->input->keys[SDL_SCANCODE_LCTRL] == KEY_REPEAT)
		{
			isShooting = false;
		}

		if (App->input->keys[SDL_SCANCODE_LSHIFT] == KEY_IDLE
			&& App->input->keys[SDL_SCANCODE_LCTRL] == KEY_REPEAT 
			|| App->input->keys[SDL_SCANCODE_RSHIFT] == KEY_IDLE
			&& App->input->keys[SDL_SCANCODE_LCTRL] == KEY_REPEAT)
		{
			kick++;
			if (kick == 180)
			{
				isKicking = false;
				kick = 0;
			}
		}

		if (App->input->keys[SDL_SCANCODE_D] == KEY_IDLE
			&& App->input->keys[SDL_SCANCODE_A] == KEY_IDLE
			&& App->input->keys[SDL_SCANCODE_LALT] == KEY_IDLE
			&& App->input->keys[SDL_SCANCODE_W] == KEY_IDLE
			&& App->input->keys[SDL_SCANCODE_S] == KEY_IDLE
			&& App->input->keys[SDL_SCANCODE_LCTRL] == KEY_IDLE)
		{
			isJumpingUp1 = false;
			isJumpingDown1 = false;
			isWalking = false;
			isShooting = false;
			isCrouching = false;
			isKicking = false;
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
	
	if (!ground && !isJumping) position.y+=2;

	collider->SetPos(position.x, position.y-58);
	feet->SetPos(position.x, position.y-1);

	currentAnimation->Update();

	return update_status::UPDATE_CONTINUE;
}

update_status ModulePlayer::PostUpdate()
{
	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	App->render->Blit(texture, position.x, position.y - rect.h, &rect);
	isColliding = false;
	ground = false;
	return update_status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{

	if (c2->type == Collider::Type::BOX)
	{
		isColliding = true;
		//position.x--;
		//App->render->camera.x++;
		cout << "collision" << endl;
	}
	if (c1->type == Collider::Type::FEET && c2->type == Collider::Type::GROUND)
	{
		ground = true;
		isJumping = false;
		if (!isJumpingDown2)
		{
			jumpState = false;
		}
	}
}