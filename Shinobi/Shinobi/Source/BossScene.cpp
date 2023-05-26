#include "BossScene.h"

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

BossScene::BossScene(bool startEnabled) : Module(startEnabled)
{

	// ground
	ground.x = 0;
	ground.y = 0;
	ground.w = 512;
	ground.h = 256;

	//sky
	sky.x = 0;
	sky.y = 0;
	sky.w = 512;
	sky.h = 256;

}

BossScene::~BossScene()
{

}

// Load assets
bool BossScene::Start()
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


	stageTexture = App->textures->Load("Assets/Scenes/layer_a2.png");
	skyTexture = App->textures->Load("Assets/Scenes/layer_b2.png");

	App->enemies->AddEnemy(ENEMY_TYPE::BOSS, 200, 100);
	App->collisions->AddCollider({ 0, 208, 2048, 2 }, Collider::Type::GROUND);

	return ret;
}

Update_Status BossScene::Update()
{

	//next stage condition
	if (nextStage)
	{
		if (App->player->position.x >= 2000)
		{
			clear = true;
			clearcount++;
			if (clearcount >= 60) App->fade->FadeToBlack(this, (Module*)App->missionComplete, false, false, 60);
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
Update_Status BossScene::PostUpdate()
{
	// Draw everything --------------------------------------

	App->render->Blit(skyTexture, 0, 0, SDL_FLIP_NONE, &sky, 1.0f); // sky
	App->render->Blit(stageTexture, 0, 0, SDL_FLIP_NONE, &ground, 1.0f); // ground

	return Update_Status::UPDATE_CONTINUE;
}

bool BossScene::CleanUp()
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