#ifndef __MODULE_HOSTAGE_H__
#define __MODULE_HOSTAGE_H__

#include "Module.h"

#define MAX_HOSTAGES 20

enum class HOSTAGE_TYPE
{
	NO_TYPE,
	HOSTAGE,
};

struct HostageSpawnpoint
{
	HOSTAGE_TYPE type = HOSTAGE_TYPE::NO_TYPE;
	int x, y;
};

class Hostage;
struct SDL_Texture;

class ModuleHostage : public Module
{
public:
	// Constructor
	ModuleHostage(bool startEnabled);

	// Destructor
	~ModuleHostage();

	// Called when the module is activated
	// Loads the necessary textures for the enemies
	bool Start() override;

	// Called at the middle of the application loop
	// Handles all enemies logic and spawning/despawning
	Update_Status Update() override;

	// Called at the end of the application loop
	// Iterates all the enemies and draws them
	Update_Status PostUpdate() override;

	// Called on application exit
	// Destroys all active enemies left in the array
	bool CleanUp() override;

	// Called when an enemi collider hits another collider
	// The hostage is destroyed and an explosion particle is fired
	void OnCollision(Collider* c1, Collider* c2) override;

	// Add an hostage into the queue to be spawned later
	bool AddHostage(HOSTAGE_TYPE type, int x, int y);

	// Iterates the queue and checks for camera position
	void HandleHostageSpawn();

	// Destroys any enemies that have moved outside the camera limits
	void HandleHostageDespawn();

	int powerup = 0;


private:
	// Spawns a new hostage using the data from the queue
	void SpawnHostage(const HostageSpawnpoint& info);

private:
	bool collision = true;
	// A queue with all spawn points information
	HostageSpawnpoint spawnQueue[MAX_HOSTAGES];

	// All spawned enemies in the scene
	Hostage* hostages[MAX_HOSTAGES] = { nullptr };

	// The enemies sprite sheet
	SDL_Texture* texture = nullptr;

	// The audio fx for destroying an hostage
	int hostageDestroyedFx = 0;
};

#endif // __MODULE_ENEMIES_H__