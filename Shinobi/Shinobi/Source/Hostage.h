#ifndef __HOSTAGE_H__
#define __HOSTAGE_H__

#include "p2Point.h"
#include "Animation.h"

struct SDL_Texture;
struct Collider;

class Hostage
{
public:
	// Constructor
	// Saves the spawn position for later movement calculations
	Hostage(int x, int y);

	// Destructor
	virtual ~Hostage();

	// Returns the enemy's collider
	const Collider* GetCollider() const;

	// Called from inhering enemies' Udpate
	// Updates animation and collider position
	virtual void Update();

	// Called from ModuleEnemies' Update
	virtual void Draw();

	// Collision response
	// Triggers an animation and a sound fx
	virtual void OnCollision(Collider* collider);

public:
	// The current position in the world
	iPoint position;

	// The enemy's texture
	SDL_Texture* texture = nullptr;

	// Sound fx when destroyed
	int destroyedFx = 0;

	bool ground = false;

protected:

	Animation* currentAnimation = nullptr;
	Animation idleAnim, exitAnim;
	iPoint hostageposition;
	bool col = false;
	Collider* collider = nullptr;
	int time = 0;

	bool flip = true;
};

#endif // __HOSTAGE_H__

