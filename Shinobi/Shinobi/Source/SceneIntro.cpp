#include "SceneIntro.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleScene.h"
#include "ModuleScene2.h"
#include "BossScene.h"
#include "ModuleUI.h"
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

	nums.x = 0;
	nums.y = 36;
	nums.h = 10;
	nums.w = 34;

	segarect.x = 0;
	segarect.y = 17;
	segarect.h = 10;
	segarect.w = 42;

	coin.x = 1;
	coin.y = 26;
	coin.w = 92;
	coin.h = 10;

	shinobi.x = 1;
	shinobi.y = 1;
	shinobi.w = 95;
	shinobi.h = 17;

	shinobi2.x = 1;
	shinobi2.y = 18;
	shinobi2.w = 95;
	shinobi2.h = 17;
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
	logos[0].logo = App->textures->Load("Assets/logo.png");
	logos[1].logo = App->textures->Load("Assets/logo2.png");
	logos[2].logo = App->textures->Load("Assets/logo3.png");
	logos[3].logo = App->textures->Load("Assets/logo4.png");
	logos[4].logo = App->textures->Load("Assets/logo5.png");
	logos[5].logo = App->textures->Load("Assets/logo6.png");
	sega = App->textures->Load("Assets/sega.png");
	light = App->textures->Load("Assets/light.png");
	text = App->textures->Load("Assets/ui/nums.png");
	text2 = App->textures->Load("Assets/ui/text2.png");
	/*App->audio->PlayMusic("Assets/Music/introTitle.ogg", 1.0f);*/

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->render->win = false;
	App->scene->nextStage = false;
	App->scene2->nextStage = false;
	App->sceneboss->nextStage = false;
	App->scene->clear = false;
	App->scene2->clear = false;
	App->sceneboss->clear = false;

	App->audio->isPlaying = false;
	Mix_HaltMusic();

	App->scene->hostages[0] = { false };
	App->scene->hostages[1] = { false };
	App->scene->hostages[2] = { false };
	App->scene->hostages[3] = { false };

	App->scene2->hostages[0] = { false };
	App->scene2->hostages[1] = { false };
	App->scene2->hostages[2] = { false };

	App->ui->restart1 = true;
	App->ui->restart2 = true;

	App->ui->lifenum = 2;

	currentAnimation = &lightAnim;
	currentAnimation->Reset();

	delay = 0;
	counter = 0;
	scount = 0;

	for (int i = 0; i <= 5; i++)
	{
		logos[i].centerX = 121;
		logos[i].centerY = 14;
		logos[i].time = 0.0f;
		logos[i].radius = 150.0f;
		logos[i].angularStep = 0.05f;
		logos[i].angularVelocity = 0.2f;
		logos[i].logopos.x = 0;
		logos[i].logopos.y = 0;
	}

	return ret;
}

Update_Status SceneIntro::Update()
{
	GamePad& pad = App->input->pads[0];
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_DOWN|| pad.a_down)
	{
		App->audio->PlayFx(App->audio->coin);
		App->fade->FadeToBlack(this, (Module*)App->missionNum, true, false, 50);
	}

	delay++;

	for (int i = 0; i <= 5; i++)
	{
		if (logos[i].radius >= 0 && delay >= i*3)
		{
			logos[i].time += 4;
			logos[i].radius -= logos[i].angularVelocity * 4;
			logos[i].logopos.x = static_cast<int>(logos[i].centerX + logos[i].radius * sin(logos[i].angularStep * logos[i].time));

			logos[i].logopos.y = static_cast<int>(logos[i].centerY + logos[i].radius * cos(logos[i].angularStep * logos[i].time));

		}
	}

	if (delay >= 260) currentAnimation->Update();
	
	counter++;
	if (counter == 60) counter = 0;
	
	if (scount <= 8) scount++;
	else scount = 0;
	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneIntro::PostUpdate()
{
	// Draw everything --------------------------------------
	if (delay <= 80 || delay >= 200) App->render->Blit(introimage1, 0, 0, SDL_FLIP_NONE, NULL);
	else if (delay >= 80 && delay <= 140) App->render->Blit(introimage2, 0, 0, SDL_FLIP_NONE, NULL);
	else if (delay >= 140 && delay <= 200) App->render->Blit(introimage3, 0, 0, SDL_FLIP_NONE, NULL);

	for (int i = 5; i >= 0; i--)
	{
		if (delay >= i*3) App->render->Blit(logos[i].logo, logos[i].logopos.x, logos[i].logopos.y, SDL_FLIP_NONE, NULL);
	}
	
	App->render->Blit(sega, 128, 180, SDL_FLIP_NONE, NULL);

	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	App->render->Blit(light, 126, 114, SDL_FLIP_NONE, &rect);

	App->render->Blit(text, 232, 208, SDL_FLIP_NONE, &segarect);
	App->render->Blit(text, 280, 207, SDL_FLIP_NONE, &nums);
	if (counter <= 30) App->render->Blit(text, 122, 144, SDL_FLIP_NONE, &coin);

	if (scount <= 4) App->render->Blit(text2, 120, 64, SDL_FLIP_NONE, &shinobi);
	else App->render->Blit(text2, 120, 64, SDL_FLIP_NONE, &shinobi2);

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneIntro::CleanUp()
{
	App->textures->Unload(introimage1);
	App->textures->Unload(introimage2);
	App->textures->Unload(introimage3);
	for (int i = 0; i < 6; i++)
	{
		App->textures->Unload(logos[i].logo);
	}
	App->textures->Unload(sega);
	App->textures->Unload(light);
	App->textures->Unload(text);
	App->textures->Unload(text2);
	return true;
}