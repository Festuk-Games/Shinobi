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

	savet.x = 0;
	savet.y = 0;
	savet.h = 8;
	savet.w = 16;
	
	for	(int i = 0; i < 10; i++)
	{
		timer[i] = { 1 + 8* i, 1, 7, 14 };
	}

	points = { 81, 12, 3, 3 };

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
	skill1 = App->textures->Load("Assets/UI/skill1.png");
	skill2 = App->textures->Load("Assets/UI/skill2.png");
	skill3 = App->textures->Load("Assets/UI/skill3.png");
	nums = App->textures->Load("Assets/UI/nums.png");
	save = App->textures->Load("Assets/UI/save.png");

	return ret;
}

update_status ModuleUI::Update()
{

	//Timer one number every second
	timef2++;
	if (timef2 == 120)
	{
		timesec2--;
		timef2 = 0;
	}
	if (timesec2 < 0) timesec2 = 9;

	timef1++;
	if (timef1 == 1200)
	{
		timesec1--;
		timef1 = 0;
	}
	if (timesec1 < 0) timesec1 = 5;

	timef3++;
	if (timef3 == 1200*6)
	{
		timemin--;
		timef3 = 0;
	}

	return update_status::UPDATE_CONTINUE;
}


// Update: draw background
update_status ModuleUI::PostUpdate()
{
	
	//Draw the hostages
	for (int i = 0; i < 4; i++)
	{
		App->render->Blit(hostage, 40 + 8 * i, 200, &host, 0.0f);
	}

	//Draw the lifes
	for (int i = 0; i < 2; i++)
	{
		App->render->Blit(lifes, 16 + 8 * i, 20, &life, 0.0f);
	}

	//Draw the skills icons
	if (sk1)
	{
		App->render->Blit(skill1, 266, 200, &skill, 0.0f);
	}
	else if (sk2)
	{
		App->render->Blit(skill2, 266, 200, &skill, 0.0f);
	}
	else if (sk3)
	{
		App->render->Blit(skill3, 266, 200, &skill, 0.0f);
	}

	App->render->Blit(save, 24, 200, &savet, 0.0f);
	
	App->render->Blit(nums, 286, 200, &timer[timemin], 0.0f);
	App->render->Blit(nums, 295, 203, &points, 0.0f);
	App->render->Blit(nums, 295, 208, &points, 0.0f);
	App->render->Blit(nums, 300, 200, &timer[timesec1], 0.0f);
	App->render->Blit(nums, 308, 200, &timer[timesec2], 0.0f);
	
	

	return update_status::UPDATE_CONTINUE;
}