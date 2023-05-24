#include "ModuleUI.h"
#include <iostream>
#include <string>

using namespace std;

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleScene.h"
#include "ModuleScene2.h"

#include <fstream>

ModuleUI::ModuleUI(bool startEnabled) : Module(startEnabled)
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

	savet.x = 85;
	savet.y = 7;
	savet.h = 8;
	savet.w = 16;

	sega.x = 1;
	sega.y = 17;
	sega.h = 8;
	sega.w = 40;

	coin.x = 1;
	coin.y = 27;
	coin.h = 8;
	coin.w = 90;

	t1987.x = 1;
	t1987.y = 37;
	t1987.h = 8;
	t1987.w = 32;

	blue1p.x = 18;
	blue1p.y = 47;
	blue1p.h = 8;
	blue1p.w = 14;

	white1p.x = 1;
	white1p.y = 47;
	white1p.h = 8;
	white1p.w = 14;
	
	playerReady.x = 0;
	playerReady.y = 154;
	playerReady.h = 10;
	playerReady.w = 105;

	hi.x = 0;
	hi.y = 144;
	hi.h = 10;
	hi.w = 15;

	gameoverRed.x = 1;
	gameoverRed.y = 69;
	gameoverRed.h = 17;
	gameoverRed.w = 136;

	gameoverWhite.x = 1;
	gameoverWhite.y = 86;
	gameoverWhite.h = 17;
	gameoverWhite.w = 136;

	nextstage.x = 0;
	nextstage.y = 91;
	nextstage.h = 10;
	nextstage.w = 111;

	clear.x = 0;
	clear.y = 103;
	clear.h = 10;
	clear.w = 88;

	for	(int i = 0; i < 10; i++)
	{
		timer[i] = { 1 + 8* i, 1, 7, 14 };
	}

	points = { 81, 12, 3, 3 };

	for (int i = 0; i < 10; i++)
	{
		bscore[i] = {  1 + 8 * i, 81, 7, 8 };
	}

	for (int i = 0; i < 10; i++)
	{
		wscore[i] = { 1 + 8 * i, 60, 7, 8 };
	}

	for (int i = 0; i < 10; i++)
	{
		h_score[i] = { 1 + 8 * i, 71, 7, 8 };
	}

	scoreCounter = 0;
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
	/*skill1 = App->textures->Load("Assets/UI/skill1.png");
	skill2 = App->textures->Load("Assets/UI/skill2.png");
	skill3 = App->textures->Load("Assets/UI/skill3.png");*/
	nums = App->textures->Load("Assets/UI/nums.png");
	text2 = App->textures->Load("Assets/UI/text2.png");
	go = App->textures->Load("Assets/UI/go.png");


	timesec2 = 9;
	timesec1 = 5;
	timemin = 2;

	fstream file;
	file.open("score.txt", ios::in);
	file >> highScore;
	cout << highScore;
	file.close();

	nextCounter = 0;
	counter = 0;
	nextframe = 0;
	if (App->scene->IsEnabled())
	{
		App->scene->nextStage = false;
		App->scene->clear = false;
		if (lifenum >=2)
		{
			hostages = 4;
		}
		skill1 = App->textures->Load("Assets/UI/skill2.png");
	}
	else if (App->scene2->IsEnabled())
	{
		App->scene->nextStage = false;
		App->scene->clear = false;
		if (lifenum >= 2)
		{
			hostages = 3;
		}
		skill1 = App->textures->Load("Assets/UI/skill3.png");
	}
	App->scene->nextStage = false;
	return ret;
}

Update_Status ModuleUI::Update()
{

	if (timemin <= 0 && timesec1 <= 0 && timesec2 <= 0)  lose = true;

	//Timer one number every second
	timef2++;
	if (timef2 == 60)
	{
		timesec2--;
		timef2 = 0;
	}
	if (timemin <= 0 && timesec1 <= 0 && timesec2 <= 0)  timesec2 = 0;
	else if (timesec2 < 0) timesec2 = 9;
	

	timef1++;
	if (timef1 == 600)
	{
		timesec1--;
		timef1 = 0;
	}
	if (timemin <= 0 && timesec1 <= 0)  timesec1 = 0;
	else if (timesec1 < 0) timesec1 = 5;


	timef3++;
	if (timef3 == 600*6)
	{
		timemin--;
		timef3 = 0;
	}
	if (timemin < 0) timemin = 0;

	time1p++;
	if (time1p == 40)
	{
		if (blue) blue = false;
		else blue = true;
		time1p = 0;
	}

	if (hostages == 0)
	{
		App->scene->nextStage = true;

	}

	if (scoreCounter > highScore)
	{
		highScore = scoreCounter;
		fstream file;
		file.open("score.txt", ios::out);
		file.seekp(0);
		file << highScore;
		file.close();
	}

	if (counter <= 80) counter++;

	if (lose && losecounter <= 8) losecounter++;
	else losecounter = 0;

	if (App->scene->nextStage && nextCounter <= 80) nextCounter++;
	if (App->scene->nextStage && nextframe <= 10) nextframe++;
	else nextframe = 0;

	if (App->scene->nextStage)
	{
		if (goposx <= 1980) goposx++;
		else goposx = 1900;
	}

	return Update_Status::UPDATE_CONTINUE;
}


