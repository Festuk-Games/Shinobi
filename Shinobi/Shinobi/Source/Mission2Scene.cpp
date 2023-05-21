#include "Mission2Scene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "Animation.h"

Mission2Scene::Mission2Scene(bool startEnabled) : Module(startEnabled)
{
	//rects

	ground.x = 0;
	ground.y = 0;
	ground.w = 160;
	ground.h = 208;

}

Mission2Scene::~Mission2Scene()
{

}

// Load assets
bool Mission2Scene::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	mission1_1 = App->textures->Load("Assets/Scenes/mission1_1.png");
	mission1_2 = App->textures->Load("Assets/Scenes/mission1_2.png");

	timer = 0;
	changescene = 0;
	imageX = -80;
	imageY = 224;

	return ret;
}

Update_Status Mission2Scene::Update()
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
		App->fade->FadeToBlack(this, (Module*)App->scene2, false, true, 40);
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
Update_Status Mission2Scene::PostUpdate()
{
	// Draw everything --------------------------------------

	if (s1) App->render->Blit(mission1_1, imageX, imageY, SDL_FLIP_NONE, &ground, 1.0f);
	else App->render->Blit(mission1_2, imageX, imageY, SDL_FLIP_NONE, &ground, 1.0f);

	return Update_Status::UPDATE_CONTINUE;
}

bool Mission2Scene::CleanUp()
{
	App->textures->Unload(mission1_1);
	App->textures->Unload(mission1_2);
	return true;
}