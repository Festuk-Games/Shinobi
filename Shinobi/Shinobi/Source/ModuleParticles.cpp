#include "ModuleParticles.h"

#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"
#include "BossScene.h"
#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles(bool startEnabled) : Module(startEnabled)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		particles[i] = nullptr;

	// shuriken particle
	shuriken.anim.PushBack({ 287, 15, 16, 13 });
	shuriken.anim.PushBack({ 302, 15, 16, 13 });
	shuriken.anim.PushBack({ 317, 15, 16, 13 });
	shuriken.speed = iPoint(5, 0);
	shuriken.anim.loop = true;
	shuriken.anim.speed = 0.2f;
	shuriken.lifetime = 80;

	powgun.anim.PushBack({ 362, 19, 13, 6 });
	powgun.anim.PushBack({ 345, 19, 13, 6 });
	powgun.anim.PushBack({ 383, 19, 13, 6 });
	powgun.anim.PushBack({ 345, 19, 13, 6 });
	powgun.speed = iPoint(5, 0);
	powgun.anim.loop = true;
	powgun.anim.speed = 0.2f;
	powgun.lifetime = 80;

	patada.anim.PushBack({ 0, 0, 0, 0 });


	hit.anim.PushBack({ 202, 12, 24, 18 });
	hit.anim.PushBack({ 225, 12, 24, 18 });
	hit.anim.PushBack({ 248, 12, 24, 18 });
	hit.anim.loop = false;
	hit.anim.speed = 0.3f;

	hitPow.anim.PushBack({ 1, 43, 51, 48 });
	hitPow.anim.PushBack({ 54, 43, 51, 48 });
	hitPow.anim.PushBack({ 104, 43, 51, 48 });
	hitPow.anim.PushBack({ 154, 43, 51, 48 });
	hitPow.anim.PushBack({ 204, 43, 51, 48 });
	hitPow.anim.PushBack({ 254, 43, 51, 48 });
	hitPow.anim.PushBack({ 304, 43, 51, 48 });
	hitPow.anim.PushBack({ 354, 43, 51, 48 });
	hitPow.anim.loop = false;
	hitPow.anim.speed = 0.5f;

	enemyshot.anim.PushBack({ 162, 15, 16, 11 });
	enemyshot.anim.PushBack({ 177, 15, 16, 11 });
	enemyshot.anim.loop = true;
	enemyshot.anim.speed = 0.3f;
	enemyshot.lifetime = 80;

	bonus500.anim.PushBack({ 110, 98, 39, 18 });
	bonus500.anim.PushBack({ 0, 0, 0, 0 });
	bonus500.anim.loop = false;
	bonus500.anim.speed = 0.04f;

	pow.anim.PushBack({ 1, 97, 50, 20 });
	pow.anim.PushBack({ 0, 0, 0, 0 });
	pow.anim.loop = false;
	pow.anim.speed = 0.04f;

	espada.anim.PushBack({ 0,6,51,28 });
	espada.anim.PushBack({ 50,6,51,28 });
	espada.anim.PushBack({ 100,6,51,28 });
	espada.anim.loop = true;
	espada.anim.speed = 0.3f;

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			ultimateEffect.anim.PushBack({ 62 * j,199 + 60 * i,63,61 });
		}
	}
	ultimateEffect.anim.loop = false;
	ultimateEffect.anim.speed = 1.0f;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 18; j++)
		{
			ultimateEffect2.anim.PushBack({ 7 + 39 * j,569 + 239 * i,40,209 });
		}
	}
	ultimateEffect2.anim.loop = false;
	ultimateEffect2.anim.speed = 0.3f;

	ultimate.anim.PushBack({ 4, 122, 46, 66 });
	ultimate.anim.PushBack({ 0, 0, 0, 0 });
	ultimate.fliph = false;
	ultimate.flipv = false;
	ultimate.anim.loop = false;
	ultimate.speed = iPoint(1, 0);
	ultimate.anim.speed = 0.06f;

	ultimate2.anim.PushBack({ 4, 122, 46, 66 });
	ultimate2.anim.PushBack({ 0, 0, 0, 0 });
	ultimate2.fliph = false;
	ultimate2.flipv = false;
	ultimate2.anim.loop = false;
	ultimate2.speed = iPoint(-1, 0);
	ultimate2.anim.speed = 0.06f;

	ultiCenterUp.anim.PushBack({ 58, 122, 38, 66 });
	ultiCenterUp.anim.PushBack({ 58, 122, 38, 66 });
	ultiCenterUp.anim.PushBack({ 0, 0, 0, 0 });
	ultiCenterUp.anim.loop = false;
	ultiCenterUp.speed = iPoint(0, -4);
	ultiCenterUp.anim.speed = 0.01f;

	ultiUpRight.anim.PushBack({ 108, 122, 45, 66 });
	ultiUpRight.anim.PushBack({ 108, 122, 45, 66 });
	ultiUpRight.anim.PushBack({ 0, 0, 0, 0 });
	ultiUpRight.anim.loop = false;
	ultiUpRight.speed = iPoint(4, -4);
	ultiUpRight.anim.speed = 0.01f;

	ultiRight.anim.PushBack({ 165, 137, 59, 34 });
	ultiRight.anim.PushBack({ 165, 137, 59, 34 });
	ultiRight.anim.PushBack({ 0, 0, 0, 0 });
	ultiRight.anim.loop = false;
	ultiRight.speed = iPoint(4, 0);
	ultiRight.anim.speed = 0.01f;

	ultiCenterDown.anim.PushBack({ 58, 122, 38, 66 });
	ultiCenterDown.anim.PushBack({ 58, 122, 38, 66 });
	ultiCenterDown.anim.PushBack({ 0, 0, 0, 0 });
	ultiCenterDown.flipv = true;
	ultiCenterDown.anim.loop = false;
	ultiCenterDown.speed = iPoint(0, 4);
	ultiCenterDown.anim.speed = 0.01f;

	ultiUpLeft.anim.PushBack({ 108, 122, 45, 66 });
	ultiUpLeft.anim.PushBack({ 108, 122, 45, 66 });
	ultiUpLeft.anim.PushBack({ 0, 0, 0, 0 });
	ultiUpLeft.fliph = true;
	ultiUpLeft.anim.loop = false;
	ultiUpLeft.speed = iPoint(-4, -4);
	ultiUpLeft.anim.speed = 0.01f;

	ultiLeft.anim.PushBack({ 165, 137, 59, 34 });
	ultiLeft.anim.PushBack({ 165, 137, 59, 34 });
	ultiLeft.anim.PushBack({ 0, 0, 0, 0 });
	ultiLeft.fliph = true;
	ultiLeft.anim.loop = false;
	ultiLeft.speed = iPoint(-4, 0);
	ultiLeft.anim.speed = 0.01f;

	ultiDownRight.anim.PushBack({ 108, 122, 45, 66 });
	ultiDownRight.anim.PushBack({ 108, 122, 45, 66 });
	ultiDownRight.anim.PushBack({ 0, 0, 0, 0 });
	ultiDownRight.flipv = true;
	ultiDownRight.anim.loop = false;
	ultiDownRight.speed = iPoint(4, 4);
	ultiDownRight.anim.speed = 0.01f;

	ultiDownLeft.anim.PushBack({ 108, 122, 45, 66 });
	ultiDownLeft.anim.PushBack({ 108, 122, 45, 66 });
	ultiDownLeft.anim.PushBack({ 0, 0, 0, 0 });
	ultiDownLeft.fliph = true;
	ultiDownLeft.flipv = true;
	ultiDownLeft.anim.loop = false;
	ultiDownLeft.speed = iPoint(-4, 4);
	ultiDownLeft.anim.speed = 0.01f;

	ultiDownRight2.anim.PushBack({ 108, 122, 45, 66 });
	ultiDownRight2.anim.PushBack({ 108, 122, 45, 66 });
	ultiDownRight2.anim.PushBack({ 0, 0, 0, 0 });
	ultiDownRight2.flipv = true;
	ultiDownRight2.anim.loop = false;
	ultiDownRight2.speed = iPoint(3, 4);
	ultiDownRight2.anim.speed = 0.01f;

	ultiDownLeft2.anim.PushBack({ 108, 122, 45, 66 });
	ultiDownLeft2.anim.PushBack({ 108, 122, 45, 66 });
	ultiDownLeft2.anim.PushBack({ 0, 0, 0, 0 });
	ultiDownLeft2.fliph = true;
	ultiDownLeft2.flipv = true;
	ultiDownLeft2.anim.loop = false;
	ultiDownLeft2.speed = iPoint(-3, 4);
	ultiDownLeft2.anim.speed = 0.01f;

	ultiUpRight2.anim.PushBack({ 108, 122, 45, 66 });
	ultiUpRight2.anim.PushBack({ 108, 122, 45, 66 });
	ultiUpRight2.anim.PushBack({ 0, 0, 0, 0 });
	ultiUpRight2.anim.loop = false;
	ultiUpRight2.speed = iPoint(3, -4);
	ultiUpRight2.anim.speed = 0.01f;

	ultiUpLeft2.anim.PushBack({ 108, 122, 45, 66 });
	ultiUpLeft2.anim.PushBack({ 108, 122, 45, 66 });
	ultiUpLeft2.anim.PushBack({ 0, 0, 0, 0 });
	ultiUpLeft2.fliph = true;
	ultiUpLeft2.anim.loop = false;
	ultiUpLeft2.speed = iPoint(-3, -4);
	ultiUpLeft2.anim.speed = 0.01f;

	ultiWind.anim.PushBack({ 15, 1042, 34, 12 });
	ultiWind.anim.PushBack({ 48, 1042, 34, 12 });
	ultiWind.anim.PushBack({ 81, 1042, 34, 12 });
	ultiWind.anim.PushBack({ 114, 1042, 34, 12 });
	ultiWind.fliph = false;
	ultiWind.anim.loop = true;
	ultiWind.speed = iPoint(6, 0);
	ultiWind.lifetime = 80;
	ultiWind.anim.speed = 0.1f;

	for (int i = 0; i <= 7; i++)
	{
		fireBoss[i].anim.PushBack({ 455 - i * 31, 141, 32, 27 });
		fireBoss[i].fliph = false;
		fireBoss[i].anim.loop = true;
		fireBoss[i].anim.speed = 0.1f;
	}
}

