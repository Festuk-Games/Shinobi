#include "LogoScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "Animation.h"
#include "ModuleUI.h"

LogoScene::LogoScene(bool startEnabled) : Module(startEnabled)
{

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			logoAnim.PushBack({ 320 * j + 1 * j, 224 * i + 1 * i, 320, 224 });
		}
	}

	logoAnim.speed = 0.2f;
	logoAnim.loop = false;
}

LogoScene::~LogoScene()
{

}

// Load assets
bool LogoScene::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	logo = App->textures->Load("Assets/Scenes/intro/festuk_logo.png");//ruta del spritesheet

	/*App->audio->PlayMusic("Assets/Music/introTitle.ogg", 1.0f);*/

	App->render->camera.x = 0;
	App->render->camera.y = 0;
	App->ui->lifenum = 2;
	currentAnim = &logoAnim;
	return ret;
}

Update_Status LogoScene::Update()
{
	currentAnim->Update();
	delay++;
	if (delay >= 200) App->fade->FadeToBlack(this, (Module*)App->scene, false, false, 60);//tiempo que tarda en cambiar la escena

	if(delay == 55)App->audio->PlayFx(App->audio->swoosh_logo);
	
	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status LogoScene::PostUpdate()
{
	SDL_Rect rect = currentAnim->GetCurrentFrame();
	// Draw everything --------------------------------------
	App->render->Blit(logo, 0, 0, SDL_FLIP_NONE, &rect);


	return Update_Status::UPDATE_CONTINUE;
}

bool LogoScene::CleanUp()
{
	App->textures->Unload(logo);

	return true;
}