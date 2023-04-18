#include "ModuleScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"

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

	App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 600, 80);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 625, 80);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 640, 80);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 665, 80);

	if (stage1)
	{
		stageTexture = App->textures->Load("Assets/layer_a.png");
		stageTextureL2 = App->textures->Load("Assets/layer_aa.png");
		skyTexture = App->textures->Load("Assets/layer_b.png");
		stageTexture2 = App->textures->Load("Assets/layer_a1.png");
		skyTexture2 = App->textures->Load("Assets/layer_b1.png");
		stageTexture3 = App->textures->Load("Assets/layer_a2.png");
		skyTexture3 = App->textures->Load("Assets/layer_b2.png");

		App->collisions->AddCollider({ 416, 175, 32, 1 }, Collider::Type::GROUND);
		App->collisions->AddCollider({ 704, 175, 32, 1 }, Collider::Type::GROUND);
		App->collisions->AddCollider({ 864, 175, 32, 1 }, Collider::Type::GROUND);
		App->collisions->AddCollider({ 1408, 143, 32, 1 }, Collider::Type::GROUND);
		/*App->collisions->AddCollider({ 1408, 175, 32, 1 }, Collider::Type::GROUND);*/
		App->collisions->AddCollider({ 1440, 175, 32, 1 }, Collider::Type::GROUND);
		App->collisions->AddCollider({ 1472, 175, 32, 1 }, Collider::Type::GROUND);

		App->collisions->AddCollider({ 416, 176, 32, 32 }, Collider::Type::BOX);
		App->collisions->AddCollider({ 704, 176, 32, 32 }, Collider::Type::BOX);
		App->collisions->AddCollider({ 864, 176, 32, 32 }, Collider::Type::BOX);
		App->collisions->AddCollider({ 1408, 144, 32, 32 }, Collider::Type::BOX);
		App->collisions->AddCollider({ 1408, 176, 32, 32 }, Collider::Type::BOX);
		App->collisions->AddCollider({ 1440, 176, 32, 32 }, Collider::Type::BOX);
		App->collisions->AddCollider({ 1472, 176, 32, 32 }, Collider::Type::BOX);

		App->collisions->AddCollider({ 544, 64, 32, 32 }, Collider::Type::WALL);

		App->collisions->AddCollider({ 0, 207, 2048, 16 }, Collider::Type::GROUND);
		App->collisions->AddCollider({ 96, 95, 992, 7 }, Collider::Type::GROUND);
		App->collisions->AddCollider({ 1296, 95, 656, 7 }, Collider::Type::GROUND);

		App->collisions->AddCollider({ 80, -90, 16, 186 }, Collider::Type::WALL);
		App->collisions->AddCollider({ 1088, -90, 16, 186 }, Collider::Type::WALL);
		App->collisions->AddCollider({ 1280, -90, 16, 186 }, Collider::Type::WALL);
		App->collisions->AddCollider({ 1952, -90, 16, 186 }, Collider::Type::WALL);
	}


	return ret;
}

update_status ModuleScene::Update()
{

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
		App->render->Blit(skyTexture, 0, -265, &sky, 0.5f); // sky
		App->render->Blit(stageTexture, 0, -(512 - SCREEN_HEIGHT), &ground, 1.0f); // ground


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
