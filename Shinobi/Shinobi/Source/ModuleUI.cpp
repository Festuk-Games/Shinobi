#include "ModuleUI.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"

ModuleUI::ModuleUI()
{
	host.x = 0;
	host.y = 0;
	host.h = 8;
	host.w = 8;

	life.x = 0;
	life.y = 0;
	life.h = 8;
	life.w = 8;

	skill.x = 0;
	skill.y = 0;
	skill.h = 14;
	skill.w = 16;
}

ModuleUI::~ModuleUI()
{

}

// Load assets
bool ModuleUI::Start()
{
	LOG("Loading UI assets");

	bool ret = true;

	hostage = App->textures->Load("Assets/UI/hostage.png");
	lifes = App->textures->Load("Assets/UI/lifes.png");
	skill2 = App->textures->Load("Assets/UI/skill2.png");

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
	App->render->Blit(hostage, 0, 0, &host, 0.0f);
	App->render->Blit(lifes, 16, 0, &life, 0.0f);
	App->render->Blit(skill2, 50, 0, &skill, 0.0f);

	return update_status::UPDATE_CONTINUE;
}