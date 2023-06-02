#include "ModuleScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"

#include "ModulePlayer.h"
#include "ModuleUI.h"
#include "ModuleAuxScene.h"
#include "ModuleParticles.h"
#include "ModuleHostage.h"

#include "ModuleFadeToBlack.h"

ModuleScene::ModuleScene(bool startEnabled) : Module(startEnabled)
{
	//stage1 rects

	// ground
	ground.x = 0;
	ground.y = 0;
	ground.w = 2048;
	ground.h = 512;

	//sky
	sky.x = 0;
	sky.y = 0;
	sky.w = 1312;
	sky.h = 512;



}

ModuleScene::~ModuleScene()
{

}

// Load assets
bool ModuleScene::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	App->ui->sk1 = true;
	App->ui->lose = false;
	nextStage = false;
	clear = false;
	App->ui->scoreCounter = 0;
	App->ui->lifenum = 2;

	App->render->camera.x = 0;
	App->render->colPos = 0;
	//enable modules
	App->player->Enable();
	App->hostage->Enable();
	App->auxscene->Enable();
	App->enemies->Enable();
	App->ui->Enable();
	App->collisions->Enable();
	App->particles->Enable();

	if (stage1)
	{
		stageTexture = App->textures->Load("Assets/Scenes/layer_a.png");
		skyTexture = App->textures->Load("Assets/Scenes/layer_b.png");

		App->collisions->AddCollider({ 416, 176, 32, 1 }, Collider::Type::GROUND);
		App->collisions->AddCollider({ 704, 176, 32, 1 }, Collider::Type::GROUND);
		App->collisions->AddCollider({ 864, 176, 32, 1 }, Collider::Type::GROUND);
		App->collisions->AddCollider({ 1408, 144, 32, 1 }, Collider::Type::GROUND);
		//App->collisions->AddCollider({ 1408, 176, 32, 1 }, Collider::Type::GROUND);
		App->collisions->AddCollider({ 1440, 176, 32, 1 }, Collider::Type::GROUND);
		App->collisions->AddCollider({ 1472, 176, 32, 1 }, Collider::Type::GROUND);
		App->collisions->AddCollider({ 544, 64, 32, 1 }, Collider::Type::GROUND);

		App->collisions->AddCollider({ 416, 178, 32, 30 }, Collider::Type::BOX);
		App->collisions->AddCollider({ 704, 178, 32, 30 }, Collider::Type::BOX);
		App->collisions->AddCollider({ 864, 178, 32, 30 }, Collider::Type::BOX);
		App->collisions->AddCollider({ 1408, 146, 32, 30 }, Collider::Type::BOX);
		App->collisions->AddCollider({ 1408, 178, 32, 30 }, Collider::Type::BOX);
		App->collisions->AddCollider({ 1440, 178, 32, 30 }, Collider::Type::BOX);
		App->collisions->AddCollider({ 1472, 178, 32, 30 }, Collider::Type::BOX);
		App->collisions->AddCollider({ 544, 66, 32, 30 }, Collider::Type::BOX);

		//App->collisions->AddCollider({ 544, 64, 32, 32 }, Collider::Type::WALL);

		App->collisions->AddCollider({ 0, 208, 2048, 2 }, Collider::Type::GROUND);
		App->collisions->AddCollider({ 96, 96, 992, 2 }, Collider::Type::GROUND2);
		App->collisions->AddCollider({ 1296, 96, 656, 2 }, Collider::Type::GROUND2);

		App->collisions->AddCollider({ 80, -90, 16, 186 }, Collider::Type::WALL);
		App->collisions->AddCollider({ 1086, -90, 16, 186 }, Collider::Type::WALL);
		App->collisions->AddCollider({ 1280, -90, 16, 186 }, Collider::Type::WALL);
		App->collisions->AddCollider({ 1950, -90, 16, 186 }, Collider::Type::WALL);
	}
	//App->enemies->AddEnemy(ENEMY_TYPE::PURPLE, 272, 150);

	App->enemies->AddEnemy(ENEMY_TYPE::FIGHTER, 220, 142);
	//App->enemies->AddEnemy(ENEMY_TYPE::FIGHTER, 341, 130);
	App->enemies->AddEnemy(ENEMY_TYPE::GUNNER, 220, 139);
	//App->enemies->AddEnemy(ENEMY_TYPE::FIGHTER, 707, 130-32);
	//App->enemies->AddEnemy(ENEMY_TYPE::FIGHTER, 726, 130-32);
	//App->enemies->AddEnemy(ENEMY_TYPE::FIGHTER, 740, 130);
	//App->enemies->AddEnemy(ENEMY_TYPE::GUNNER, 783, 130);



	//Enemigos suelo arriba
	//App->enemies->AddEnemy(ENEMY_TYPE::GUNNER, 610, 97-78);
	App->enemies->AddEnemy(ENEMY_TYPE::FIGHTER, 958, 97 - 78);
	//App->enemies->AddEnemy(ENEMY_TYPE::PURPLE, 982, 0);

	
	App->hostage->AddHostage(HOSTAGE_TYPE::HOSTAGE, 480, 208 - 29);
	
	App->hostage->AddHostage(HOSTAGE_TYPE::HOSTAGE, 705, 97 - 29);
	App->hostage->AddHostage(HOSTAGE_TYPE::HOSTAGE, 1020, 97 - 29);
	//App->hostage->AddHostage(HOSTAGE_TYPE::HOSTAGE, 650, 68);
	App->hostage->AddHostage(HOSTAGE_TYPE::HOSTAGE, 1500, 68);

	return ret;
}

