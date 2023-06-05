#ifndef __SCENE_RANKING_H__
#define __SCENE_RANKING_H__

#include "Module.h"
#include "Animation.h"
#include "ModulePlayer.h"

struct SDL_Texture;

class SceneRanking : public Module
{
public:
	//Constructor
	SceneRanking(bool startEnabled);

	//Destructor
	~SceneRanking();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	Update_Status Update();

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	Update_Status PostUpdate();

	bool CleanUp();

public:

	SDL_Texture* grey = nullptr;
	SDL_Texture* hab1 = nullptr;
	SDL_Texture* hab2 = nullptr;
	SDL_Texture* hab3 = nullptr;

	SDL_Rect score, hscore;
	SDL_Rect rscore[10], h_score[10];

	SDL_Texture* nums = nullptr;



	SDL_Rect missionrect, missionrect2;
	int counter = 0;
	int changescene = 0;
	int xpos = 0;
	int digit = 0;

	Animation missionAnim;
	Animation* currentAnim = nullptr;

};

#endif 