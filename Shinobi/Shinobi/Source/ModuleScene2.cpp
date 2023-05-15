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


	stageTexture2 = App->textures->Load("Assets/Scenes/layer_a1.png");
	skyTexture2 = App->textures->Load("Assets/Scenes/layer_b1.png");

	//App->collisions->AddCollider({ 419, 175, 28, 1 }, Collider::Type::GROUND);
	//App->collisions->AddCollider({ 704, 175, 32, 1 }, Collider::Type::GROUND);
	//App->collisions->AddCollider({ 864, 175, 32, 1 }, Collider::Type::GROUND);
	//App->collisions->AddCollider({ 1408, 143, 32, 1 }, Collider::Type::GROUND);
	//App->collisions->AddCollider({ 1408, 175, 32, 1 }, Collider::Type::GROUND);
	//App->collisions->AddCollider({ 1440, 175, 32, 1 }, Collider::Type::GROUND);
	//App->collisions->AddCollider({ 1472, 175, 32, 1 }, Collider::Type::GROUND);
	//App->collisions->AddCollider({ 544, 63, 32, 1 }, Collider::Type::GROUND);

	//App->collisions->AddCollider({ 416, 176, 32, 32 }, Collider::Type::BOX);
	//App->collisions->AddCollider({ 704, 176, 32, 32 }, Collider::Type::BOX);
	//App->collisions->AddCollider({ 864, 176, 32, 32 }, Collider::Type::BOX);
	//App->collisions->AddCollider({ 1408, 144, 32, 32 }, Collider::Type::BOX);
	//App->collisions->AddCollider({ 1408, 176, 32, 32 }, Collider::Type::BOX);
	//App->collisions->AddCollider({ 1440, 176, 32, 32 }, Collider::Type::BOX);
	//App->collisions->AddCollider({ 1472, 176, 32, 32 }, Collider::Type::BOX);

	////App->collisions->AddCollider({ 544, 64, 32, 32 }, Collider::Type::WALL);

	App->collisions->AddCollider({ 0, 207, 2048, 2 }, Collider::Type::GROUND);
	//App->collisions->AddCollider({ 96, 95, 992, 7 }, Collider::Type::GROUND);
	//App->collisions->AddCollider({ 1296, 95, 656, 7 }, Collider::Type::GROUND);

	//App->collisions->AddCollider({ 80, -90, 16, 186 }, Collider::Type::WALL);
	//App->collisions->AddCollider({ 1088, -90, 16, 186 }, Collider::Type::WALL);
	//App->collisions->AddCollider({ 1280, -90, 16, 186 }, Collider::Type::WALL);
	//App->collisions->AddCollider({ 1952, -90, 16, 186 }, Collider::Type::WALL);
	//

	//App->enemies->AddEnemy(ENEMY_TYPE::GUNNER, 1000, 130);
	//App->enemies->AddEnemy(ENEMY_TYPE::GUNNER, 1600, 130);
	//App->enemies->AddEnemy(ENEMY_TYPE::FIGHTER, 350, 130);
	//App->enemies->AddEnemy(ENEMY_TYPE::FIGHTER, 500, 130);
	//App->enemies->AddEnemy(ENEMY_TYPE::FIGHTER, 1800, 130);
	//App->enemies->AddEnemy(ENEMY_TYPE::SOLDIER, 700, 130);
	//App->enemies->AddEnemy(ENEMY_TYPE::SOLDIER, 1200, 130);

	//App->hostage->AddHostage(HOSTAGE_TYPE::HOSTAGE, 800, 208 - 29);
	//App->hostage->AddHostage(HOSTAGE_TYPE::HOSTAGE, 480, 208 - 29);
	//App->hostage->AddHostage(HOSTAGE_TYPE::HOSTAGE, 1200, 208 - 29);
	//App->hostage->AddHostage(HOSTAGE_TYPE::HOSTAGE, 650, 68);
	//App->hostage->AddHostage(HOSTAGE_TYPE::HOSTAGE, 1500, 68);

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
			if (clearcount >= 60) App->fade->FadeToBlack(this, (Module*)App->intro, false, false, 60);
			//stage1 = false;
			//stage2 = true;
			//App->player->position.x = 30;
			//App->render->camera.x = 0;
			//nextStage = false;
			//App->audio->PlayMusic("Audio/music/mission_2.ogg", 0.5f);
		}
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