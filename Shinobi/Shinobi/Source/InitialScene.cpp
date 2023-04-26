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

}

InitialScene::~InitialScene()
{

}

// Load assets
bool InitialScene::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	logo = App->textures->Load("Assets/festuk_logo.png");
	
	/*App->audio->PlayMusic("Assets/Music/introTitle.ogg", 1.0f);*/

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status InitialScene::Update()
{
	delay++;
	if (delay >= 40) App->fade->FadeToBlack(this, (Module*)App->intro, false, false, 60);

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status InitialScene::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(logo, 0, 0, SDL_FLIP_NONE, NULL);


	return Update_Status::UPDATE_CONTINUE;
}