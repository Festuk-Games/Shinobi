#include "ModuleScene2.h"

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

ModuleScene2::ModuleScene2(bool startEnabled) : Module(startEnabled)
{

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

ModuleScene2::~ModuleScene2()
{

}

// Load assets
bool ModuleScene2::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	App->ui->sk1 = true;
	App->ui->lose = false;
	nextStage = false;
	clear = false;

	//enable modules
	App->player->Enable();
	App->hostage->Enable();
	App->auxscene->Enable();
	App->enemies->Enable();
	App->ui->Enable();
	App->collisions->Enable();
	App->particles->Enable();

	App->render->camera.x = 0;

	stageTexture2 = App->textures->Load("Assets/Scenes/layer_a1.png");
	skyTexture2 = App->textures->Load("Assets/Scenes/layer_b1.png");

	App->collisions->AddCollider({ 288, 176, 32, 1 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 576, 176, 64, 1 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 896, 176, 64, 1 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 960, 144, 352, 1 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 1024, 112, 224, 1 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 1120, 80, 32, 1 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 1312, 176, 96, 1 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 1568, 176, 32, 1 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 1600, 144, 96, 1 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 1600, 112, 32, 1 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 1696, 176, 32, 1 }, Collider::Type::GROUND);

	App->collisions->AddCollider({ 288, 178, 32, 30 }, Collider::Type::BOX);
	App->collisions->AddCollider({ 576, 178, 64, 30 }, Collider::Type::BOX);
	App->collisions->AddCollider({ 896, 178, 64, 30 }, Collider::Type::BOX);
	App->collisions->AddCollider({ 960, 146, 352, 62 }, Collider::Type::BOX);
	App->collisions->AddCollider({ 1024, 114, 224, 30 }, Collider::Type::BOX);
	App->collisions->AddCollider({ 1120, 82, 32, 30 }, Collider::Type::BOX);
	App->collisions->AddCollider({ 1312, 178, 96, 30 }, Collider::Type::BOX);
	App->collisions->AddCollider({ 1568, 178, 32, 30 }, Collider::Type::BOX);
	App->collisions->AddCollider({ 1600, 146, 96, 62 }, Collider::Type::BOX);
	App->collisions->AddCollider({ 1600, 114, 32, 30 }, Collider::Type::BOX);
	App->collisions->AddCollider({ 1696, 178, 32, 30 }, Collider::Type::BOX);

	App->collisions->AddCollider({ 0, 208, 2048, 2 }, Collider::Type::GROUND);
	
	//rehenes
	App->hostage->AddHostage(HOSTAGE_TYPE::HOSTAGE, 295, 208 - 29- 32);
	App->hostage->AddHostage(HOSTAGE_TYPE::HOSTAGE, 870, 208 - 29);
	App->hostage->AddHostage(HOSTAGE_TYPE::HOSTAGE, 1640, 208 - 29-64);
	//enemigos luchadores grises
	App->enemies->AddEnemy(ENEMY_TYPE::FIGHTER, 325, 130);
	App->enemies->AddEnemy(ENEMY_TYPE::FIGHTER, 335, 130);
	App->enemies->AddEnemy(ENEMY_TYPE::FIGHTER, 340, 130);
	App->enemies->AddEnemy(ENEMY_TYPE::FIGHTER, 525, 130);
	App->enemies->AddEnemy(ENEMY_TYPE::FIGHTER, 841, 130);
	App->enemies->AddEnemy(ENEMY_TYPE::FIGHTER, 1064, 130-64-32);
	App->enemies->AddEnemy(ENEMY_TYPE::FIGHTER, 1122, 130 - 64 - 64);
	App->enemies->AddEnemy(ENEMY_TYPE::FIGHTER, 1154, 130 - 64 - 64);
	App->enemies->AddEnemy(ENEMY_TYPE::FIGHTER, 1468, 130);

	//Spiderman

	App->enemies->AddEnemy(ENEMY_TYPE::SPIDERMAN, 800, 80);

	//enemigos gunner
	App->enemies->AddEnemy(ENEMY_TYPE::GUNNER, 471, 139);
	App->enemies->AddEnemy(ENEMY_TYPE::GUNNER, 576, 139-32);
	App->enemies->AddEnemy(ENEMY_TYPE::GUNNER, 896, 139 - 32);
	App->enemies->AddEnemy(ENEMY_TYPE::GUNNER, 1233, 139 - 32);
	App->enemies->AddEnemy(ENEMY_TYPE::GUNNER, 1624, 139 - 32-64);

	App->enemies->AddEnemy(ENEMY_TYPE::SITTGUNNER, 350,130);

	//Enemigos Tochos (purple...)
	App->enemies->AddEnemy(ENEMY_TYPE::PURPLE, 831, 130);
	App->enemies->AddEnemy(ENEMY_TYPE::GREEN, 250, 130);


	return ret;
	
}

Update_Status ModuleScene2::Update()
{

	//next stage condition
	if (nextStage)
	{
		if (App->player->position.x >= 2000)
		{
			clear = true;
			clearcount++;
			if (clearcount >= 60) App->fade->FadeToBlack(this, (Module*)App->missionBoss, false, false, 60);
			//stage1 = false;
			//stage2 = true;
			//App->player->position.x = 30;
			//App->render->camera.x = 0;
			//nextStage = false;
			//App->audio->PlayMusic("Audio/music/mission_2.ogg", 0.5f);
		}
	}
	
	if (App->player->position.x >= 2000)
	{
		App->fade->FadeToBlack(this, (Module*)App->missionBoss, false, false, 60);
		//App->player->position.x = 30;
		//App->render->camera.x = 0;
	}

	if (App->ui->lose)
	{
		if (losecounter <= 120) losecounter++;
		else App->fade->FadeToBlack(this, (Module*)App->intro, false, false, 60);
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status ModuleScene2::PostUpdate()
{
	// Draw everything --------------------------------------

	App->render->Blit(skyTexture2, 0, -265, SDL_FLIP_NONE, &sky, 0.5f); // sky
	App->render->Blit(stageTexture2, 0, -(512 - SCREEN_HEIGHT), SDL_FLIP_NONE, &ground, 1.0f); // ground

	return Update_Status::UPDATE_CONTINUE;
}

bool ModuleScene2::CleanUp()
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