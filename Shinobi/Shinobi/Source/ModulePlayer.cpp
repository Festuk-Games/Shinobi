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
#include "ModuleUi.h"

#include "ModuleCollisions.h"

#include "SDL/include/SDL_scancode.h"


ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{
	//initial position
	position.x = 30;
	position.y = 208;

	// idle animation
	idleAnim.PushBack({211, 116, 76, 66});

	// walk forward animation
	forwardAnim.PushBack({ 30, 30, 76, 66 });
	forwardAnim.PushBack({ 105, 30, 76, 66 });
	forwardAnim.PushBack({ 180, 30, 76, 66 });
	forwardAnim.PushBack({ 255, 30, 76, 66 });
	forwardAnim.PushBack({ 330, 30, 76, 66 });
	forwardAnim.PushBack({ 405, 30, 76, 66 });
	forwardAnim.loop = true;
	forwardAnim.speed = 0.2f;

	//walk backward animation
	backwardAnim.PushBack({ 30, 30, 76, 66 });
	backwardAnim.PushBack({ 105, 30, 76, 66 });
	backwardAnim.PushBack({ 180, 30, 76, 66 });
	backwardAnim.PushBack({ 255, 30, 76, 66 });
	backwardAnim.PushBack({ 330, 30, 76, 66 });
	backwardAnim.PushBack({ 405, 30, 76, 66 });
	backwardAnim.loop = true;
	backwardAnim.speed = 0.2f;

	//jump animation
	jumpAnim1.PushBack({ 30, 210, 76, 66 });
	jumpAnim2.PushBack({ 105, 210, 76, 66 });
	jumpAnim1.loop = false;
	jumpAnim1.speed = 0.1f;
	jumpAnim2.loop = false;
	jumpAnim2.speed = 0.1f;

	//jump up animation
	jumpUpAnim.PushBack({ 617, 402, 76, 66 });
	jumpUpAnim.PushBack({ 692, 402, 76, 66 });
	jumpUpAnim.loop = false;
	jumpUpAnim.speed = 0.03f;

	//crouch animation
	crouchAnim.PushBack({30, 116, 76, 66 });
	crouchAnim.loop = false;
	crouchAnim.speed = 0.1f;

	//crouch right animation
	crouchForwardAnim.PushBack({ 30, 401, 76, 66 });
	crouchForwardAnim.PushBack({ 105, 401, 76, 66 });
	crouchForwardAnim.PushBack({ 180, 401, 76, 66 });
	crouchForwardAnim.loop = true;
	crouchForwardAnim.speed = 0.1f;

	//crouch left animation
	crouchBackwardAnim.PushBack({ 30, 401, 76, 66 });
	crouchBackwardAnim.PushBack({ 105, 401, 76, 66 });
	crouchBackwardAnim.PushBack({ 180, 401, 76, 66 });
	crouchBackwardAnim.loop = true;
	crouchBackwardAnim.speed = 0.1f;

	//crouch attack animation
	crouchAttackAnim.PushBack({ 1054, 402, 76, 66 });
	crouchAttackAnim.loop = false;
	crouchAttackAnim.speed = 0.1f;

	//crouch kick animation
	crouchKickAnim.PushBack({ 380,654,45,40 });
	crouchKickAnim.PushBack({ 431,654,67,40 });
	crouchKickAnim.PushBack({ 504,654,45,40 });
	crouchKickAnim.loop = false;
	crouchKickAnim.speed = 0.1f;

	//crouch katana animation
	crouchKatanaAnim.PushBack({ 30,497,76,66 });
	crouchKatanaAnim.PushBack({ 105,497,76,66 });
	crouchKatanaAnim.PushBack({ 180,497,76,66 });
	crouchKatanaAnim.PushBack({ 255,497,76,66 });
	crouchKatanaAnim.PushBack({ 330,497,76,66 });
	crouchKatanaAnim.PushBack({ 405,497,76,66 });
	crouchKatanaAnim.PushBack({ 480,497,76,66 });
	crouchKatanaAnim.loop = false;
	crouchKatanaAnim.speed = 0.2f;

	//shoot animation
	shootAnim.PushBack({ 392, 116, 76, 66 });
	shootAnim.loop = false;
	shootAnim.speed = 0.1f;

	//die animation
	dieAnim1.PushBack({ 99,650,42,44 });
	dieAnim2.PushBack({ 147,650,42,44 });
	dieAnim2.PushBack({ 194,650,62,44 });
	dieAnim2.PushBack({ 262,650,72,44 });
	dieAnim1.loop = false;
	dieAnim1.speed = 0.05f;
	dieAnim2.loop = false;
	dieAnim2.speed = 0.08f;

	//back animation
	backAnim.PushBack({ 542, 402, 76, 66 });
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
	currentAnimation = &idleAnim;
	texture = App->textures->Load("Assets/main.png"); 
	collider = App->collisions->AddCollider({ position.x, position.y-58, 35, 58 }, Collider::Type::PLAYER, this);
	feet = App->collisions->AddCollider({ position.x, position.y, 35, 1 }, Collider::Type::FEET, this);

	return ret;
} 