Update_Status ModuleScene::Update()
{

	//next stage condition
	if (nextStage && stage1)
	{
		if (App->player->position.x >= 2000)
		{
			//clear = true;
			clearcount++;
			if (clearcount >= 60)
			{
				App->fade->FadeToBlack(this, (Module*)App->mission2, false, false, 60);
				//App->player->position.x = 30;
				//App->render->camera.x = 0;
			}
			/*stage1 = false;
			stage2 = true;
			nextStage = false;
			App->audio->PlayMusic("Audio/music/mission_2.ogg", 0.5f);*/
		}
	}
	
	if (App->ui->lose)
	{
		if (losecounter <= 120) losecounter++;
		else App->fade->FadeToBlack(this, (Module*)App->intro, false, false, 60);
	}

	//if (App->player->L2 && !ground2)
	//{
	//	groundCol = App->collisions->AddCollider({ 96, 96, 992, 2 }, Collider::Type::GROUND);
	//	groundCol2 = App->collisions->AddCollider({ 1296, 96, 656, 2 }, Collider::Type::GROUND);
	//	ground2 = true;
	//}
	//else if (!App->player->L2 && ground2)
	//{
	//	groundCol->pendingToDelete = true;
	//	groundCol2->pendingToDelete = true;
	//	ground2 = false;
	//}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status ModuleScene::PostUpdate()
{
	// Draw everything --------------------------------------
	if (stage1)
	{
		App->render->Blit(skyTexture, 0, -265, SDL_FLIP_NONE, &sky, 0.5f); // sky
		App->render->Blit(stageTexture, 0, -(512 - SCREEN_HEIGHT), SDL_FLIP_NONE, &ground, 1.0f); // ground

		if (App->audio->isPlaying);
		else
		{
			App->audio->isPlaying = true;
			App->audio->PlayMusic("Audio/music/mission_1.ogg", 2.0f);
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

bool ModuleScene::CleanUp()
{
	//disable modules
	App->player->Disable();
	App->hostage->Disable();
	App->auxscene->Disable();
	App->enemies->Disable();
	App->ui->Disable();
	App->collisions->Disable();
	App->particles->Disable();
	App->textures->Unload(skyTexture);
	App->textures->Unload(stageTexture);
	App->textures->Unload(App->auxscene->stageTextureL2);
	App->textures->Unload(App->ui->hostage);
	App->textures->Unload(App->ui->lifes);
	App->textures->Unload(App->ui->skill1);
	App->textures->Unload(App->ui->skill2);
	App->textures->Unload(App->ui->skill3);
	App->textures->Unload(App->ui->nums);
	App->textures->Unload(App->ui->text2);

	return true;
}