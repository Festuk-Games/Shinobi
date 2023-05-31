#ifndef __ENEMY_BOSS_H__
#define __ENEMY_BOSS_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Boss : public Enemy
{
public:

	// Constructor (x y coordinates in the world)
	// Creates animation data and the collider
	Enemy_Boss(int x, int y);

	// The enemy is going to perform a sinusoidal movement
	void Update() override;

private:

	// The original spawning position. The wave will be calculated from that
	int spawn_y = 0;

	// The total height of the wave
	int waveHeight = 50;

	Path path;

	// The enemy animation

	Animation idleAnim;
	Animation headAnim;
	Animation legsAnim;
	Animation attackAnim1;
	Animation hitAnim;
	Animation dieAnim;



	bool changedirection = true;

	bool pl = false;

	int pos1 = 500, pos2 = 650;
	int pdistance = 200;
	int shot = 0;
	bool shooting = false, reloading = false, walking = true;
	int time = 0;

	struct particle1
	{
		bool alive = false;
		int particle;
		int centerX = 0;
		int centerY = 100;
		float radius = 40.0f;
		float angularVelocity = 0.16f;
		float angularStep = 0.012f;
		float time = 0.0f;
		bool left = true;
	}particle1[8];

	struct particle2
	{
		bool alive = false;
		int particle;
		int centerX = 0;
		int centerY = 140;
		float radius = 40.0f;
		float angularVelocity = 0.16f;
		float angularStep = 0.012f;
		float time = 0.0f;
		bool left = true;
	}particle2[8];

	bool isShooting = false;

	int delay = 0;

	int count = 1;
};

#endif // __ENEMY_BOSS_H__