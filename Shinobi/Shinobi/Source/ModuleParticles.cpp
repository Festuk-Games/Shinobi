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
	texture = App->textures->Load("Assets/bullets2.png");

	// shuriken particle
	shuriken.anim.PushBack({ 287, 15, 16, 13 });
	shuriken.anim.PushBack({ 302, 15, 16, 13 });
	shuriken.anim.PushBack({ 317, 15, 16, 13 });
	shuriken.speed = iPoint(5, 0);
	shuriken.anim.loop = true;
	shuriken.anim.speed = 0.2f;

	patada.anim.PushBack ({0, 0, 0, 0}) ;


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

	pow.anim.PushBack({ 1, 97, 50, 20 });
	pow.anim.PushBack({ 0, 0, 0, 0 });
	pow.anim.loop = false;
	pow.anim.speed = 0.04f;

	ultimate.anim.PushBack({ 6, 122, 38, 66 });
	ultimate.anim.PushBack({ 0, 0, 0, 0 });
	ultimate.anim.loop = false;
	ultimate.speed = iPoint(1, 0);
	ultimate.anim.speed = 0.02f;

	ultimate2.anim.PushBack({ 6, 122, 38, 66 });
	ultimate2.anim.PushBack({ 0, 0, 0, 0 });
	ultimate2.anim.loop = false;
	ultimate2.speed = iPoint(-1, 0);
	ultimate2.anim.speed = 0.02f;

	ulti.anim.PushBack({ 58, 122, 38, 66 });
	//ulti.anim.PushBack({ 0, 0, 0, 0 });
	ulti.anim.loop = true;
	ulti.speed = iPoint(0, -4);
	ulti.anim.speed = 0.01f;

	ulti2.anim.PushBack({ 108, 122, 45, 66 });
	/*ulti2.anim.PushBack({ 0, 0, 0, 0 });*/
	ulti2.anim.loop = true;
	ulti2.speed = iPoint(4, -4);
	ulti2.anim.speed = 0.01f;

	ulti3.anim.PushBack({ 165, 137, 59, 34 });
	//ulti3.anim.PushBack({ 0, 0, 0, 0 });
	ulti3.anim.loop = true;
	ulti3.speed = iPoint(4, 0);
	ulti3.anim.speed = 0.01f;

	ulti4.anim.PushBack({ 58, 122, 38, 66 });
	//ulti4.anim.PushBack({ 0, 0, 0, 0 });
	ulti4.anim.loop = true;
	ulti4.speed = iPoint(0, 4);
	ulti4.anim.speed = 0.01f;

	ulti5.anim.PushBack({ 108, 122, 45, 66 });
	//ulti5.anim.PushBack({ 0, 0, 0, 0 });
	ulti5.anim.loop = true;
	ulti5.speed = iPoint(-4, -4);
	ulti5.anim.speed = 0.01f;

	ulti6.anim.PushBack({ 165, 137, 59, 34 });
	//ulti6.anim.PushBack({ 0, 0, 0, 0 });
	ulti6.anim.loop = true;
	ulti6.speed = iPoint(-4, 0);
	ulti6.anim.speed = 0.01f;

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
		SDL_RendererFlip fliptype = SDL_FLIP_NONE;

		if (particle != nullptr && particle->isAlive && !particle->fliph && !particle->flipv)
		{
			App->render->Blit(texture, particle->position.x, particle->position.y, SDL_FLIP_NONE, &(particle->anim.GetCurrentFrame()));
		}
		else if (particle != nullptr && particle->isAlive && particle->fliph && !particle->flipv)
		{
			App->render->Blit(texture, particle->position.x, particle->position.y, SDL_FLIP_HORIZONTAL, &(particle->anim.GetCurrentFrame()));
		}
		else if (particle != nullptr && particle->isAlive && particle->flipv && !particle->fliph)
		{
			App->render->Blit(texture, particle->position.x, particle->position.y, SDL_FLIP_VERTICAL, &(particle->anim.GetCurrentFrame()));
		}
		else if (particle != nullptr && particle->isAlive && particle->flipv && particle->fliph)
		{
			fliptype = static_cast<SDL_RendererFlip>(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);

			App->render->Blit(texture, particle->position.x, particle->position.y, fliptype, &(particle->anim.GetCurrentFrame()));
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
				p->collider = App->collisions->AddCollider({ 0,0,5,5 }, colliderType, this);
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
		if (particles[i] != nullptr && particles[i]->collider == c1 && c2->type != Collider::Type::ULTIMATE)
		{
			AddParticle(hit, particles[i]->position.x, particles[i]->position.y);
			delete particles[i];
			particles[i] = nullptr;
			break;
		}
		else if (particles[i] != nullptr && particles[i]->collider == c1 && c1->type == Collider::Type::PLAYER_SHOT && c2->type == Collider::Type::ULTIMATE)
		{

			if (particles[i]->speed == iPoint(4, -4))
			{
				particles[i]->speed = iPoint(-4, -4);
				particles[i]->fliph = true;
			}
			else if (particles[i]->speed == iPoint(-4, -4))
			{
				particles[i]->speed = iPoint(-4, 4);
				particles[i]->flipv = true;
			}
			else if (particles[i]->speed == iPoint(-4, 4))
			{
				particles[i]->speed = iPoint(4, 4);
				particles[i]->fliph = false;
			}
			else if (particles[i]->speed == iPoint(4, 4))
			{
				particles[i]->speed = iPoint(4, -4);
				particles[i]->flipv = false;
			}

			else if (particles[i]->speed == iPoint(4, 0))
			{
				particles[i]->speed = iPoint(-4, 0);
				particles[i]->fliph = true;
			}
			else if (particles[i]->speed == iPoint(-4, 0))
			{
				particles[i]->speed = iPoint(4, 0);
				particles[i]->fliph = false;
			}

			else if (particles[i]->speed == iPoint(0, 4))
			{
				particles[i]->speed = iPoint(0, -4);
				particles[i]->flipv = false;
			}
			else if (particles[i]->speed == iPoint(0, -4))
			{
				particles[i]->speed = iPoint(0, 4);
				particles[i]->flipv = true;
			}
		}
	}
}