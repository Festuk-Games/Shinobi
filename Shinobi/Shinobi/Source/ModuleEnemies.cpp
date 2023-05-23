#include "ModuleEnemies.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"

#include "Enemy.h"
#include "Enemy_Gunner.h"
#include "Enemy_Fighter.h"
#include "Enemy_Soldier.h"
#include "Enemy_Purple.h"
#include "Enemy_green.h"
#include "Enemy_Boss.h"
using namespace std;

#include "ModuleScene.h"

#include "ModuleCollisions.h"
#include <iostream>

#define SPAWN_MARGIN 10000


ModuleEnemies::ModuleEnemies(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
	LOG("Loading enemies");

	ground.x = 0;
	ground.y = 0;
	ground.w = 2048;
	ground.h = 512;
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
	purple = App->textures->Load("Assets/purple.png");
	green = App->textures->Load("Assets/green.png");
	boss = App->textures->Load("Assets/boss.png");

	stageTextureL2 = App->textures->Load("Assets/Scenes/layer_aa.png");

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
	if (App->scene->IsEnabled())
	{
		App->render->Blit(stageTextureL2, 0, -(512 - SCREEN_HEIGHT), SDL_FLIP_NONE, &ground, 1.0f);
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
	App->textures->Unload(purple);
	App->textures->Unload(green);

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
				case ENEMY_TYPE::PURPLE:
					enemies[i] = new Enemy_Purple(info.x, info.y);
					enemies[i]->texture = purple;
					enemies[i]->destroyedFx = enemyDestroyedFx;
					break;
				case ENEMY_TYPE::GREEN:
					enemies[i] = new Enemy_green(info.x, info.y);
					enemies[i]->texture = green;
					enemies[i]->destroyedFx = enemyDestroyedFx;
					break;
				case ENEMY_TYPE::BOSS:
					enemies[i] = new Enemy_Boss(info.x, info.y);
					enemies[i]->texture = boss;
					enemies[i]->destroyedFx = enemyDestroyedFx;
					break;
			}
			break;
		}
	}
}

void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
		{
			if (c2->type == Collider::Type::PLAYER_SHOT)
			{
				enemies[i]->OnCollision(c2); //Notify the enemy of a collision
				c1->pendingToDelete = true;
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
				enemies[i]->jump = true;
				enemies[i]->position.y--;
			}
			if (c2->type == Collider::Type::WALL)
			{
				
				if (!enemies[i]->collision)
				{
					cout << "No hay colision" << endl;
					enemies[i]->isCollidingLeft = false;
					enemies[i]->isCollidingRight = false;
				}
				else if (enemies[i]->flip && enemies[i]->collision)
				{
					cout << "colision derecha" << endl;
					enemies[i]->isCollidingRight = true;
					enemies[i]->isCollidingLeft = false;
				}
				else
				{
					cout << "colision izq" << endl;
					enemies[i]->isCollidingLeft = true;
					enemies[i]->isCollidingRight = false;
				}

			}
		}
		if (enemies[i] != nullptr && enemies[i]->GetAttackCollider() == c1)
		{
			if (c2->type == Collider::Type::PLAYER) {

				enemies[i]->attackCol = true;
				enemies[i]->attack->rect.w = 0;
				enemies[i]->attack->rect.h = 0;
				enemies[i]->attack->SetPos(0, 0);
			}
		}
	}
}