// Update: draw background
Update_Status ModuleUI::PostUpdate()
{
	
	//Draw the hostages
	for (int i = 0; i < hostages; i++)
	{
		App->render->Blit(hostage, 40 + 8 * i, 205, SDL_FLIP_NONE, &host, 0.0f);
	}

	//Draw the lifes
	for (int i = 0; i < lifenum; i++)
	{
		App->render->Blit(lifes, 22 + 8 * i, 19, SDL_FLIP_NONE, &life, 0.0f);
	}

	//Draw the skills icons
	if (sk1) App->render->Blit(skill1, 246, 210, SDL_FLIP_NONE, &skill, 0.0f);
	

	if (!App->scene->nextStage)
	{
		App->render->Blit(nums, 24, 205, SDL_FLIP_NONE, &savet, 0.0f);
	}
	
	//App->render->Blit(nums, 286, 200, SDL_FLIP_NONE, &timer[timemin], 0.0f);
	//App->render->Blit(nums, 295, 203, SDL_FLIP_NONE, &points, 0.0f);
	//App->render->Blit(nums, 295, 208, SDL_FLIP_NONE, &points, 0.0f);
	//App->render->Blit(nums, 300, 200, SDL_FLIP_NONE, &timer[timesec1], 0.0f);
	//App->render->Blit(nums, 308, 200, SDL_FLIP_NONE, &timer[timesec2], 0.0f);

	App->render->Blit(nums, 266, 210, SDL_FLIP_NONE, &timer[timemin], 0.0f);
	App->render->Blit(nums, 275, 213, SDL_FLIP_NONE, &points, 0.0f);
	App->render->Blit(nums, 275, 218, SDL_FLIP_NONE, &points, 0.0f);
	App->render->Blit(nums, 280, 210, SDL_FLIP_NONE, &timer[timesec1], 0.0f);
	App->render->Blit(nums, 288, 210, SDL_FLIP_NONE, &timer[timesec2], 0.0f);
	
	if (blue) App->render->Blit(nums, 16, 10, SDL_FLIP_NONE, &blue1p, 0.0f);
	else App->render->Blit(nums, 16, 10, SDL_FLIP_NONE, &white1p, 0.0f);
	

	string sc = to_string(scoreCounter);
	xpos = 97 - (sc.size() * 8);

	for (int i = 0; i < sc.size(); i++)
	{
		digit = sc[i] - '0';

		if (blue) App->render->Blit(nums, xpos + (i * 8), 10, SDL_FLIP_NONE, &bscore[digit], 0.0f);
		else App->render->Blit(nums, xpos + (i * 8), 10, SDL_FLIP_NONE, &wscore[digit], 0.0f);
	}

	string hscore = to_string(highScore);
	xpos = 190 - (hscore.size() * 8);

	for (int i = 0; i < hscore.size(); i++)
	{
		digit = hscore[i] - '0';

		App->render->Blit(nums, xpos + (i * 8), 10, SDL_FLIP_NONE, &h_score[digit], 0.0f);
	}

	App->render->Blit(nums, 126, 9, SDL_FLIP_NONE, &hi, 0.0f);

	if (counter <= 80)
	{
		App->render->Blit(nums, 110, 110, SDL_FLIP_NONE, &playerReady, 0.0f);
	}

	if (lose)
	{
		if (losecounter <=4) App->render->Blit(text2, 110, 110, SDL_FLIP_NONE, &gameoverRed, 0.0f);
		else App->render->Blit(text2, 110, 110, SDL_FLIP_NONE, &gameoverWhite, 0.0f);
	}

	if (App->scene->nextStage)
	{
		if (nextCounter <= 80)
		{
			if (nextframe <= 5) App->render->Blit(nums, 140, 60, SDL_FLIP_NONE, &nextstage, 0.0f);
		}
		App->render->Blit(go, goposx, 140, SDL_FLIP_NONE, NULL, 1.0f);
	}

	if (App->scene->clear)
	{
		App->render->Blit(nums, 140, 60, SDL_FLIP_NONE, &clear, 0.0f);
	}
	return Update_Status::UPDATE_CONTINUE;
}