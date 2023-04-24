#include "SceneIntro.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "Animation.h"

SceneIntro::SceneIntro(bool startEnabled) : Module(startEnabled)
{
	lightAnim.PushBack({ 0,0,0,0 });
	lightAnim.PushBack({ 0,0,24,32 });
	lightAnim.PushBack({ 23,0,24,32 });
	lightAnim.PushBack({ 46,0,24,32 });
	lightAnim.PushBack({ 23,0,24,32 });
	lightAnim.PushBack({ 0,0,24,32 });
	lightAnim.PushBack({ 0,0,0,0 });
	lightAnim.speed = 0.35f;
	lightAnim.loop = false;
}

SceneIntro::~SceneIntro()
{

}

// Load assets
bool SceneIntro::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	introimage1 = App->textures->Load("Assets/intro.png");
	introimage2 = App->textures->Load("Assets/intro2.png");
	introimage3 = App->textures->Load("Assets/intro3.png");
	logo1 = App->textures->Load("Assets/logo.png");
	logo2 = App->textures->Load("Assets/logo2.png");
	logo3 = App->textures->Load("Assets/logo3.png");
	logo4 = App->textures->Load("Assets/logo4.png");
	logo5 = App->textures->Load("Assets/logo5.png");
	logo6 = App->textures->Load("Assets/logo6.png");
	sega = App->textures->Load("Assets/sega.png");
	light = App->textures->Load("Assets/light.png");
	/*App->audio->PlayMusic("Assets/Music/introTitle.ogg", 1.0f);*/

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	/*logopos.x = 0;
	logopos.y = 100;*/

	currentAnimation = &lightAnim;

	return ret;
}

Update_Status SceneIntro::Update()
{
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->mission, 90);
	}

	//if (App->input->keys[SDL_SCANCODE_W] == KEY_REPEAT) logopos.y--;
	//if (App->input->keys[SDL_SCANCODE_S] == KEY_REPEAT) logopos.y++;
	//if (App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT) logopos.x++;
	//if (App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT) logopos.x--;

	delay++;

	for (size_t i = 0; i <= 5; i++)
	{
		if (logos[i].radius >= 0 && delay >= i*3)
		{
			logos[i].time += 3;

			logos[i].radius -= logos[i].angularVelocity * 4;
			logos[i].logopos.x = logos[i].centerX + logos[i].radius * sin(logos[i].angularStep * logos[i].time);
			logos[i].logopos.y = logos[i].centerY + logos[i].radius * cos(logos[i].angularStep * logos[i].time);

		}
	}

	if (delay >= 240) currentAnimation->Update();
	
	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneIntro::PostUpdate()
{
	// Draw everything --------------------------------------
	if (delay <= 80 || delay >= 200) App->render->Blit(introimage1, 24, 0, SDL_FLIP_NONE, NULL);
	else if (delay >= 80 && delay <= 140) App->render->Blit(introimage2, 24, 0, SDL_FLIP_NONE, NULL);
	else if (delay >= 140 && delay <= 200) App->render->Blit(introimage3, 24, 0, SDL_FLIP_NONE, NULL);

	if (delay >= 15) App->render->Blit(logo6, logos[5].logopos.x, logos[5].logopos.y, SDL_FLIP_NONE, NULL);
	if (delay >= 12) App->render->Blit(logo5, logos[4].logopos.x, logos[4].logopos.y, SDL_FLIP_NONE, NULL);
	if (delay >= 9) App->render->Blit(logo4, logos[3].logopos.x, logos[3].logopos.y, SDL_FLIP_NONE, NULL);
	if (delay >= 6) App->render->Blit(logo3, logos[2].logopos.x, logos[2].logopos.y, SDL_FLIP_NONE, NULL);
	if (delay >= 3) App->render->Blit(logo2, logos[1].logopos.x, logos[1].logopos.y, SDL_FLIP_NONE, NULL);
	App->render->Blit(logo1, logos[0].logopos.x, logos[0].logopos.y, SDL_FLIP_NONE, NULL);
	App->render->Blit(sega, 150, 170, SDL_FLIP_NONE, NULL);

	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	App->render->Blit(light, 145, 114, SDL_FLIP_NONE, &rect);



	return Update_Status::UPDATE_CONTINUE;
}