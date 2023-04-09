#include "ModuleScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"

ModuleScene::ModuleScene()
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

}

ModuleScene::~ModuleScene()
{

}

// Load assets
bool ModuleScene::Start()
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

update_status ModuleScene::Update()
{
	flag.Update();

	//next stage condition
	if (nextStage && stage1)
	{
		if (App->player->position.x >= 500)
		{
			stage1 = false;
			stage2 = true;
			App->player->position.x = 30;
			App->render->camera.x = 0;
			nextStage = false;
			App->audio->PlayMusic("Audio/music/mission_2.ogg", 2.0f);
		}
	}
	if (nextStage && stage2)
	{
		if (App->player->position.x >= 500)
		{
			stage2 = false;
			stage3 = true;
			App->player->position.x = 30;
			App->render->camera.x = 0;
			nextStage = false;
			App->audio->PlayMusic("Audio/music/mission_3.ogg", 2.0f);
		}
	}
	if (nextStage && stage3)
	{

	}

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleScene::PostUpdate()
{
	// Draw everything --------------------------------------
	if (stage1)
	{
		App->render->Blit(skyTexture, 0, -265, &sky, 0.375f); // sky
		App->render->Blit(stageTexture, 0, -(512 - SCREEN_HEIGHT), &ground, 0.75f); // ground


		if (App->audio->isPlaying);
		else
		{
			App->audio->isPlaying = true;
			App->audio->PlayMusic("Audio/music/mission_1.ogg", 2.0f);
		}
	}
	if (stage2)
	{
		App->render->Blit(skyTexture2, 0, -265, &sky, 0.375f); // sky
		App->render->Blit(stageTexture2, 0, -(512 - SCREEN_HEIGHT), &ground, 0.75f); // ground

	}
	if (stage3)
	{
		App->render->Blit(skyTexture3, 0, 0, &sky, 0.75); // sky
		App->render->Blit(stageTexture3, 0, 0, &ground, 0.75f); // ground

	}

	//App->render->Blit(stageTexture, 560, 8, &(flag.GetCurrentFrame()), 0.75f); // flag animation
	
	//App->render->Blit(stageTexture, 0, 0, &ground);

	return update_status::UPDATE_CONTINUE;
}