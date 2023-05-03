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

	// idle animation
	idleAnim.PushBack({211, 116, 76, 66});

	// walk forward animation
	walkAnim.PushBack({ 30, 30, 76, 66 });
	walkAnim.PushBack({ 105, 30, 76, 66 });
	walkAnim.PushBack({ 180, 30, 76, 66 });
	walkAnim.PushBack({ 255, 30, 76, 66 });
	walkAnim.PushBack({ 330, 30, 76, 66 });
	walkAnim.PushBack({ 405, 30, 76, 66 });
	walkAnim.loop = true;
	walkAnim.speed = 0.2f;

	//jump animation
	jumpUpAnim.PushBack({ 30, 210, 76, 66 });
	jumpDownAnim.PushBack({ 105, 210, 76, 66 });
	jumpUpAnim.loop = false;
	jumpUpAnim.speed = 0.1f;
	jumpDownAnim.loop = false;
	jumpDownAnim.speed = 0.1f;

	//jump up animation
	jumpUpFloorAnim.PushBack({ 617, 402, 76, 66 });
	jumpUpFloorAnim.PushBack({ 692, 402, 76, 66 });
	jumpUpFloorAnim.loop = false;
	jumpUpFloorAnim.speed = 0.001f;

	//jump down animation
	jumpDownFloorAnim.PushBack({ 798, 402, 76, 66 });
	jumpDownFloorAnim.PushBack({ 873, 402, 76, 66 });
	jumpDownFloorAnim.loop = false;
	jumpDownFloorAnim.speed = 0.03f;

	//crouch animation
	crouchIdleAnim.PushBack({30, 116, 76, 66 });
	crouchIdleAnim.loop = false;
	crouchIdleAnim.speed = 0.1f;

	//crouch right animation
	crouchAnim.PushBack({ 30, 401, 76, 66 });
	crouchAnim.PushBack({ 105, 401, 76, 66 });
	crouchAnim.PushBack({ 180, 401, 76, 66 });
	crouchAnim.loop = true;
	crouchAnim.speed = 0.1f;

	//crouch attack animation
	crouchAttackAnim.PushBack({ 1054, 402, 76, 66 });
	crouchAttackAnim.loop = false;
	crouchAttackAnim.speed = 0.1f;

	//crouch kick animation
	crouchKickAnim.PushBack({ 542,593,76,66 });
	crouchKickAnim.PushBack({ 617,593,76,66 });
	crouchKickAnim.PushBack({ 542,593,76,66 });
	crouchKickAnim.PushBack({ 30, 116, 76, 66 });
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
	dieAnim1.PushBack({ 798,593,76,66 });
	dieAnim2.PushBack({ 873,593,76,66 });
	dieAnim2.PushBack({ 948,593,76,66 });
	dieAnim2.PushBack({ 1023,593,76,66 });
	dieAnim1.loop = false;
	dieAnim1.speed = 0.05f;
	dieAnim2.loop = false;
	dieAnim2.speed = 0.08f;

	//back animation
	backAnim.PushBack({ 542, 402, 76, 66 });
	backAnim.loop = false;
	backAnim.speed = 0.1f;

	//katana animation
	katanaAnim.PushBack({586, 497, 76, 66});
	katanaAnim.PushBack({ 661, 497, 76, 66 });
	katanaAnim.PushBack({ 736, 497, 76, 66 });
	katanaAnim.PushBack({ 811, 497, 76, 66 });
	katanaAnim.PushBack({ 211, 593, 76, 66 });
	katanaAnim.PushBack({ 286, 593, 76, 66 });
	katanaAnim.PushBack({ 361, 593, 76, 66 });
	katanaAnim.PushBack({ 436, 593, 76, 66 });
	katanaAnim.loop = false;
	katanaAnim.speed = 0.3f;


	attackJumpAnim1.PushBack({ 286, 209, 76, 66 });
	attackJumpAnim1.loop = false;
	attackJumpAnim1.speed = 0.1f;
	attackJumpAnim2.PushBack({ 361, 209, 76, 66 });
	attackJumpAnim2.loop = false;
	attackJumpAnim2.speed = 0.1f;

	katanaJumpAnim.PushBack({ 286, 209, 76, 66 });
	katanaJumpAnim.loop = false;
	katanaJumpAnim.speed = 0.1f;
}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;
	
	//initial position
	position.x = 30;
	position.y = 208;
	currentAnimation = &idleAnim;
	texture = App->textures->Load("Assets/main.png"); 
	katana = App->collisions->AddCollider({ 0,0,0,0 }, Collider::Type::PLAYER_SHOT, this);
	collider = App->collisions->AddCollider({ position.x, position.y-58, 35, 58 }, Collider::Type::PLAYER, this);
	feet = App->collisions->AddCollider({ position.x, position.y, 35, 1 }, Collider::Type::FEET, this);
	enemyNearCollider = App->collisions->AddCollider({ position.x-50, position.y, 135, 58 }, Collider::Type::ENEMY_NEAR, this);

	App->ui->lifenum = 2;

	return ret;
} 

