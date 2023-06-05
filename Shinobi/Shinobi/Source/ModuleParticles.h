#ifndef __MODULE_PARTICLES_H__
#define __MODULE_PARTICLES_H__

#include "Module.h"

#include "Particle.h"
#include "Collider.h"

#define MAX_ACTIVE_PARTICLES 150

struct SDL_Texture;
struct Collider;

class ModuleParticles : public Module
{
public:
	// Constructor
	// Initializes all the particles in the array to nullptr
	ModuleParticles(bool startEnabled);

	//Destructor
	~ModuleParticles();

	// Called when the module is activated
	// Loads the necessary textures for the particles
	bool Start() override;

	// Called at the middle of the application loop
	// Iterates all the particles and calls its Update()
	// Removes any "dead" particles
	Update_Status Update() override;

	// Called at the end of the application loop
	// Iterates all the particles and draws them
	Update_Status PostUpdate() override;

	// Called on application exit
	// Destroys all active particles left in the array
	bool CleanUp() override;

	void OnCollision(Collider* c1, Collider* c2) override;

	// Creates a new particle and adds it to the array
	// Param particle	- A template particle from which the new particle will be created
	// Param x, y		- Position x,y in the screen (upper left axis)
	// Param delay		- Delay time from the moment the function is called until the particle is displayed in screen
	void AddParticle(const Particle& particle, int x, int y, Collider::Type colliderType = Collider::Type::NONE, uint delay = 0);

	// An array to store and handle all the particles
	Particle* particles[MAX_ACTIVE_PARTICLES] = { nullptr };

private:
	// Particles spritesheet loaded into an SDL Texture
	SDL_Texture* texture = nullptr;

	// An index to the last added particle
	uint lastParticle = 0;

public:
	//Template particle for an shuriken
	Particle shuriken;
	Particle patada;
	Particle enemyshot;
	Particle hit;
	Particle bonus500;
	Particle pow;
	Particle hitPow;
	Particle powgun;
	Particle ultimate, ultimate2;
	Particle ultimateEffect, ultimateEffect2;
	Particle ultiCenterUp, 
			ultiUpRight, 
			ultiUpRight2, 
			ultiRight, 
			ultiDownRight, 
			ultiCenterDown, 
			ultiDownLeft, 
			ultiLeft, 
			ultiUpLeft, 
			ultiUpLeft2,
			ultiDownLeft2,
			ultiDownRight2;
	Particle ultiWind;
	Particle fireBoss[8];
	Particle espada;


};

#endif // !__MODULEPARTICLES_H__