ModuleParticles::~ModuleParticles()
{

}

bool ModuleParticles::Start()
{
	LOG("Loading particles");
	texture = App->textures->Load("Assets/bullets2.png");

	


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
			

			if (colliderType != Collider::Type::NONE && colliderType != Collider::Type::ENEMY_SHOT)
			{
				p->collider = App->collisions->AddCollider(p->anim.GetCurrentFrame(), colliderType, this);

			}
			else if (colliderType == Collider::Type::ENEMY_SHOT)
			{
				p->collider = App->collisions->AddCollider({ 0,0,5,5 }, colliderType, this);
				if (App->sceneboss->IsEnabled())
				{
					App->enemies->GetParticle(i);
				}
			}

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
			if (c1->type == Collider::Type::PLAYER_SHOT && !App->player->isPowerUp)
			{
				AddParticle(hit, particles[i]->position.x, particles[i]->position.y);
			}
			else if (c1->type == Collider::Type::PLAYER_SHOT && App->player->isPowerUp)
			{
				AddParticle(hitPow, particles[i]->position.x-5, particles[i]->position.y - 14);
			}
			else AddParticle(hit, particles[i]->position.x, particles[i]->position.y);
			if (c1->type== Collider::Type::ENEMY_SHOT)
			{
				AddParticle(hit, particles[i]->position.x, particles[i]->position.y);
			}
			delete particles[i];
			particles[i] = nullptr;
			break;
		}
		else if (particles[i] != nullptr && particles[i]->collider == c1 && c1->type == Collider::Type::ULTI_SHOT && c2->type == Collider::Type::ULTIMATE)
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

			else if (particles[i]->speed == iPoint(3, -4))
			{
				particles[i]->speed = iPoint(3, 4);
				particles[i]->flipv = true;
			}
			else if (particles[i]->speed == iPoint(3, 4))
			{
				particles[i]->speed = iPoint(-3, 4);
				particles[i]->fliph = true;
			}
			else if (particles[i]->speed == iPoint(-3, 4))
			{
				particles[i]->speed = iPoint(-3, -4);
				particles[i]->flipv = false;
			}
			else if (particles[i]->speed == iPoint(-3, -4))
			{
				particles[i]->speed = iPoint(3, -4);
				particles[i]->fliph = false;
			}
		}
	}
}