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

}

MissionNumScene::~MissionNumScene()
{

}

// Load assets
bool MissionNumScene::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	grey = App->textures->Load("Assets/grey.png");
	mission = App->textures->Load("Assets/ui/text2.png");
	name = App->textures->Load("Assets/ui/nums.png");

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	counter = 0;
	changescene = 0;
	writefx = 0;
	aux = 10;

	currentAnim = &missionAnim;
	currentAnim->Reset();
	return ret;
}

Update_Status MissionNumScene::Update()
{
	currentAnim->Update();

	/*changescene++;*/
	if (changescene >= 180)
	{
		App->fade->FadeToBlack(this, (Module*)App->mission, true, false, 50);
	}
	
	if (writefx <= 10)
	{
		if (aux == 10)
		{
			App->audio->PlayFx(App->audio->write);
			aux = 0;
			writefx++;
		}
		aux++;
	}

	if (counter <= 8) counter++;
	else counter = 0;

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status MissionNumScene::PostUpdate()
{
	// Draw everything --------------------------------------

	App->render->Blit(grey, 0, 0, SDL_FLIP_NONE, NULL);

	SDL_Rect rect = currentAnim->GetCurrentFrame();
	App->render->Blit(name, 65, 120, SDL_FLIP_NONE, &rect);

	if (counter <= 4) App->render->Blit(mission, 100, 60, SDL_FLIP_NONE, &missionrect, 0.0f);
	else App->render->Blit(mission, 100, 60, SDL_FLIP_NONE, &missionrect2, 0.0f);

	return Update_Status::UPDATE_CONTINUE;
}

bool MissionNumScene::CleanUp()
{
	App->textures->Unload(grey);
	App->textures->Unload(name);
	App->textures->Unload(mission);

	return true;
}