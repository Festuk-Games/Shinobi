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
struct Collider;

class ModuleHostage : public Module
{
public:

	ModuleHostage(bool startEnabled);

	~ModuleHostage();


	bool Start() override;

	Update_Status Update() override;

	Update_Status PostUpdate() override;

public:

	int speed = 1;

	SDL_Texture* texture = nullptr;

	struct hostages
	{
		Animation* currentAnimation = nullptr;
		Animation idleAnim, exitAnim;
		iPoint hostageposition;
		bool col = false;
		Collider* collider = nullptr;
		int time = 0;
	}h[2];

};


#endif // __ModuleHostage_H__
