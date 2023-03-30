#ifndef __MODULE_SCENE_H__
#define __MODULE_SCENE_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class ModuleScene : public Module
{
public:
	//Constructor
	ModuleScene();

	//Destructor
	~ModuleScene();

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
	SDL_Texture* skyTexture = nullptr;
	SDL_Texture* stageTexture2 = nullptr;
	SDL_Texture* skyTexture2 = nullptr;
	SDL_Texture* stageTexture3 = nullptr;
	SDL_Texture* skyTexture3 = nullptr;
	// The sprite rectangle for the ground
	SDL_Rect ground , sky;

	// The sprite section for the background
	SDL_Rect background;

	// The different sprite sections for the flag
	Animation flag;

	bool stage1 = false, stage2 = false, stage3 = true;

};

#endif