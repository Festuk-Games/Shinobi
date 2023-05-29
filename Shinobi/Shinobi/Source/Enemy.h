#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "p2Point.h"
#include "Animation.h"

struct SDL_Texture;
struct Collider;

class Enemy
{
public:
	// Constructor
	// Saves the spawn position for later movement calculations
	Enemy(int x, int y);

	// Destructor
	virtual ~Enemy();

	// Returns the enemy's collider
	const Collider* GetCollider() const;
	const Collider* GetAttackCollider() const;
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

	iPoint flipPos;

	// The enemy's texture
	SDL_Texture* texture = nullptr;

	// Sound fx when destroyed
	int destroyedFx = 0;

	bool ground = false;
	bool jump = false;
	bool flip = true;
	bool isBoss = false;
	bool collision = true;
	bool isCollidingRight = false;
	bool isCollidingLeft = false;
	bool attackCol = false;
	Collider* attack = nullptr;

	int currentParticle;

protected:
	// A ptr to the current animation
	Animation* currentAnim = nullptr;
	Animation* currentHeadAnim = nullptr;
	Animation* currentLegsAnim = nullptr;

	// The enemy's collider
	Collider* collider = nullptr;
	Collider* feet = nullptr;

	// Original spawn position. Stored for movement calculations
	iPoint spawnPos;

	
	bool die = false;
};

#endif // __ENEMY_H__