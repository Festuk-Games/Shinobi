#ifndef __MODULE_HOSTAGE_H__
#define __MODULE_HOSTAGE_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL/libx86/SDL2.lib")
#pragma comment( lib, "SDL/libx86/SDL2main.lib")

class Hostage;
struct SDL_Texture;

class ModuleHostage : public Module
{
public:

	ModuleHostage();

	~ModuleHostage();


	bool Start() override;

	update_status Update() override;

	update_status PostUpdate() override;

public:

	int speed = 1;

	SDL_Texture* texture = nullptr;


	Animation* currentAnimation = nullptr;

	struct hostages
	{
		Animation idleAnim, exitAnim;
		iPoint hostageposition;
		bool col = false;
	}h[2];


};


#endif // __ModuleHostage_H__
