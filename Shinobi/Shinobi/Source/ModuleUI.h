#ifndef __MODULE_UI_H__
#define __MODULE_UI_H__

#include "Module.h"
#include "Animation.h"

using namespace std;

struct SDL_Texture;

class ModuleUI : public Module
{
public:
	//Constructor
	ModuleUI(bool startEnabled);

	//Destructor
	~ModuleUI();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	Update_Status Update();

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	Update_Status PostUpdate();

public:

	SDL_Texture* hostage = nullptr;
	SDL_Texture* lifes = nullptr;
	SDL_Texture* skill1 = nullptr;
	SDL_Texture* skill2 = nullptr;
	SDL_Texture* skill3 = nullptr;
	SDL_Texture* nums = nullptr;
	SDL_Texture* text2 = nullptr;
	SDL_Texture* go = nullptr;


	bool sk1 = true;

	int timesec2 = 9;
	int timesec1 = 5;
	int timemin = 2;
	int timef2 = 0;
	int timef1 = 0;
	int timef3 = 0;

	int hostages = 3;

	int time1p = 0;
	bool blue = false;

	int lifenum = 2;

	SDL_Rect life, 
			savet, 
			host, 
			skill, 
			timer[10], 
			points, 
			sega, 
			coin, 
			t1987, 
			blue1p, 
			white1p, 
			bscore[10], 
			wscore[10], 
			rscore[10],
			h_score[10], 
			playerReady, 
			hi,
			gameoverRed,
			gameoverWhite,
			nextstage,
			clear,
			whitePts,
			redPts,
			specialBonus;

	int digit = 0;
	int bnDigit = 0;
	int xpos = 0;
	int scoreCounter = 0;

	int highScore = 0;

	int counter = 0;

	int losecounter = 0;
	bool lose = false;

	int nextCounter = 0, nextframe = 0;
	int goposx = 1900;
};

#endif