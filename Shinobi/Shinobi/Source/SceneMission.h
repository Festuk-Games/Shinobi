#ifndef __SCENE_MISSION_H__
#define __SCENE_MISSION_H__

#include "Module.h"
#include "Animation.h"
#include "ModulePlayer.h"

struct SDL_Texture;

class SceneMission : public Module
{
public:
	//Constructor
	SceneMission(bool startEnabled);

	//Destructor
	~SceneMission();

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

	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* mission1_0 = nullptr;
	SDL_Texture* mission1_1 = nullptr;

	// The sprite rectangle for the ground
	SDL_Rect ground;

	// The different sprite sections for the flag
	Animation flag;

	bool stage1 = true, stage1L2 = false, stage2 = false, stage3 = false;
	bool nextStage = true;

	int timer = 0;
	bool s1 = true;
	int changescene = 0;

	int imageX = -50, imageY = 224;

};

#endif 