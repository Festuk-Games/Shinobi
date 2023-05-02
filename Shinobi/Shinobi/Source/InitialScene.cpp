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
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			membersAnim.PushBack({ 384*j + 5*j, 224*i + 5*i, 384, 224 });
		}
	}

	for (int i = 2; i < 4; i++) 
	{
		for (int j = 0; j < 10; j++)
		{
			membersAnim2.PushBack({ 384 * j + 5 * j, 224 * i + 5 * i, 384, 224 });
		}
	}

	membersAnim.speed = 0.2f;
	membersAnim.loop = false;
	membersAnim2.speed = 0.2f;
	membersAnim2.loop = false;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			infoAnim1.PushBack({ 384 * j + 5 * j, 224 * i + 5 * i, 384, 224 });
		}
	}

	for (int i = 2; i < 4; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			infoAnim2.PushBack({ 384 * j + 5 * j, 224 * i + 5 * i, 384, 224 });
		}
	}

	for (int i = 4; i < 5; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			infoAnim3.PushBack({ 384 * j + 5 * j, 224 * i + 5 * i, 384, 224 });
		}
	}

	infoAnim1.speed = 0.2f;
	infoAnim1.loop = false;
	infoAnim2.speed = 0.2f;
	infoAnim2.loop = false;
	infoAnim3.speed = 0.2f;
	infoAnim3.loop = false;

	currentAnimation = &infoAnim1;
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
	
	/*App->audio->PlayMusic("Assets/Music/introTitle.ogg", 1.0f);*/

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status InitialScene::Update()
{

	if (delay <= 100) currentAnimation = &infoAnim1;
	else if (delay <= 200 && delay > 100) currentAnimation = &infoAnim2;
	else if (delay <= 300 && delay > 200) currentAnimation = &infoAnim3;

	else if (delay <= 400 && delay > 300) currentAnimation = &membersAnim;
	else currentAnimation = &membersAnim2;

	currentAnimation->Update();
	delay++;
	if (delay >= 520) App->fade->FadeToBlack(this, (Module*)App->intro, false, false, 20);

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status InitialScene::PostUpdate()
{
	// Draw everything --------------------------------------

	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	if (delay <=300)
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

	return true;
}