#include "MissionCompleteScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "Animation.h"

MissionCompleteScene::MissionCompleteScene(bool startEnabled) : Module(startEnabled)
{
	//rects

	ground.x = 0;
	ground.y = 0;
	ground.w = 160;
	ground.h = 208;

}

MissionCompleteScene::~MissionCompleteScene()
{

}

// Load assets
bool MissionCompleteScene::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	mission1_boss = App->textures->Load("Assets/Scenes/mission1_boss.png");

	timer = 0;
	changescene = 0;
	imageX = -80;
	imageY = 224;

	App->audio->isPlaying = false;
	Mix_HaltMusic();

	return ret;
}

Update_Status MissionCompleteScene::Update()
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
		App->fade->FadeToBlack(this, (Module*)App->ranking, false, true, 40);
		imageY -= 8;
		imageX += 6;
	}

	//move the image to the center
	if (imageY > 8 && imageX < (SCREEN_WIDTH - ground.w)) {
		imageY -= 8;
		imageX += 6;
	}
	if (changescene==25)
	{
		App->audio->PlayFx(App->audio->mission);
	}
	if (changescene==50)
	{
		App->audio->PlayFx(App->audio->mission1);
	}
	if (changescene==75)
	{
		App->audio->PlayFx(App->audio->finished);
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status MissionCompleteScene::PostUpdate()
{
	// Draw everything --------------------------------------

	App->render->Blit(mission1_boss, imageX, imageY, SDL_FLIP_NONE, &ground, 1.0f);

	return Update_Status::UPDATE_CONTINUE;
}

bool MissionCompleteScene::CleanUp()
{

	App->textures->Unload(mission1_boss);
	return true;
}