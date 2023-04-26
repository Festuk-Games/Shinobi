#ifndef __HOSTAGE_HOSTAGE_H__
#define __HOSTAGE_HOSTAGE_H__

#include "Hostage.h"
#include "Path.h"

class Hostage_Hostage : public Hostage
{
public:

	// Constructor (x y coordinates in the world)
	// Creates animation data and the collider
	Hostage_Hostage(int x, int y);

	// The enemy is going to perform a sinusoidal movement
	void Update() override;

private:
	// The position (as ratio) in the wave at a specific moment
	float waveRatio = 0.0f;

	// The speed at which the wave ratio is increased
	float waveRatioSpeed = 0.01f;

	// The original spawning position. The wave will be calculated from that
	int spawn_y = 0;

	// The total height of the wave
	int waveHeight = 50;

	Path path;

	bool changedirection = true;

	//Animation* currentAnimation = nullptr;
	//Animation idleAnim, exitAnim;
	//iPoint hostageposition;
	//bool col = false;
	//Collider* collider = nullptr;
	//int time = 0;
};

#endif // __HOSTAGE_HOSTAGE_H__