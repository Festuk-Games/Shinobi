#include "SceneMission.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleScene.h"

#include "ModuleFadeToBlack.h"

SceneMission::SceneMission(bool startEnabled) : Module(startEnabled)
{


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
	if (changescene >= 200)
	{
		App->fade->FadeToBlack(this, (Module*)App->scene, 40);
	}
	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneMission::PostUpdate()
{
	// Draw everything --------------------------------------

	if (s1) App->render->Blit(mission1_0, 112, 8, SDL_FLIP_NONE, &ground, 1.0f); 
	else App->render->Blit(mission1_1, 112, 8, SDL_FLIP_NONE, &ground, 1.0f);

	return Update_Status::UPDATE_CONTINUE;
}