#include "ModuleScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleScene::ModuleScene()
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

ModuleScene::~ModuleScene()
{

}

// Load assets
bool ModuleScene::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	stageTexture = App->textures->Load("Assets/layer_a.png");
	skyTexture = App->textures->Load("Assets/layer_b.png");

	return ret;
}

update_status ModuleScene::Update()
{
	flag.Update();

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleScene::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(skyTexture, 0, -265, &sky, 0.375f); // sky
	App->render->Blit(stageTexture, 0, -(512 - SCREEN_HEIGHT), &ground, 0.75f); // ground

	//App->render->Blit(stageTexture, 560, 8, &(flag.GetCurrentFrame()), 0.75f); // flag animation

	// TODO 2: Draw the ship from the sprite sheet with some parallax effect

	// TODO 3: Animate the girl on the ship (see sprite sheet)
	
	//App->render->Blit(stageTexture, 0, 0, &ground);

	return update_status::UPDATE_CONTINUE;
}