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
#include "ModuleScene2.h"
#include "ModuleUi.h"

#include "ModuleCollisions.h"

#include "SDL/include/SDL_scancode.h"


ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{

	// idle animation
	idleAnim.PushBack({211, 116, 76, 66});

	// idle pow animation
	idlePowAnim.PushBack({ 286, 116, 76, 66 });

	// walk forward animation
	walkAnim.PushBack({ 30, 30, 76, 66 });
	walkAnim.PushBack({ 105, 30, 76, 66 });
	walkAnim.PushBack({ 180, 30, 76, 66 });
	walkAnim.PushBack({ 255, 30, 76, 66 });
	walkAnim.PushBack({ 330, 30, 76, 66 });
	walkAnim.PushBack({ 405, 30, 76, 66 });
	walkAnim.loop = true;
	walkAnim.speed = 0.2f;

	// walk gun animation
	walkGunAnim.PushBack({ 511, 30, 76, 66 });
	walkGunAnim.PushBack({ 586, 30, 76, 66 });
	walkGunAnim.PushBack({ 661, 30, 76, 66 });
	walkGunAnim.PushBack({ 736, 30, 76, 66 });
	walkGunAnim.PushBack({ 811, 30, 76, 66 });
	walkGunAnim.PushBack({ 886, 30, 76, 66 });
	walkGunAnim.loop = true;
	walkGunAnim.speed = 0.2f;

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
	jumpUpFloorAnim.speed = 0.46f;

	//jump down animation
	jumpDownFloorAnim.PushBack({ 798, 402, 76, 66 });
	jumpDownFloorAnim.PushBack({ 873, 402, 76, 66 });
	jumpDownFloorAnim.loop = false;
	jumpDownFloorAnim.speed = 0.06f;

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

	//gun attack animation
	powAttackAnim.PushBack({ 467, 116, 76, 66 });
	powAttackAnim.loop = false;
	powAttackAnim.speed = 0.1f;

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

	//punch
	punchAnim.PushBack({ 979, 116, 76, 66 });
	punchAnim.loop = false;
	punchAnim.speed = 0.1f;

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

	jumpUpPowAnim.PushBack({ 798, 209, 76, 66 });
	jumpDownPowAnim.PushBack({ 1023, 209, 76, 66 });
	jumpUpPowAnim.loop = false;
	jumpUpPowAnim.speed = 0.1f;
	jumpDownPowAnim.loop = false;
	jumpDownPowAnim.speed = 0.1f;

	attackJumpAnim1.PushBack({ 286, 209, 76, 66 });
	attackJumpAnim1.loop = false;
	attackJumpAnim1.speed = 0.1f;
	attackJumpAnim2.PushBack({ 361, 209, 76, 66 });
	attackJumpAnim2.loop = false;
	attackJumpAnim2.speed = 0.1f;

	katanaJumpAnim.PushBack({ 286, 209, 76, 66 });
	katanaJumpAnim.loop = false;
	katanaJumpAnim.speed = 0.1f;

	crouchPowAttackAnim.PushBack({ 30, 593, 76, 66 });
	crouchPowAttackAnim.loop = false;
	crouchPowAttackAnim.speed = 0.1f;

	crouchGunIdleAnim.PushBack({ 286, 401, 76, 66 });
	crouchGunIdleAnim.loop = true;
	crouchGunIdleAnim.speed = 0.1f;

	crouchGunAnim.PushBack({ 361, 401, 76, 66 });
	crouchGunAnim.PushBack({ 436, 401, 76, 66 });
	crouchGunAnim.PushBack({ 286, 401, 76, 66 });
	crouchGunAnim.loop = true;
	crouchGunAnim.speed = 0.1f;

	attackJumpPowAnim1.PushBack({ 873, 209, 76, 66 });
	attackJumpPowAnim1.loop = false;
	attackJumpPowAnim1.speed = 0.1f;
	attackJumpPowAnim2.PushBack({ 948, 209, 76, 66 });
	attackJumpPowAnim2.loop = false;
	attackJumpPowAnim2.speed = 0.1f;

	ultiAnim.PushBack({ 992, 30, 76, 66 });
	ultiAnim.loop = false;
	ultiAnim.speed = 0.1f;
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
	position.y = 209;
	App->ui->lifenum = 2;
	alive = true;
	isPowerUp = false;
	currentAnimation = &idleAnim;
	currentAnimation->Reset();

	texture = App->textures->Load("Assets/main.png"); 
	katana = App->collisions->AddCollider({ 0,0,0,0 }, Collider::Type::PLAYER_SHOT, this);
	collider = App->collisions->AddCollider({ position.x, position.y-58, 35, 58 }, Collider::Type::PLAYER, this);
	feet = App->collisions->AddCollider({ position.x+5, position.y, 35, 1 }, Collider::Type::FEET, this);
	enemyNearCollider = App->collisions->AddCollider({ position.x-40, position.y, 115, 58 }, Collider::Type::ENEMY_NEAR, this);

	ultiTimer = 0;

	return ret;
} 

