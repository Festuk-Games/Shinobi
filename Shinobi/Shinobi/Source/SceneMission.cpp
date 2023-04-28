#include "SceneMission.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleScene.h"

#include "ModuleFadeToBlack.h"

SceneMission::SceneMission(bool startEnabled) : Module(startEnabled)
{
	//rects
	
	ground.x = 0;
	ground.y = 0;
	ground.w = 160;
	ground.h = 208;
	
}

SceneMission::~SceneMission()
{

}

// Load assets
bool SceneMission::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	mission1_0 = App->textures->Load("Assets/Scenes/mission1_0.png");
	mission1_1 = App->textures->Load("Assets/Scenes/mission1_1.png");

	return ret;
}

Update_Status SceneMission::Update()
{
	timer++;
	changescene++;
	if (timer == 10) s1 = false;
	if (timer == 20)
	{
		s1 = true;
		timer = 0;
	}
	if (changescene >= 100)
	{
		App->fade->FadeToBlack(this, (Module*)App->scene, false, true, 40);
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
Update_Status SceneMission::PostUpdate()
{
	// Draw everything --------------------------------------

	if (s1) App->render->Blit(mission1_0, imageX, imageY, SDL_FLIP_NONE, &ground, 1.0f); 
	else App->render->Blit(mission1_1, imageX, imageY, SDL_FLIP_NONE, &ground, 1.0f);

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneMission::CleanUp()
{
	App->textures->Unload(mission1_0);
	App->textures->Unload(mission1_1);
	return true;
}