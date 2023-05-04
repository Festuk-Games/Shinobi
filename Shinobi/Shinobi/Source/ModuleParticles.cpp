#include "ModuleParticles.h"

#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles(bool startEnabled) : Module(startEnabled)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		particles[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{

}

bool ModuleParticles::Start()
{
	LOG("Loading particles");
	texture = App->textures->Load("Assets/bullets.png");

	// shuriken particle
	shuriken.anim.PushBack({ 287, 15, 16, 13 });
	shuriken.anim.PushBack({ 302, 15, 16, 13 });
	shuriken.anim.PushBack({ 317, 15, 16, 13 });
	shuriken.speed = iPoint(5, 0);
	shuriken.anim.loop = true;
	shuriken.anim.speed = 0.2f;

	hit.anim.PushBack({ 202, 12, 24, 18 });
	hit.anim.PushBack({ 225, 12, 24, 18 });
	hit.anim.PushBack({ 248, 12, 24, 18 });
	hit.anim.loop = false;
	hit.anim.speed = 0.3f;

	enemyshot.anim.PushBack({ 162, 15, 16, 11 });
	enemyshot.anim.PushBack({ 177, 15, 16, 11 });
	enemyshot.anim.loop = true;
	enemyshot.anim.speed = 0.3f;

	bonus500.anim.PushBack({ 110, 98, 39, 18 });
	bonus500.anim.PushBack({ 0, 0, 0, 0 });
	bonus500.anim.loop = false;
	bonus500.anim.speed = 0.04f;

	return true;
}

bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");

	// Delete all remaining active particles on application exit 
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (particles[i] != nullptr)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}
	return true;
}

Update_Status ModuleParticles::Update()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if (particle == nullptr)	continue;

		// Call particle Update. If it has reached its lifetime, destroy it
		if (particle->Update() == false)
		{
			delete particle;
			particles[i] = nullptr;
		}

	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleParticles::PostUpdate()
{
	//Iterating all particle array and drawing any active particles
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if (particle != nullptr && particle->isAlive)
		{
			App->render->Blit(texture, particle->position.x, particle->position.y, SDL_FLIP_NONE, &(particle->anim.GetCurrentFrame()));
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, Collider::Type colliderType, uint delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		//Finding an empty slot for a new particle
		if (particles[i] == nullptr)
		{
			Particle* p = new Particle(particle);

			p->frameCount = -(int)delay;			// We start the frameCount as the negative delay
			p->position.x = x;						// so when frameCount reaches 0 the particle will be activated
			p->position.y = y;

			//Adding the particle's collider
			
			if (colliderType == Collider::Type::ENEMY_SHOT) {
				p->collider = App->collisions->AddCollider({ 0,0,1,1 }, colliderType, this);
			}
			else if (colliderType != Collider::Type::NONE)
				p->collider = App->collisions->AddCollider(p->anim.GetCurrentFrame(), colliderType, this);

			
			particles[i] = p;
			break;
		}
	}
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (particles[i] != nullptr && particles[i]->collider == c1)
		{
			AddParticle(hit, particles[i]->position.x, particles[i]->position.y);
			delete particles[i];
			particles[i] = nullptr;
			break;
		}
	}
}