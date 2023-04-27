#ifndef __INITIAL_SCENE_H__
#define __INITIAL_SCENE_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;

class InitialScene : public Module
{
public:
	//Constructor
	InitialScene(bool startEnabled);

	//Destructor
	~InitialScene();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	Update_Status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	Update_Status PostUpdate() override;

public:
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* logo = nullptr;

	SDL_Rect logorect;

	int delay = 0;
};

#endif