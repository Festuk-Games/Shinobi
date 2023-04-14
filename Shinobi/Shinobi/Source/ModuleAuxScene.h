#ifndef __MODULE_AUX_SCENE_H__
#define __MODULE_AUX_SCENE_H__

#include "Module.h"
#include "Animation.h"
#include "ModulePlayer.h"

struct SDL_Texture;

class ModuleAuxScene : public Module
{
public:
	//Constructor
	ModuleAuxScene();

	//Destructor
	~ModuleAuxScene();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	update_status Update();

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	update_status PostUpdate();

public:

	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* stageTexture = nullptr;
	SDL_Texture* stageTextureL2 = nullptr;
	SDL_Texture* skyTexture = nullptr;
	SDL_Texture* stageTexture2 = nullptr;
	SDL_Texture* skyTexture2 = nullptr;
	SDL_Texture* stageTexture3 = nullptr;
	SDL_Texture* skyTexture3 = nullptr;
	// The sprite rectangle for the ground
	SDL_Rect ground, sky;

	// The sprite section for the background
	SDL_Rect background;

	// The different sprite sections for the flag
	Animation flag;

	bool stage1 = true, stage1L2 = false, stage2 = false, stage3 = false;
	bool nextStage = true;

};

#endif