#include "LogoScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "Animation.h"

LogoScene::LogoScene(bool startEnabled) : Module(startEnabled)
{

}

LogoScene::~LogoScene()
{

}

// Load assets
bool LogoScene::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	logo = App->textures->Load("Assets/festuk_logo.png");

	/*App->audio->PlayMusic("Assets/Music/introTitle.ogg", 1.0f);*/

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status LogoScene::Update()
{
	delay++;
	if (delay >= 40) App->fade->FadeToBlack(this, (Module*)App->scene2, false, false, 60);

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status LogoScene::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(logo, 0, 0, SDL_FLIP_NONE, NULL);


	return Update_Status::UPDATE_CONTINUE;
}

bool LogoScene::CleanUp()
{
	App->textures->Unload(logo);

	return true;
}