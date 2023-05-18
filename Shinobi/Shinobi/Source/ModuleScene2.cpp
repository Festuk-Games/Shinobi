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

	App->collisions->AddCollider({ 288, 175, 32, 1 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 576, 175, 64, 1 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 896, 175, 64, 1 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 960, 143, 352, 1 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 1024, 111, 224, 1 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 1120, 79, 32, 1 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 1312, 175, 96, 1 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 1568, 175, 32, 1 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 1600, 143, 96, 1 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 1600, 111, 32, 1 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 1696, 175, 32, 1 }, Collider::Type::GROUND);

	App->collisions->AddCollider({ 288, 176, 32, 32 }, Collider::Type::BOX);
	App->collisions->AddCollider({ 576, 176, 64, 32 }, Collider::Type::BOX);
	App->collisions->AddCollider({ 896, 176, 64, 32 }, Collider::Type::BOX);
	App->collisions->AddCollider({ 960, 144, 352, 64 }, Collider::Type::BOX);
	App->collisions->AddCollider({ 1024, 112, 224, 32 }, Collider::Type::BOX);
	App->collisions->AddCollider({ 1120, 80, 32, 32 }, Collider::Type::BOX);
	App->collisions->AddCollider({ 1312, 176, 96, 32 }, Collider::Type::BOX);
	App->collisions->AddCollider({ 1568, 176, 32, 32 }, Collider::Type::BOX);
	App->collisions->AddCollider({ 1600, 144, 96, 64 }, Collider::Type::BOX);
	App->collisions->AddCollider({ 1600, 112, 32, 32 }, Collider::Type::BOX);
	App->collisions->AddCollider({ 1696, 176, 32, 32 }, Collider::Type::BOX);

	App->collisions->AddCollider({ 0, 207, 2048, 2 }, Collider::Type::GROUND);
	
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
	
	if (App->player->position.x >= 2000)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneboss, false, false, 60);
		App->player->position.x = 30;
		App->render->camera.x = 0;
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