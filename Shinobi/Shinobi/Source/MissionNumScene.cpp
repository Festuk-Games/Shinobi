#include "MissionNumScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "Animation.h"

MissionNumScene::MissionNumScene(bool startEnabled) : Module(startEnabled)
{
	
}

MissionNumScene::~MissionNumScene()
{

}

// Load assets
bool MissionNumScene::Start()
{
	LOG("Loading background assets");

	bool ret = true;


	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status MissionNumScene::Update()
{

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status MissionNumScene::PostUpdate()
{
	// Draw everything --------------------------------------

	return Update_Status::UPDATE_CONTINUE;
}

bool MissionNumScene::CleanUp()
{

	return true;
}