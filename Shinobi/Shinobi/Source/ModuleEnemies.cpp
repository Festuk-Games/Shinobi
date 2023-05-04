#include "ModuleEnemies.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"

#include "Enemy.h"
#include "Enemy_Gunner.h"
#include "Enemy_Fighter.h"
#include "Enemy_Soldier.h"

#include "ModuleCollisions.h"

#define SPAWN_MARGIN 1000


ModuleEnemies::ModuleEnemies(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
	LOG("Loading enemies");
}

ModuleEnemies::~ModuleEnemies()
{
	
}

bool ModuleEnemies::Start()
{
	LOG("Loading enemies");
	gunner = App->textures->Load("Assets/gun.png");
	fighter = App->textures->Load("Assets/fighter.png");
	soldier = App->textures->Load("Assets/soldier.png");
	return true;
}

Update_Status ModuleEnemies::Update()
{
	HandleEnemiesSpawn();

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr)
			enemies[i]->Update();
	}

	HandleEnemiesDespawn();

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleEnemies::PostUpdate()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
			enemies[i]->Draw();
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEnemies::CleanUp()
{
	LOG("Freeing all enemies");

	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	App->textures->Unload(gunner);
	App->textures->Unload(fighter);
	App->textures->Unload(soldier);

	return true;
}

bool ModuleEnemies::AddEnemy(ENEMY_TYPE type, int x, int y)
{
	bool ret = false;

	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(spawnQueue[i].type == ENEMY_TYPE::NO_TYPE)
		{
			spawnQueue[i].type = type;
			spawnQueue[i].x = x;
			spawnQueue[i].y = y;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModuleEnemies::HandleEnemiesSpawn()
{
	// Iterate all the enemies queue
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (spawnQueue[i].type != ENEMY_TYPE::NO_TYPE)
		{
			// Spawn a new enemy if the screen has reached a spawn position
			if (spawnQueue[i].x * SCREEN_SIZE < App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN)
			{
				LOG("Spawning enemy at %d", spawnQueue[i].x * SCREEN_SIZE);

				SpawnEnemy(spawnQueue[i]);
				spawnQueue[i].type = ENEMY_TYPE::NO_TYPE; // Removing the newly spawned enemy from the queue
			}
		}
	}
}

void ModuleEnemies::HandleEnemiesDespawn()
{
	// Iterate existing enemies
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			// Delete the enemy when it has reached the end of the screen
			if (enemies[i]->position.x * SCREEN_SIZE < (App->render->camera.x) - SPAWN_MARGIN)
			{
				LOG("DeSpawning enemy at %d", enemies[i]->position.x * SCREEN_SIZE);

				delete enemies[i];
				enemies[i] = nullptr;
			}
		}
	}
}

void ModuleEnemies::SpawnEnemy(const EnemySpawnpoint& info)
{
	// Find an empty slot in the enemies array
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] == nullptr)
		{
			switch (info.type)
			{
				case ENEMY_TYPE::GUNNER:
					enemies[i] = new Enemy_Gunner(info.x, info.y);
					enemies[i]->texture = gunner;
					enemies[i]->destroyedFx = enemyDestroyedFx;
					break;
				case ENEMY_TYPE::FIGHTER:
					enemies[i] = new Enemy_Fighter(info.x, info.y);
					enemies[i]->texture = fighter;
					enemies[i]->destroyedFx = enemyDestroyedFx;
					break;
				case ENEMY_TYPE::SOLDIER:
					enemies[i] = new Enemy_Soldier(info.x, info.y);
					enemies[i]->texture = soldier;
					enemies[i]->destroyedFx = enemyDestroyedFx;
					break;
			}
			break;
		}
	}
}

void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{
	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
		{
			if (c2->type == Collider::Type::PLAYER_SHOT)
			{
				enemies[i]->OnCollision(c2); //Notify the enemy of a collision

				//delete enemies[i];
				//enemies[i] = nullptr;
				break;
			}
			if (/*c1->type == Collider::Type::FEET && */c2->type == Collider::Type::GROUND)
			{
				enemies[i]->ground = true;
			}
			if (c2->type == Collider::Type::BOX)
			{
				enemies[i]->ground = true;
				enemies[i]->position.y--;
			}
		}
	}
}