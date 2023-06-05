#ifndef __ENEMY_GREEN_H__
#define __ENEMY_GREEN_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_green : public Enemy
{
public:

	// Constructor (x y coordinates in the world)
	// Creates animation data and the collider
	Enemy_green(int x, int y);

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

	// The enemy animation
	Animation idleAnim;
	Animation walkAnim;
	Animation hitAnim;
	Animation dieAnim;
	Animation shootAnim;

	bool changedirection = true;

	bool pl = false;
	bool moving = false;
	int pos1 = 500, pos2 = 650;
	int pdistance = 200;
	int shot = 0;
	bool shooting = false, reloading = false, walking = true, idle = false;
	int time = 0;
	int bullets = 1;
};

#endif // __ENEMY_GREEN_H__