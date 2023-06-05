#include "SceneRanking.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleUI.h"
#include "Animation.h"
#include <string>
#include <iostream>
using namespace std;

SceneRanking::SceneRanking(bool startEnabled) : Module(startEnabled)
{
	missionrect.x = 1;
	missionrect.y = 35;
	missionrect.w = 116;
	missionrect.h = 17;

	missionrect2.x = 1;
	missionrect2.y = 52;
	missionrect2.w = 116;
	missionrect2.h = 17;

	missionAnim.PushBack({ 0,166,6,8 });
	missionAnim.PushBack({ 0,166,15,8 });
	missionAnim.PushBack({ 0,166,25,8 });
	missionAnim.PushBack({ 0,166,32,8 });
	missionAnim.PushBack({ 0,166,41,8 });
	missionAnim.PushBack({ 0,166,50,8 });
	missionAnim.PushBack({ 0,166,57,8 });
	missionAnim.PushBack({ 0,166,70,8 });
	missionAnim.PushBack({ 0,166,77,8 });
	missionAnim.PushBack({ 0,166,84,8 });
	missionAnim.PushBack({ 0,166,97,8 });
	missionAnim.PushBack({ 0,166,103,8 });
	missionAnim.PushBack({ 0,166,111,8 });
	missionAnim.PushBack({ 0,166,119,8 });
	missionAnim.PushBack({ 0,166,127,8 });
	missionAnim.PushBack({ 0,166,135,8 });
	missionAnim.PushBack({ 0,166,143,8 });
	missionAnim.PushBack({ 0,166,152,8 });
	missionAnim.PushBack({ 0,166,158,8 });
	missionAnim.PushBack({ 0,166,167,8 });
	missionAnim.PushBack({ 0,166,174,8 });
	missionAnim.PushBack({ 0,166,183,8 });
	missionAnim.PushBack({ 0,166,190,8 });

	missionAnim.speed = 0.2f;
	missionAnim.loop = false;

	score.x = 1;
	score.y = 191;
	score.h = 8;
	score.w = 81;

	hscore.x = 1;
	hscore.y = 204;
	hscore.h = 8;
	hscore.w = 79;

	for (int i = 0; i < 10; i++)
	{
		rscore[i] = { 1 + 8 * i, 60, 7, 8 };
	}

	for (int i = 0; i < 10; i++)
	{
		h_score[i] = { 1 + 8 * i, 71, 7, 8 };
	}
}

SceneRanking::~SceneRanking()
{

}

// Load assets
bool SceneRanking::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	grey = App->textures->Load("Assets/grey.png");
	hab1 = App->textures->Load("Assets/UI/skill1.png");
	hab2 = App->textures->Load("Assets/UI/skill2.png");
	hab3 = App->textures->Load("Assets/UI/skill3.png");
	nums = App->textures->Load("Assets/UI/nums.png");


	App->render->camera.x = 0;
	App->render->camera.y = 0;

	changescene = 0;

	currentAnim = &missionAnim;
	currentAnim->Reset();
	return ret;
}

Update_Status SceneRanking::Update()
{
	currentAnim->Update();

	changescene++;
	if (changescene >= 180)
	{
		App->fade->FadeToBlack(this, (Module*)App->intro, true, false, 50);
	}

	if (counter <= 150) counter++;
	else counter = 0;


	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneRanking::PostUpdate()
{
	// Draw everything --------------------------------------

	App->render->Blit(grey, 0, 0, SDL_FLIP_NONE, NULL);

	for (int i = 0; i < 3; i++)
	{
		if (counter < 50)
		{
			App->render->Blit(hab2, 15, 69 * i + 14, SDL_FLIP_NONE, NULL);
			App->render->Blit(hab1, 15, 69 * i + 37, SDL_FLIP_NONE, NULL);
			App->render->Blit(hab3, 15, 69 * i + 60, SDL_FLIP_NONE, NULL);

			App->render->Blit(hab2, 289, 69 * i + 14, SDL_FLIP_NONE, NULL);
			App->render->Blit(hab1, 289, 69 * i + 37, SDL_FLIP_NONE, NULL);
			App->render->Blit(hab3, 289, 69 * i + 60, SDL_FLIP_NONE, NULL);
		}
		else if (counter > 50 && counter < 100)
		{
			App->render->Blit(hab3, 15, 69 * i + 14, SDL_FLIP_NONE, NULL);
			App->render->Blit(hab2, 15, 69 * i + 37, SDL_FLIP_NONE, NULL);
			App->render->Blit(hab1, 15, 69 * i + 60, SDL_FLIP_NONE, NULL);

			App->render->Blit(hab3, 289, 69 * i + 14, SDL_FLIP_NONE, NULL);
			App->render->Blit(hab2, 289, 69 * i + 37, SDL_FLIP_NONE, NULL);
			App->render->Blit(hab1, 289, 69 * i + 60, SDL_FLIP_NONE, NULL);
		}
		else if (counter > 100 && counter < 150)
		{
			App->render->Blit(hab1, 15, 69 * i + 14, SDL_FLIP_NONE, NULL);
			App->render->Blit(hab3, 15, 69 * i + 37, SDL_FLIP_NONE, NULL);
			App->render->Blit(hab2, 15, 69 * i + 60, SDL_FLIP_NONE, NULL);

			App->render->Blit(hab1, 289, 69 * i + 14, SDL_FLIP_NONE, NULL);
			App->render->Blit(hab3, 289, 69 * i + 37, SDL_FLIP_NONE, NULL);
			App->render->Blit(hab2, 289, 69 * i + 60, SDL_FLIP_NONE, NULL);
		}
	}

	App->render->Blit(nums, 85, 60, SDL_FLIP_NONE, &score, 0.0f);
	App->render->Blit(nums, 85, 80, SDL_FLIP_NONE, &hscore, 0.0f);

	string sc = to_string(App->ui->scoreCounter);
	xpos = 220 - (sc.size() * 8);

	for (unsigned int i = 0; i < sc.size(); i++)
	{
		digit = sc[i] - '0';

		 App->render->Blit(nums, xpos + (i * 8), 60, SDL_FLIP_NONE, &rscore[digit], 0.0f);
	}

	string hscore = to_string(App->ui->highScore);
	xpos = 220 - (hscore.size() * 8);

	for (unsigned int i = 0; i < hscore.size(); i++)
	{
		digit = hscore[i] - '0';

		App->render->Blit(nums, xpos + (i * 8), 80, SDL_FLIP_NONE, &h_score[digit], 0.0f);
	}

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneRanking::CleanUp()
{
	App->textures->Unload(grey);

	return true;
}