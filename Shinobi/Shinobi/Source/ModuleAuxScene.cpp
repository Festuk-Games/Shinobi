#include "ModuleAuxScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"

ModuleAuxScene::ModuleAuxScene(bool startEnabled) : Module(startEnabled)
{

	//stage1 rects
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

	//stage2 rects
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

	//stage3 rects
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

ModuleAuxScene::~ModuleAuxScene()
{

}

// Load assets
bool ModuleAuxScene::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	stageTextureL2 = App->textures->Load("Assets/Scenes/layer_aa.png");
	
	return ret;
}

Update_Status ModuleAuxScene::Update()
{

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status ModuleAuxScene::PostUpdate()
{
	// Draw everything --------------------------------------
	if (stage1)
	{
		if (App->player->L2) App->render->Blit(stageTextureL2, 0, -(512 - SCREEN_HEIGHT), SDL_FLIP_NONE, &ground, 1.0f); // groundL2
	}

	return Update_Status::UPDATE_CONTINUE;
}