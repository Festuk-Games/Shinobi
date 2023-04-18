#ifndef __MODULE_PLAYER_H__
#define __MODULE_PLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL/libx86/SDL2.lib")
#pragma comment( lib, "SDL/libx86/SDL2main.lib")

struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
public:
	// Constructor
	ModulePlayer();

	// Destructor
	~ModulePlayer();

	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start() override;

	// Called at the middle of the application loop
	// Processes new input and handles player movement
	update_status Update() override;

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	update_status PostUpdate() override;

	void OnCollision(Collider* c1, Collider* c2) override;

public:
	// Position of the player in the map
	iPoint position;

	// The speed in which we move the player (pixels per frame)
	int speed = 3;

	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* texture = nullptr;
	
	Collider* collider = nullptr;
	Collider* feet = nullptr;

	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation = nullptr;

	// A set of animations
	Animation idleAnim;
	Animation forwardAnim;
	Animation backwardAnim;
	Animation crouchAnim, crouchForwardAnim, crouchBackwardAnim;
	Animation jumpAnim1, jumpAnim2;
	Animation jumpUpAnim;
	Animation shootAnim;
	Animation gunAnim;
	Animation dieAnim1, dieAnim2, dieAnim3;
	Animation backAnim;
	Animation crouchAttackAnim , crouchKickAnim, crouchKatanaAnim;

	iPoint diePosition;
	iPoint jumpPosition;

	int kick = 0;
	bool diePos = false;
	bool dieState = false;
	bool jumpState = false;
	bool isJumping = false;
	bool isJumpingUp1 = false;
	bool isJumpingUp2 = false;
	bool isJumpingDown1 = false;
	bool isJumpingDown2 = false;
	bool isShooting = false;
	bool isKicking = false;
	bool isWalking = false;
	bool isCrouching = false;
	bool alive = true;

	bool isColliding = false;
	bool L2 = false;
	bool ground = false;

	bool right = false;
	bool left = false;

};

#endif //!__MODULE_PLAYER_H__