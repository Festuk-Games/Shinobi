#include "InitialScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "Animation.h"

InitialScene::InitialScene(bool startEnabled) : Module(startEnabled)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			membersAnim.PushBack({ 384*j + 5*j, 224*i + 5*i, 384, 224 });
		}
	}

	membersAnim.speed = 0.2f;
	membersAnim.loop = false;


	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			infoAnim.PushBack({ 384 * j + 5 * j, 224 * i + 5 * i, 384, 224 });
		}
	}

	infoAnim.speed = 0.2f;
	infoAnim.loop = false;

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			descriptionAnim.PushBack({ 384 * j + 5 * j, 224 * i + 5 * i, 384, 224 });
		}
	}

	descriptionAnim.speed = 0.2f;
	descriptionAnim.loop = false;

	currentAnimation = &descriptionAnim;
}

InitialScene::~InitialScene()
{
	
}

// Load assets
bool InitialScene::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	members = App->textures->Load("Assets/names_intro.png");
	info = App->textures->Load("Assets/intro_upc.png");
	description = App->textures->Load("Assets/intro_explicacion.png");
	
	/*App->audio->PlayMusic("Assets/Music/introTitle.ogg", 1.0f);*/

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	writefx = 0;
	return ret;
}

Update_Status InitialScene::Update()
{

	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->intro, false, false, 50);
	}

	if (writefx <= 28 && delay <= 320)
	{
		if (aux == 10)
		{
			App->audio->PlayFx(App->audio->write);
			aux = 0;
			writefx++;
		}
		aux++;
	}
	else if (writefx <= 23 && delay <= 580 && delay >= 320)
	{
		if (aux == 10)
		{
			App->audio->PlayFx(App->audio->write);
			aux = 0;
			writefx++;
		}
		aux++;
	}
	else if (writefx <= 16)
	{
		if (aux == 10)
		{
			App->audio->PlayFx(App->audio->write);
			aux = 0;
			writefx++;
		}
		aux++;
	}

	if (delay == 320)
	{
		writefx = 0;
		aux == 10;
	}
	if (delay == 580)
	{
		writefx = 0;
		aux == 10;
	}

	if (delay <= 320) currentAnimation = &descriptionAnim;
	else if (delay >= 320 && delay <= 580) currentAnimation = &infoAnim;
	else currentAnimation = &membersAnim;

	currentAnimation->Update();
	delay++;
	if (delay >= 820) App->fade->FadeToBlack(this, (Module*)App->intro, false, false, 20);

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status InitialScene::PostUpdate()
{
	// Draw everything --------------------------------------

	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	if (delay <=320)
	{
		App->render->Blit(description, 0, 0, SDL_FLIP_NONE, &rect);
	}
	else if (delay >= 320 && delay <= 580)
	{
		App->render->Blit(info, 0, 0, SDL_FLIP_NONE, &rect);
	}
	else App->render->Blit(members, 0, 0, SDL_FLIP_NONE, &rect);
	
	return Update_Status::UPDATE_CONTINUE;
}

bool InitialScene::CleanUp()
{
	App->textures->Unload(members);
	App->textures->Unload(info);
	App->textures->Unload(description);

	return true;
}