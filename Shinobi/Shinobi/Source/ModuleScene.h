#ifndef __MODULE_SCENE_H__
#define __MODULE_SCENE_H__

#include "Module.h"
#include "Animation.h"
#include "ModulePlayer.h"

struct SDL_Texture;

class ModuleScene : public Module
{
public:
	//Constructor
	ModuleScene(bool startEnabled);

	//Destructor
	~ModuleScene();

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
	
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* stageTexture = nullptr;
	SDL_Texture* stageTextureL2 = nullptr;
	SDL_Texture* skyTexture = nullptr;
	SDL_Texture* stageTexture2 = nullptr;
	SDL_Texture* skyTexture2 = nullptr;
	SDL_Texture* stageTexture3 = nullptr;
	SDL_Texture* skyTexture3 = nullptr;

	SDL_Texture* hostage = nullptr;

	// The sprite rectangle for the ground
	SDL_Rect ground, sky;

	// The sprite section for the background
	SDL_Rect background;

	// The different sprite sections for the flag
	Animation flag;

	bool stage1 = true, stage1L2 = false, stage2 = false, stage3 = false;
	bool nextStage = false;

	int losecounter = 0;

	bool clear = false;
	int clearcount = 0;

	bool hostages[4] = { false };

	bool ground2 = false;
	Collider* groundCol = nullptr;
	Collider* groundCol2 = nullptr;
};

#endif