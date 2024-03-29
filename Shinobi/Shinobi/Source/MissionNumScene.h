#ifndef __MISSION_NUM_SCENE_H__
#define __MISSION_NUM_SCENE_H__

#include "Module.h"
#include "Animation.h"
#include "ModulePlayer.h"

struct SDL_Texture;

class MissionNumScene : public Module
{
public:
	//Constructor
	MissionNumScene(bool startEnabled);

	//Destructor
	~MissionNumScene();

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
	SDL_Texture* name = nullptr;
	SDL_Texture* mission = nullptr;

	SDL_Rect missionrect, missionrect2;
	int counter = 0;
	int changescene = 0;

	Animation missionAnim;
	Animation* currentAnim = nullptr;

	int writefx = 0;
	int aux = 10;
};

#endif 