Update_Status ModulePlayer::Update()
{
	//Player movement
	if (alive)
	{
		//Jumping input
		if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_DOWN && !isJumping && !isJumpingUp1 && !isJumpingDown1)
		{
			isJumping = true;
			jumpPosition.y = position.y;
		}
		//jump animation
		if (isJumping)
		{
			if (!jumpState)
			{
				if (position.y >= jumpPosition.y-72)
				{
					currentAnimation = &jumpAnim1;
					currentAnimation->Reset();
					position.y -= 8;
					collider->SetPos(position.x, position.y - 58); 
					feet->SetPos(position.x, position.y-1);
					if (App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT && position.x < 2010 && !isColliding)
					{
						position.x += speed;
					}
					if (App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT && position.x > 20 && !isColliding)
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
					if (App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT && position.x < 2010)
					{
						position.x += speed;
					}
					if (App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT && position.x > 20)
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
			return Update_Status::UPDATE_CONTINUE;
		}
		if (App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT && !isCrouching && !isColliding && position.x < 2010)
		{
			right = true;
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
			right = false;
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
			if (right) App->particles->shuriken.speed = iPoint(5, 0);
			else App->particles->shuriken.speed = iPoint(-5, 0);
			App->particles->AddParticle(App->particles->shuriken, position.x + 35, position.y - 50, Collider::Type::PLAYER_SHOT);
		
		}
		//jumping to second floor input
		if (App->input->keys[SDL_SCANCODE_W] == KEY_REPEAT && !isWalking && !isCrouching)
		{
			isJumpingUp1 = true;
			if (currentAnimation != &backAnim)
			{
				currentAnimation = &backAnim;
				currentAnimation->Reset();
			}
		}
		//jumping to first floor input
		if (App->input->keys[SDL_SCANCODE_S] == KEY_REPEAT && !isWalking && !isCrouching)
		{
			isJumpingDown1 = true;
			if (currentAnimation != &backAnim)
			{
				currentAnimation = &backAnim;
				currentAnimation->Reset();
			}
		}
		//jumping input -> second floor
		if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_DOWN && !isJumping && isJumpingUp1 && App->scene->stage1)
		{
			isJumpingUp2 = true;
			jumpPosition.y = position.y;
		}
		//jump to second floor animation
		if (isJumpingUp2)
		{
			if (!jumpState)
			{
				if (position.y >= 68)
				{

					currentAnimation = &jumpUpAnim;
					currentAnimation->Update();
					position.y -= 10;
					collider->SetPos(position.x, position.y - 58);
					feet->SetPos(position.x, position.y - 1);
				}
				if (position.y == 68)
				{
					jumpState = true;
				}
			}
			else
			{
				L2 = true;
				if (position.y >= 68 && position.y <= 95)
				{
					currentAnimation = &jumpUpAnim;
					currentAnimation->Update();
					position.y += speed;
					collider->SetPos(position.x, position.y - 58);
					feet->SetPos(position.x, position.y - 1);
				}
				if (position.y == 95)
				{
					isJumpingUp1 = false;
					isJumpingUp2 = false;
					jumpState = false;
					currentAnimation = &idleAnim;
				}
			}
			currentAnimation->Update();
			return Update_Status::UPDATE_CONTINUE;
		}
		//jumping input -> first floor 
		if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_DOWN && !isJumping && isJumpingDown1)
		{
			isJumpingDown2 = true;
			jumpPosition.y = position.y;
		}
		//jump to first floor animation
		if (isJumpingDown2)
		{
			if (!jumpState)
			{
				if (position.y >= 67)
				{
					currentAnimation = &jumpUpAnim;
					currentAnimation->Update();
					position.y -= 10;
					collider->SetPos(position.x, position.y - 58);
					feet->SetPos(position.x, position.y - 1);
				}
				if (position.y == 67)
				{
					jumpState = true;
				}
			}
			else
			{
				L2 = false;
				if (position.y >= 67 && position.y <= 208)
				{
					currentAnimation = &jumpUpAnim;
					currentAnimation->Update();
					position.y += speed;
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
			return Update_Status::UPDATE_CONTINUE;
		}

		//crouch animation
		if (App->input->keys[SDL_SCANCODE_LCTRL] == KEY_REPEAT)
		{
			isCrouching = true;
			//coruch right
			if (App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT && position.x < 2010 && !isColliding)
			{
				right = true;
				isWalking = true;
				if (currentAnimation != &crouchForwardAnim)
				{
					currentAnimation = &crouchForwardAnim;
					currentAnimation->Reset();
				}
				position.x += speed;
			}
			//crouch left
			else if (App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT && position.x > 20 && !isColliding)
			{
				right = false;
				isWalking = true;
				if (currentAnimation != &crouchBackwardAnim)
				{
					currentAnimation = &crouchBackwardAnim;
					currentAnimation->Reset();
				}
				position.x -= speed;
			}
			//crouch attack
			else if (App->input->keys[SDL_SCANCODE_LALT] == KEY_DOWN && !isWalking)
			{
				isShooting = true;
				if (currentAnimation != &crouchAttackAnim)
				{
					currentAnimation = &crouchAttackAnim;
					currentAnimation->Reset();
				}
				App->audio->PlayFx(App->audio->shuriken);
				if (right) App->particles->shuriken.speed = iPoint(5, 0);
				else App->particles->shuriken.speed = iPoint(-5, 0);
				App->particles->AddParticle(App->particles->shuriken, position.x + 35, position.y - 30, Collider::Type::PLAYER_SHOT);
			}
			//crouch katana
			else if (App->input->keys[SDL_SCANCODE_LSHIFT] == KEY_DOWN && !isWalking)
			{
				isKicking = true;
				if (currentAnimation != &crouchKatanaAnim)
				{
					currentAnimation = &crouchKatanaAnim;
					currentAnimation->Reset();
				}
			}
			//crouch kick
			else if (App->input->keys[SDL_SCANCODE_RSHIFT] == KEY_DOWN && !isWalking)
			{
				isKicking = true;
				if (currentAnimation != &crouchKickAnim)
				{
					currentAnimation = &crouchKickAnim;
					currentAnimation->Reset();
				}
			}
			//crouch idle
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

		//not crouching
		if (isCrouching && App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT
			&& App->input->keys[SDL_SCANCODE_LCTRL] == KEY_IDLE
			|| isCrouching && App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT
			&& App->input->keys[SDL_SCANCODE_LCTRL] == KEY_IDLE)
		{
			isCrouching = false;
			currentAnimation = &idleAnim;
		}
		//not walking
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
		//not kicking
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
		//idle
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
	{	//die
		if (!diePos)
		{
			diePosition = position;
			diePos = true;
		}
		if (position.x >= diePosition.x - 25 )
		{
			if (currentAnimation != &dieAnim1)
			{
				currentAnimation = &dieAnim1;
				currentAnimation->Reset();
			}
			position.x -= speed;
			App->render->camera.x += speed;
		}
		else if (position.x <= diePosition.x - 25)
		{
			if (currentAnimation != &dieAnim2)
			{
				currentAnimation = &dieAnim2;
				currentAnimation->Reset();
			}
		}
		if (App->ui->lifenum >=1 && dietime >= 100)
		{
			alive = true;
			position.x = 30;
			position.y = 208;
			App->render->camera.x = 0;
			dietime=0;
		}
		dietime++;
	}
	
	//ground
	if (!ground && !isJumping) position.y+=2;

	//update colliders position
	collider->SetPos(position.x, position.y-58);
	feet->SetPos(position.x, position.y-1);

	currentAnimation->Update();

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePlayer::PostUpdate()
{
	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	if(right) App->render->Blit(texture, position.x, position.y - rect.h, SDL_FLIP_NONE, &rect);
	else App->render->Blit(texture, position.x, position.y - rect.h, SDL_FLIP_HORIZONTAL, &rect);
	isColliding = false;
	ground = false;
	return Update_Status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	//box collider
	if (c2->type == Collider::Type::BOX)
	{
		isColliding = true;
		cout << "collision" << endl;
	}
	//ground collider
	if (c1->type == Collider::Type::FEET && c2->type == Collider::Type::GROUND)
	{
		ground = true;
		isJumping = false;
		if (!isJumpingDown2)
		{
			jumpState = false;
		}
	}
	//enemy shot collider
	if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::ENEMY_SHOT)
	{
		App->ui->lifenum--;
		alive = false;
	}
	if (c2->type == Collider::Type::HOSTAGE)
	{
		cout << "collision" << endl;
	}
}