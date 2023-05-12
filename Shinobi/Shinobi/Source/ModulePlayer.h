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
	ModulePlayer(bool startEnabled);

	// Destructor
	~ModulePlayer();

	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start() override;

	// Called at the middle of the application loop
	// Processes new input and handles player movement
	Update_Status Update() override;

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	Update_Status PostUpdate() override;

	void OnCollision(Collider* c1, Collider* c2) override;

	bool CleanUp();

public:
	// Position of the player in the map
	iPoint position;

	// The speed in which we move the player (pixels per frame)
	int speed = 3;
	bool collision = true;

	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* texture = nullptr;
	
	Collider* katana = nullptr;
	Collider* collider = nullptr;
	Collider* feet = nullptr;
	Collider* enemyNearCollider = nullptr;

	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation = nullptr;

	// A set of animations
	Animation idleAnim;
	Animation walkAnim;
	Animation crouchIdleAnim, crouchAnim, crouchGunAnim;
	Animation jumpUpAnim, jumpDownAnim;
	Animation jumpUpFloorAnim, jumpDownFloorAnim;
	Animation shootAnim;
	Animation gunAnim;
	Animation dieAnim1, dieAnim2, dieAnim3;
	Animation backAnim;
	Animation crouchAttackAnim , crouchKickAnim, crouchKatanaAnim;
	Animation katanaAnim;
	Animation katanaJumpAnim;
	Animation attackJumpAnim1, attackJumpAnim2;
	Animation walkGunAnim;
	Animation idlePowAnim;
	Animation powAttackAnim;
	Animation crouchPowAttackAnim;
	Animation crouchGunIdleAnim;

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
	bool isPowerUp = false;

	bool isCollidingRight = false;
	bool isCollidingLeft = false;
	bool L2 = false;
	bool ground = false;

	bool right = true;
	//bool left = false;

	int dietime = 0;

	bool enemyNear = false;

	iPoint flipPos;

	int jumpAttackDelay = 0;

	bool canjump = true;
};

#endif //!__MODULE_PLAYER_H__