#include "ModuleUI.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"

ModuleUI::ModuleUI()
{

}

ModuleUI::~ModuleUI()
{

}

// Load assets
bool ModuleUI::Start()
{
	LOG("Loading UI assets");

	bool ret = true;

	/*stageTextureL2 = App->textures->Load("Assets/layer_aa.png");*/

	return ret;
}

update_status ModuleUI::Update()
{

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleUI::PostUpdate()
{
	// Draw everything --------------------------------------
	//if (stage1)
	//{
	//	if (App->player->L2) App->render->Blit(stageTextureL2, 0, -(512 - SCREEN_HEIGHT), &ground, 0.75f); // groundL2
	//}

	return update_status::UPDATE_CONTINUE;
}