Update_Status ModulePlayer::Update()
{
	flipPos.x = position.x - 25;
	//Player movement
	if (alive)
	{
		if (App->input->keys[SDL_SCANCODE_F3] == KEY_DOWN)
		{
			collision = !collision;
		}
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
					if (jumpAttackDelay <= 0) currentAnimation = &jumpUpAnim;
					else jumpAttackDelay--;
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
					if (position.y <= 97)
					{
						App->render->camera.y+=8;
						App->render->jumpcam+=2;
					}
					if (App->input->keys[SDL_SCANCODE_LALT] == KEY_DOWN)
					{
						if (!enemyNear)
						{
							currentAnimation = &attackJumpAnim1;
							App->audio->PlayFx(App->audio->shuriken);
							if (right) App->particles->shuriken.speed = iPoint(5, 0);
							else App->particles->shuriken.speed = iPoint(-5, 0);
							App->particles->AddParticle(App->particles->shuriken, position.x + 35, position.y - 50, Collider::Type::PLAYER_SHOT);
						}
						else
						{
							currentAnimation = &katanaJumpAnim;
						}
						jumpAttackDelay+=5;
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
					if (jumpAttackDelay <= 0)
					{
						currentAnimation = &jumpDownAnim;
					}
					else jumpAttackDelay--;
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
					if (position.y <= 97 && App->render->jumpcam >= 1)
					{
						App->render->camera.y-=4;
						App->render->jumpcam--;
					}
					if (App->input->keys[SDL_SCANCODE_LALT] == KEY_DOWN)
					{
						if (!enemyNear)
						{
							currentAnimation = &attackJumpAnim2;
							App->audio->PlayFx(App->audio->shuriken);
							if (right) App->particles->shuriken.speed = iPoint(5, 0);
							else App->particles->shuriken.speed = iPoint(-5, 0);
							App->particles->AddParticle(App->particles->shuriken, position.x + 35, position.y - 50, Collider::Type::PLAYER_SHOT);
						}
						else
						{
							currentAnimation = &katanaJumpAnim;
						}
						jumpAttackDelay+=5;
					}
				}
			}
			currentAnimation->Update();
			return Update_Status::UPDATE_CONTINUE;
		}
		if (App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT && !isCrouching && !isColliding && position.x < 2010)
		{
			right = true;
			isWalking = true;
			if (!isPowerUp) currentAnimation = &walkAnim;
			else currentAnimation = &walkGunAnim;
			position.x += speed;
		}
		if (App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT && !isCrouching && !isColliding && position.x > 20 )
		{
			right = false;
			isWalking = true;
			if (!isPowerUp) currentAnimation = &walkAnim;
			else currentAnimation = &walkGunAnim;
			position.x -= speed;
		}

		// Spawn shuriken particles when pressing LALT
		if (App->input->keys[SDL_SCANCODE_LALT] == KEY_DOWN && !isWalking && !isCrouching)
		{
			isShooting = true;
			if (!enemyNear)
			{
				currentAnimation = &shootAnim;
				App->audio->PlayFx(App->audio->shuriken);
				if (right) App->particles->shuriken.speed = iPoint(5, 0);
				else App->particles->shuriken.speed = iPoint(-5, 0);
				App->particles->AddParticle(App->particles->shuriken, position.x + 35, position.y - 50, Collider::Type::PLAYER_SHOT);
			}
			else if(enemyNear)
			{
				currentAnimation = &katanaAnim;
				currentAnimation->Reset();
				if (right)
				{
					katana->rect.w = 20;
					katana->rect.h = 20;
					katana->SetPos(position.x+55, position.y - 50);
				}
				else
				{
					katana->rect.w = 20;
					katana->rect.h = 20;
					katana->SetPos(position.x-20, position.y - 50);
				}
				/*katana->rect.w = 0;
				katana->rect.h = 0;*/
			}
			
		
		}
		//jumping to second floor input
		if (App->input->keys[SDL_SCANCODE_W] == KEY_REPEAT && !isWalking && !isCrouching && !L2)
		{
			isJumpingUp1 = true;
			currentAnimation = &backAnim;

		}
		//jumping to first floor input
		if (App->input->keys[SDL_SCANCODE_S] == KEY_REPEAT && !isWalking && !isCrouching && L2)
		{
			isJumpingDown1 = true;
			currentAnimation = &backAnim;

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

					currentAnimation = &jumpUpFloorAnim;
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
					currentAnimation = &jumpUpFloorAnim;
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
					currentAnimation = &jumpDownFloorAnim;
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
					currentAnimation = &jumpDownFloorAnim;
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
				if (!isPowerUp) currentAnimation = &crouchAnim;
				else currentAnimation = &crouchGunAnim;
				position.x += speed;
			}
			//crouch left
			else if (App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT && position.x > 20 && !isColliding)
			{
				right = false;
				isWalking = true;
				if (!isPowerUp) currentAnimation = &crouchAnim;
				else currentAnimation = &crouchGunAnim;
				position.x -= speed;
			}
			//crouch attack
			else if (App->input->keys[SDL_SCANCODE_LALT] == KEY_DOWN && !isWalking && !enemyNear && !isPowerUp)
			{
				isShooting = true;
				currentAnimation = &crouchAttackAnim;
				App->audio->PlayFx(App->audio->shuriken);
				if (right) App->particles->shuriken.speed = iPoint(5, 0);
				else App->particles->shuriken.speed = iPoint(-5, 0);
				App->particles->AddParticle(App->particles->shuriken, position.x + 35, position.y - 30, Collider::Type::PLAYER_SHOT);
			}
			//crouch attack
			else if (App->input->keys[SDL_SCANCODE_LALT] == KEY_DOWN && !isWalking && !enemyNear && isPowerUp)
			{
				isShooting = true;
				currentAnimation = &crouchAttackAnim;
				App->audio->PlayFx(App->audio->shuriken);
				if (right) App->particles->shuriken.speed = iPoint(5, 0);
				else App->particles->shuriken.speed = iPoint(-5, 0);
				App->particles->AddParticle(App->particles->shuriken, position.x + 35, position.y - 30, Collider::Type::PLAYER_SHOT);
			}
			//crouch kick / crouch katana
			else if (App->input->keys[SDL_SCANCODE_LALT] == KEY_DOWN && !isWalking && enemyNear)
			{
				isKicking = true;
				if(!isPowerUp) currentAnimation = &crouchKickAnim;
				else {
					currentAnimation = &crouchKatanaAnim;
					currentAnimation->Reset();
					/*katana->rect.w = 10;
					katana->rect.h = 20;
					katana->SetPos(position.x, position.y);*/
				}
				/*katana->rect.w = 0;
				katana->rect.h = 0;*/


			}

			//crouch idle
			else if(!isShooting && !isWalking && !isKicking)
			{
				if (!isPowerUp) currentAnimation = &crouchIdleAnim;
				else currentAnimation = &crouchGunAnim;
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
		if (App->input->keys[SDL_SCANCODE_LALT] == KEY_IDLE
			&& App->input->keys[SDL_SCANCODE_LCTRL] == KEY_REPEAT)
		{
			//kick++;
			//if (kick >= 180)
			//{
				isKicking = false;
			//	kick = 0;
			//}
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
		if (App->ui->lifenum >=1 && dietime >= 60)
		{
			alive = true;
			position.x = 30;
			position.y = 208;
			App->render->camera.x = 0;
			dietime=0;
			diePos = false;
		}
		else if (App->ui->lifenum <= 0 && dietime >= 20)
		{
			App->ui->lose = true;
			dietime = 0;
		}
		dietime++;
	}
	
	//ground
	if (!ground && !isJumping) position.y+=2;

	//update colliders position
	collider->SetPos(position.x, position.y-58);
	feet->SetPos(position.x, position.y-1);
	enemyNearCollider->SetPos(position.x-50, position.y-58);
	currentAnimation->Update();

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePlayer::PostUpdate()
{
	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	if(right) App->render->Blit(texture, position.x, position.y - rect.h, SDL_FLIP_NONE, &rect);
	else App->render->Blit(texture, flipPos.x, position.y - rect.h, SDL_FLIP_HORIZONTAL, &rect);
	isColliding = false;
	ground = false;
	enemyNear = false;
	return Update_Status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
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

	//box collider
	if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::BOX || c2->type == Collider::Type::WALL)
	{
		if (!collision)
		{
			isColliding = false;
		}
		else
		{
			isColliding = true;
			cout << "collision" << endl;
		}
		
	}
	
	//enemy shot collider
	if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::ENEMY_SHOT)
	{
		if (!collision)
		{
			isColliding = false;
		}
		else {
			App->ui->lifenum--;
			alive = false;
		}
	}
	if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::HOSTAGE)
	{
		if (!collision)
		{
			isColliding = false;
			
		}
		cout << "collision" << endl;
		
	}
	if (c1->type == Collider::Type::ENEMY_NEAR && c2->type == Collider::Type::ENEMY)
	{
		enemyNear = true;
		cout << "near" << endl;
	}
}

bool ModulePlayer::CleanUp()
{
	App->textures->Unload(texture);

	return true;
}