#include "ModuleAuxScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"

ModuleAuxScene::ModuleAuxScene()
{

	if (stage1)
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
	if (stage2)
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
	if (stage3)
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


	// Background / sky
	//ground.x = 0;
	//ground.y = 0;
	//ground.w = 2048;
	//ground.h = 512;

	// flag animation
	/*flag.PushBack({848, 208, 40, 40});
	flag.PushBack({848, 256, 40, 40});
	flag.PushBack({848, 304, 40, 40});
	flag.speed = 0.08f;*/

}

ModuleAuxScene::~ModuleAuxScene()
{

}

// Load assets
bool ModuleAuxScene::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	stageTexture = App->textures->Load("Assets/layer_a.png");
	stageTextureL2 = App->textures->Load("Assets/layer_aa.png");
	skyTexture = App->textures->Load("Assets/layer_b.png");
	stageTexture2 = App->textures->Load("Assets/layer_a1.png");
	skyTexture2 = App->textures->Load("Assets/layer_b1.png");
	stageTexture3 = App->textures->Load("Assets/layer_a2.png");
	skyTexture3 = App->textures->Load("Assets/layer_b2.png");

	return ret;
}

update_status ModuleAuxScene::Update()
{
	flag.Update();

	//next stage condition
	if (nextStage)
	{
		if (App->player->position.x >= 4000)
		{
			stage1 = false;
			stage2 = true;
			App->player->position.x = 30;
			App->render->camera.x = 0;
			nextStage = false;
		}
	}

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleAuxScene::PostUpdate()
{
	// Draw everything --------------------------------------
	if (stage1)
	{

		if (App->player->L2) App->render->Blit(stageTextureL2, 0, -(512 - SCREEN_HEIGHT), &ground, 0.75f); // groundL2
	}

	return update_status::UPDATE_CONTINUE;
}