Update_Status ModulePlayer::Update()
{
	if (position.y >= 100) L2 = false;
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
			App->audio->PlayFx(App->audio->jump);
			isJumping = true;
			jumpPosition.y = position.y;
		}
		//jump animation
		if (isJumping)
		{
			if (!jumpState)
			{
				if (position.y >= jumpPosition.y-73)
				{
					if (jumpAttackDelay <= 0 && !isPowerUp) currentAnimation = &jumpUpAnim;
					else if (jumpAttackDelay <= 0 && isPowerUp) currentAnimation = &jumpUpPowAnim;
					else jumpAttackDelay--;
					position.y -= 8;
					collider->SetPos(position.x, position.y - 58);
					feet->SetPos(position.x+5, position.y-1);
					enemyNearCollider->SetPos(position.x - 40, position.y - 58);
					if (App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT && position.x < 2010 && !isCollidingRight)
					{
						right = true;
						position.x += speed;
					}
					if (App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT && position.x > 20 && !isCollidingLeft)
					{
						right = false;
						position.x -= speed;
					}
					if (position.y <= 97 && App->scene->IsEnabled() && L2)
					{
						App->render->camera.y+=8;
						App->render->jumpcam+=2;
					}
					if (App->input->keys[SDL_SCANCODE_LALT] == KEY_DOWN)
					{
						if (!enemyNear && !isPowerUp)
						{
							currentAnimation = &attackJumpAnim1;
							App->audio->PlayFx(App->audio->shuriken);
							if (right)
							{
								App->particles->shuriken.speed = iPoint(5, 0);
								App->particles->AddParticle(App->particles->shuriken, position.x + 35, position.y - 50, Collider::Type::PLAYER_SHOT);
							}
							else
							{
								App->particles->shuriken.speed = iPoint(-5, 0);
								App->particles->AddParticle(App->particles->shuriken, position.x, position.y - 50, Collider::Type::PLAYER_SHOT);
							}
						}
						else if (!enemyNear && isPowerUp)
						{
							currentAnimation = &attackJumpPowAnim1;
							App->audio->PlayFx(App->audio->shuriken);
							if (right)
							{
								App->particles->powgun.fliph = false;
								App->particles->powgun.speed = iPoint(5, 0);
								App->particles->AddParticle(App->particles->powgun, position.x + 30, position.y - 47, Collider::Type::PLAYER_SHOT);
							}
							else
							{
								App->particles->powgun.fliph = true;
								App->particles->powgun.speed = iPoint(-5, 0);
								App->particles->AddParticle(App->particles->powgun, position.x+5, position.y - 47, Collider::Type::PLAYER_SHOT);
							}
						}
						else
						{
							currentAnimation = &katanaJumpAnim;
						}
						jumpAttackDelay+=10;
					}

				}
				if (position.y <= jumpPosition.y - 73)
				{
					jumpState = true;
				}
			}
			else
			{
				if (/*position.y >= jumpPosition.y - 72 && position.y <= 208 ||*/ !ground )
				{
					if (jumpAttackDelay <= 0 && !isPowerUp) currentAnimation = &jumpDownAnim;
					else if (jumpAttackDelay <= 0 && isPowerUp) currentAnimation = &jumpDownPowAnim;
					else jumpAttackDelay--;
					position.y += 4;
					collider->SetPos(position.x, position.y - 58);
					feet->SetPos(position.x+5, position.y-1);
					enemyNearCollider->SetPos(position.x - 40, position.y - 58);
					if (App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT && position.x < 2010 && !isCollidingRight)
					{
						right = true;
						position.x += speed;
					}
					if (App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT && position.x > 20 && !isCollidingLeft)
					{
						right = false;
						position.x -= speed;
					}
					if (position.y <= 97 && App->render->jumpcam >= 1 && App->scene->IsEnabled() && L2)
					{
						App->render->camera.y-=4;
						App->render->jumpcam--;
					}
					if (App->input->keys[SDL_SCANCODE_LALT] == KEY_DOWN)
					{
						if (!enemyNear && !isPowerUp)
						{
							currentAnimation = &attackJumpAnim2;
							App->audio->PlayFx(App->audio->shuriken);
							if (right)
							{
								App->particles->shuriken.speed = iPoint(5, 0);
								App->particles->AddParticle(App->particles->shuriken, position.x + 35, position.y - 50, Collider::Type::PLAYER_SHOT);
							}
							else
							{
								App->particles->shuriken.speed = iPoint(-5, 0);
								App->particles->AddParticle(App->particles->shuriken, position.x, position.y - 50, Collider::Type::PLAYER_SHOT);
							}
						}
						else if (!enemyNear && isPowerUp)
						{
							currentAnimation = &attackJumpPowAnim2;
							App->audio->PlayFx(App->audio->shuriken);
							if (right)
							{
								App->particles->powgun.fliph = false;
								App->particles->powgun.speed = iPoint(5, 0);
								App->particles->AddParticle(App->particles->powgun, position.x + 30, position.y - 47, Collider::Type::PLAYER_SHOT);
							}
							else
							{
								App->particles->powgun.fliph = true;
								App->particles->powgun.speed = iPoint(-5, 0);
								App->particles->AddParticle(App->particles->powgun, position.x+5, position.y - 47, Collider::Type::PLAYER_SHOT);
							}
						}
						else
						{
							currentAnimation = &katanaJumpAnim;
						}
						jumpAttackDelay+=10;
					}
				}
			}
			currentAnimation->Update();
			return Update_Status::UPDATE_CONTINUE;
		}
		if (App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT && !isCrouching && !isCollidingRight && !isJumpingUp2 && !isJumpingDown2 && position.x < 2010 
			&& App->input->keys[SDL_SCANCODE_A] == KEY_IDLE)
		{
			ulti = false;
			right = true;
			isWalking = true;
			if (!isPowerUp) currentAnimation = &walkAnim;
			else currentAnimation = &walkGunAnim;
			position.x += speed;
		}
		else if (App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT && !isCrouching && !isCollidingLeft && !isJumpingUp2 && !isJumpingDown2 && position.x > 20 
			&& App->input->keys[SDL_SCANCODE_D] == KEY_IDLE)
		{
			right = false;
			isWalking = true;
			if (!isPowerUp) currentAnimation = &walkAnim;
			else currentAnimation = &walkGunAnim;
			position.x -= speed;
		}

		// Spawn shuriken particles when pressing LALT
		if (App->input->keys[SDL_SCANCODE_LALT] == KEY_DOWN && !isWalking && !isCrouching && !isJumpingUp1)
		{
			isShooting = true;
			if (!enemyNear && !isPowerUp)
			{
				currentAnimation = &shootAnim;
				App->audio->PlayFx(App->audio->shuriken);
				if (right)
				{
					App->particles->shuriken.speed = iPoint(5, 0);
					App->particles->AddParticle(App->particles->shuriken, position.x + 35, position.y - 50, Collider::Type::PLAYER_SHOT);
				}
				else
				{
					App->particles->shuriken.speed = iPoint(-5, 0);
					App->particles->AddParticle(App->particles->shuriken, position.x, position.y - 50, Collider::Type::PLAYER_SHOT);
				}
			}
			else if (!enemyNear && isPowerUp)
			{
				currentAnimation = &powAttackAnim;
				App->audio->PlayFx(App->audio->shuriken);
				if (right)
				{
					App->particles->powgun.fliph = false;
					App->particles->powgun.speed = iPoint(5, 0);
					App->particles->AddParticle(App->particles->powgun, position.x + 30, position.y - 47, Collider::Type::PLAYER_SHOT);
				}
				else
				{
					App->particles->powgun.fliph = true;
					App->particles->powgun.speed = iPoint(-5, 0);
					App->particles->AddParticle(App->particles->powgun, position.x+5, position.y - 47, Collider::Type::PLAYER_SHOT);
				}
			}
			else if(enemyNear)
			{
				if (isPowerUp)
				{
					currentAnimation = &katanaAnim;
					currentAnimation->Reset();
				}
				else
				{
					currentAnimation = &punchAnim;
					currentAnimation->Reset();
				}
				katana->rect.w = 25;
				katana->rect.h = 25;
				if (right) katana->SetPos(position.x + 55, position.y - 50);
				else katana->SetPos(position.x - 20, position.y - 50);
				katana->rect.w = 0;
				katana->rect.h = 0;
				//katana->SetPos(0, 0);
			}
			
		}
		//jumping to second floor input
		if (App->input->keys[SDL_SCANCODE_W] == KEY_REPEAT && !isWalking && !isCrouching && !L2 && canjump)
		{
			isJumpingUp1 = true;
			currentAnimation = &backAnim;

		}
		//jumping to first floor input
		if (App->input->keys[SDL_SCANCODE_S] == KEY_REPEAT && !isWalking && !isCrouching && L2 && canjump)
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
					if (currentAnimation != &jumpUpFloorAnim)
					{
						currentAnimation = &jumpUpFloorAnim;
						currentAnimation->Reset();
					}
					currentAnimation->Update();
					position.y -= 10;
					collider->SetPos(position.x, position.y - 58);
					feet->SetPos(position.x+5, position.y - 1);
				}
				if (position.y <= 68)
				{
					jumpState = true;
				}
			}
			else
			{
				L2 = true;
				if (position.y >= 59 && position.y <= 95)
				{
					currentAnimation = &jumpUpFloorAnim;
					currentAnimation->Update();
					position.y += speed;
					collider->SetPos(position.x, position.y - 58);
					feet->SetPos(position.x+5, position.y - 1);
				}
				if (position.y == 95)
				{
					isJumpingUp1 = false;
					isJumpingUp2 = false;
					jumpState = false;
					if (!isPowerUp) currentAnimation = &idleAnim;
					else currentAnimation = &idlePowAnim;
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
				if (position.y >= 65)
				{
					if (currentAnimation != &jumpDownFloorAnim)
					{
						currentAnimation = &jumpDownFloorAnim;
						currentAnimation->Reset();
					}
					currentAnimation = &jumpDownFloorAnim;
					currentAnimation->Update();
					position.y -= 8;
					collider->SetPos(position.x, position.y - 58);
					feet->SetPos(position.x+5, position.y - 1);
				}
				if (position.y == 65)
				{
					jumpState = true;
				}
			}
			else
			{
				L2 = false;
				if (position.y >= 65 && position.y <= 208)
				{
					currentAnimation = &jumpDownFloorAnim;
					currentAnimation->Update();
					position.y += 4;
					collider->SetPos(position.x, position.y - 58);
					feet->SetPos(position.x+5, position.y - 1);
					enemyNearCollider->SetPos(position.x - 40, position.y - 58);
				}
				if (position.y == 209)
				{
					isJumpingDown1 = false;
					isJumpingDown2 = false;
					jumpState = false;
					if (!isPowerUp) currentAnimation = &idleAnim;
					else currentAnimation = &idlePowAnim;
				}
			}
			currentAnimation->Update();
			return Update_Status::UPDATE_CONTINUE;
		}
		//collision update
		if (isCrouching)
			{
				collider->rect.h = 35;
				collider->SetPos(position.x+5, position.y-35);
			}
		else
		{
			if (right)
			{
				collider->rect.h = 58;
				collider->SetPos(position.x + 3, position.y - 58);
			}
			else
			{
				collider->rect.h = 58;
				collider->SetPos(position.x - 3, position.y - 58);
			}
		}
		//crouch animation
		if (App->input->keys[SDL_SCANCODE_S] == KEY_REPEAT)
		{
			isCrouching = true;
			
			
			//coruch right
			if (App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT && position.x < 2010 && !isCollidingRight)
			{
				right = true;
				isWalking = true;
				if (!isPowerUp) currentAnimation = &crouchAnim;
				else currentAnimation = &crouchGunAnim;
				position.x += speed;
			}
			//crouch left
			else if (App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT && position.x > 20 && !isCollidingLeft)
			{
				right = false;
				isWalking = true;
				if (!isPowerUp) currentAnimation = &crouchAnim;
				else currentAnimation = &crouchGunAnim;
				position.x -= speed;
			}
			//crouch attack
			else if (App->input->keys[SDL_SCANCODE_LALT] == KEY_DOWN && !isWalking && !enemyNear)
			{
				if (!enemyNear && !isPowerUp)
				{
					isShooting = true;
					currentAnimation = &crouchAttackAnim;
					App->audio->PlayFx(App->audio->shuriken);
					if (right)
					{
						App->particles->shuriken.speed = iPoint(5, 0);
						App->particles->AddParticle(App->particles->shuriken, position.x + 35, position.y - 30, Collider::Type::PLAYER_SHOT);
					}
					else
					{
						App->particles->shuriken.speed = iPoint(-5, 0);
						App->particles->AddParticle(App->particles->shuriken, position.x, position.y - 30, Collider::Type::PLAYER_SHOT);
					}
				}
				else if (!enemyNear && isPowerUp)
				{
					isShooting = true;
					currentAnimation = &crouchPowAttackAnim;
					App->audio->PlayFx(App->audio->shuriken);
					if (right)
					{
						App->particles->powgun.fliph = false;
						App->particles->powgun.speed = iPoint(5, 0);
						App->particles->AddParticle(App->particles->powgun, position.x + 30, position.y - 25, Collider::Type::PLAYER_SHOT);
					}
					else
					{
						App->particles->powgun.fliph = true;
						App->particles->powgun.speed = iPoint(-5, 0);
						App->particles->AddParticle(App->particles->powgun, position.x+5, position.y - 25, Collider::Type::PLAYER_SHOT);
					}
				}
			}
			//crouch kick / crouch katana
			else if (App->input->keys[SDL_SCANCODE_LALT] == KEY_DOWN && !isWalking && enemyNear)
			{
				isKicking = true;
				if (!isPowerUp)
				{
					currentAnimation = &crouchKickAnim;
					currentAnimation->Reset();
					if (right)
					{
						katana->rect.w = 25;
						katana->rect.h = 25;
						katana->SetPos(position.x + 55, position.y - 50);
					}
					else
					{
						katana->rect.w = 25;
						katana->rect.h = 25;
						katana->SetPos(position.x - 20, position.y - 50);
					}
					katana->rect.w = 0;
					katana->rect.h = 0;
					//katana->SetPos(0, 0);
				}
				else {
					currentAnimation = &crouchKatanaAnim;
					currentAnimation->Reset();
					if (right)
					{
						katana->rect.w = 25;
						katana->rect.h = 25;
						katana->SetPos(position.x + 55, position.y - 50);
					}
					else
					{
						katana->rect.w = 25;
						katana->rect.h = 25;
						katana->SetPos(position.x - 20, position.y - 50);
					}
					katana->rect.w = 0;
					katana->rect.h = 0;
					//katana->SetPos(0, 0);
				}
			}

			//crouch idle
			else if(!isShooting && !isWalking && !isKicking)
			{
				if (!isPowerUp) currentAnimation = &crouchIdleAnim;
				else currentAnimation = &crouchGunIdleAnim;
			}
		}

		if (App->input->keys[SDL_SCANCODE_G] == KEY_DOWN)
		{
			ulti = true;
			ultiTimer = 0;
			currentAnimation = &ultiAnim;
			currentAnimation->Reset();
			App->particles->AddParticle(App->particles->ultimateEffect, position.x - 10, position.y - 80, Collider::Type::NONE);
		}
			
		if (ulti && ultiTimer <= 170) ultiTimer++;

		if (App->scene->IsEnabled())
		{
			if (ulti && ultiTimer == 100)
			{
				App->particles->AddParticle(App->particles->ultimate, position.x + 50, position.y - 62, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->ultimate, position.x + 10, position.y - 62, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->ultimate, position.x + 42, position.y - 62, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->ultimate, position.x + 18, position.y - 62, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->ultimate, position.x + 34, position.y - 62, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->ultimate, position.x + 26, position.y - 62, Collider::Type::PLAYER_SHOT);

				App->particles->AddParticle(App->particles->ultimate2, position.x - 50, position.y - 62, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->ultimate2, position.x - 10, position.y - 62, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->ultimate2, position.x - 42, position.y - 62, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->ultimate2, position.x - 18, position.y - 62, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->ultimate2, position.x - 34, position.y - 62, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->ultimate2, position.x - 26, position.y - 62, Collider::Type::PLAYER_SHOT);
			}
			if (ulti && ultiTimer == 120)
			{
				ulti = false;
				ultiTimer = 0;

				App->particles->AddParticle(App->particles->ultiCenterUp, position.x - 10, position.y - 90, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->ultiCenterUp, position.x + 10, position.y - 90, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->ultiUpRight2, position.x + 20, position.y - 90, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->ultiUpRight, position.x + 30, position.y - 80, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->ultiRight, position.x + 40, position.y - 80, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->ultiRight, position.x + 40, position.y - 70, Collider::Type::PLAYER_SHOT);

				App->particles->AddParticle(App->particles->ultiCenterDown, position.x - 10, position.y - 70, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->ultiCenterDown, position.x + 10, position.y - 70, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->ultiUpLeft2, position.x - 20, position.y - 90, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->ultiUpLeft, position.x - 30, position.y - 80, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->ultiLeft, position.x - 40, position.y - 80, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->ultiLeft, position.x - 40, position.y - 70, Collider::Type::PLAYER_SHOT);

				App->particles->AddParticle(App->particles->ultiDownRight2, position.x + 20, position.y - 60, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->ultiDownRight, position.x + 30, position.y - 70, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->ultiDownLeft2, position.x - 20, position.y - 60, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->ultiDownLeft, position.x - 30, position.y - 70, Collider::Type::PLAYER_SHOT);
			}
		}
		else if (App->scene2->IsEnabled())
		{
			if (ulti && ultiTimer == 100)
			{
				App->particles->AddParticle(App->particles->ultimateEffect2, position.x - 10, position.y - 200, Collider::Type::PLAYER_SHOT);
			}
			if (ulti && ultiTimer == 110) App->particles->AddParticle(App->particles->ultiWind, position.x - 70, position.y - 20, Collider::Type::PLAYER_SHOT);
			if (ulti && ultiTimer == 120) App->particles->AddParticle(App->particles->ultiWind, position.x - 70, position.y - 40, Collider::Type::PLAYER_SHOT);
			if (ulti && ultiTimer == 130) App->particles->AddParticle(App->particles->ultiWind, position.x - 70, position.y - 60, Collider::Type::PLAYER_SHOT);
			if (ulti && ultiTimer == 140) App->particles->AddParticle(App->particles->ultiWind, position.x - 70, position.y - 80, Collider::Type::PLAYER_SHOT);
			if (ulti && ultiTimer == 150) App->particles->AddParticle(App->particles->ultiWind, position.x - 70, position.y - 100, Collider::Type::PLAYER_SHOT);
			if (ulti && ultiTimer == 160) App->particles->AddParticle(App->particles->ultiWind, position.x - 70, position.y - 120, Collider::Type::PLAYER_SHOT);
			if (ulti && ultiTimer == 170) App->particles->AddParticle(App->particles->ultiWind, position.x - 70, position.y - 140, Collider::Type::PLAYER_SHOT);
			if (ulti && ultiTimer > 170)
			{
				ulti = false;
				ultiTimer = 0;
			}
		}

		//key conditions

		//not crouching
		if (isCrouching && App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT
			&& App->input->keys[SDL_SCANCODE_S] == KEY_IDLE
			|| isCrouching && App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT
			&& App->input->keys[SDL_SCANCODE_S] == KEY_IDLE)
		{
			isCrouching = false;
			if (!isPowerUp) currentAnimation = &idleAnim;
			else currentAnimation = &idlePowAnim;
		}
		//not walking
		if (isCrouching && App->input->keys[SDL_SCANCODE_D] == KEY_IDLE
			&& App->input->keys[SDL_SCANCODE_S] == KEY_REPEAT
			|| isCrouching && App->input->keys[SDL_SCANCODE_A] == KEY_IDLE
			&& App->input->keys[SDL_SCANCODE_S] == KEY_REPEAT)
		{
			isWalking = false;
		}
		if (isCrouching && App->input->keys[SDL_SCANCODE_LALT] == KEY_IDLE
			&& App->input->keys[SDL_SCANCODE_S] == KEY_REPEAT)
		{
			isShooting = false;
		}
		//not kicking
		if (App->input->keys[SDL_SCANCODE_LALT] == KEY_IDLE
			&& App->input->keys[SDL_SCANCODE_S] == KEY_REPEAT)
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
			if (!isPowerUp && !ulti) currentAnimation = &idleAnim;
			else if (!ulti) currentAnimation = &idlePowAnim;
		}


		if (position.x >= 90 && position.x <= 360
			|| position.x >= 440 && position.x <= 500 
			|| position.x >= 570 && position.x <= 660
			|| position.x >= 740 && position.x <= 820
			|| position.x >= 895 && position.x <= 1040
			|| position.x >= 1300 && position.x <= 1370
			|| position.x >= 1500 && position.x <= 1910)
		{
			canjump = true;
		}
		else
		{
			canjump = false;
		}
	}
	else
	{	//die
		isPowerUp = false;
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
			if (position.x >= 100)
			{
				App->render->camera.x += speed;
			}
		}
		else if (position.x <= diePosition.x - 25)
		{
			if (currentAnimation != &dieAnim2)
			{
				currentAnimation = &dieAnim2;
				currentAnimation->Reset();
			}
		}
		if (App->ui->lifenum >=0 && dietime >= 60)
		{
			alive = true;
			position.x = 30;
			position.y = 209;
			App->render->camera.x = 0;
			dietime=0;
			diePos = false;
		}
		else if (App->ui->lifenum < 0 && dietime >= 20)
		{
			App->ui->lose = true;
			dietime = 0;
		}
		dietime++;
	}
	
	//ground
	if (!ground && !isJumping)
	{
		currentAnimation = &jumpDownAnim;
		position.y += 2;
		if (position.y <= 97 && App->render->jumpcam >= 1 && App->scene->IsEnabled() && L2)
		{
			App->render->camera.y -= 4;
			App->render->jumpcam--;
		}
	}

	if (isCollidingRight) cout << "collision right" << endl;
	if (isCollidingLeft) cout << "collision left" << endl;

	//update colliders position
	//collider->SetPos(position.x, position.y-58);
	feet->SetPos(position.x+5, position.y-1);
	enemyNearCollider->SetPos(position.x-40, position.y-58);
	currentAnimation->Update();

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePlayer::PostUpdate()
{
	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	if(right) App->render->Blit(texture, position.x, position.y - rect.h, SDL_FLIP_NONE, &rect);
	else App->render->Blit(texture, flipPos.x, position.y - rect.h, SDL_FLIP_HORIZONTAL, &rect);
	isCollidingRight = false;
	isCollidingLeft = false;
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
			isCollidingLeft = false;
			isCollidingRight = false;
		}
		else if (right && collision)
		{
			isCollidingRight = true;
			isCollidingLeft = false;
		}
		else if (!right && collision)
		{
			isCollidingLeft = true;
			isCollidingRight = false;
		}
		
	}
	
	//enemy shot collider
	if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::ENEMY_SHOT)
	{
		if (!collision)
		{
			isCollidingLeft = false;
			isCollidingRight = false;
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
			isCollidingLeft = false;
			isCollidingRight = false;
			
		}
		cout << "collision" << endl;
		
	}
	if (c1->type == Collider::Type::ENEMY_NEAR && c2->type == Collider::Type::ENEMY)
	{
		enemyNear = true;
		//cout << "near" << endl;
	}
	if (c1->type == Collider::Type::PLAYER_SHOT && c2->type == Collider::Type::ENEMY)
	{
		katana->rect.w = 0;
		katana->rect.h = 0;
		//App->particles->AddParticle(App->particles->hit,katana->rect.x, katana->rect.y);
		katana->SetPos(0, 0);	
	}
}

bool ModulePlayer::CleanUp()
{
	App->textures->Unload(texture);

	return true;
}