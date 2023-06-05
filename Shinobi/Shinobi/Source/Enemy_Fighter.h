#ifndef __ENEMY_FIGHTER_H__
#define __ENEMY_FIGHTER_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Fighter : public Enemy
{
public:

	// Constructor (x y coordinates in the world)
	// Creates animation data and the collider
	Enemy_Fighter(int x, int y);

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
	Animation jumpAnim;

	bool changedirection = true;

	bool pl = false;
	int hitTimer = 0;
	int pos1 = 500, pos2 = 650;
	int pdistance = 200;
	int shot = 0;
	bool shooting = false, reloading = false, walking = true;
	int time = 0;

	int bullets = 3;
};

#endif // __ENEMY_FIGHTER_H__