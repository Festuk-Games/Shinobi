#ifndef __SCENE_INTRO_H__
#define __SCENE_INTRO_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;

class SceneIntro : public Module
{
public:
	//Constructor
	SceneIntro(bool startEnabled);

	//Destructor
	~SceneIntro();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	Update_Status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	Update_Status PostUpdate() override;

	bool CleanUp();

public:
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* introimage1 = nullptr;
	SDL_Texture* introimage2 = nullptr;
	SDL_Texture* introimage3 = nullptr;
	SDL_Texture* sega = nullptr;
	SDL_Texture* light = nullptr;
	SDL_Texture* text = nullptr;

	SDL_Rect segarect, nums;

	Animation* currentAnimation = nullptr;
	Animation lightAnim;

	struct logos
	{
		SDL_Texture* logo = nullptr;
		int centerX = 141;
		int centerY = 16;
		float radius = 150.0f;
		float angularVelocity = 0.2f;
		float angularStep = 0.05f;
		float posX = centerX + radius;
		float posY = centerY;
		float time = 0.0f;
		iPoint logopos;
	}logos[6];

	bool intro1 = true, intro2 = false, intro3 = false;
	
	int delay = 0;
};

#endif