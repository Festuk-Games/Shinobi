#ifndef __MODULE_UI_H__
#define __MODULE_UI_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class ModuleUI : public Module
{
public:
	//Constructor
	ModuleUI();

	//Destructor
	~ModuleUI();

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

	SDL_Texture* hostage = nullptr;
	SDL_Texture* lifes = nullptr;
	SDL_Texture* skill2 = nullptr;

	SDL_Rect life, host, skill;

};

#endif