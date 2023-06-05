#include "MissionBossScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "Animation.h"

MissionBossScene::MissionBossScene(bool startEnabled) : Module(startEnabled)
{
	//rects

	ground.x = 0;
	ground.y = 0;
	ground.w = 160;
	ground.h = 208;

}

MissionBossScene::~MissionBossScene()
{

}

// Load assets
bool MissionBossScene::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	mission1_2 = App->textures->Load("Assets/Scenes/mission1_2.png");
	mission1_3 = App->textures->Load("Assets/Scenes/mission1_3.png");

	timer = 0;
	changescene = 0;
	imageX = -80;
	imageY = 224;

	App->audio->isPlaying = false;
	Mix_HaltMusic();

	return ret;
}

Update_Status MissionBossScene::Update()
{
	timer++;
	changescene++;
	if (timer == 4) s1 = false;
	else if (timer == 8)
	{
		s1 = true;
		timer = 0;
	}
	if (changescene >= 100)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneboss, false, true, 40);
		imageY -= 8;
		imageX += 6;
	}

	//move the image to the center
	if (imageY > 8 && imageX < (SCREEN_WIDTH - ground.w)) {
		imageY -= 8;
		imageX += 6;
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status MissionBossScene::PostUpdate()
{
	// Draw everything --------------------------------------

	if (s1) App->render->Blit(mission1_2, imageX, imageY, SDL_FLIP_NONE, &ground, 1.0f);
	else App->render->Blit(mission1_3, imageX, imageY, SDL_FLIP_NONE, &ground, 1.0f);

	return Update_Status::UPDATE_CONTINUE;
}

bool MissionBossScene::CleanUp()
{
	App->textures->Unload(mission1_2);
	App->textures->Unload(mission1_3);
	return true;
}