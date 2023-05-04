#include "ModuleHostage.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "Hostage.h"
#include "ModuleCollisions.h"
#include "Hostage_Hostage.h"
#include "ModuleInput.h"

#define SPAWN_MARGIN 10000

ModuleHostage::ModuleHostage(bool startEnabled) : Module(startEnabled)
{
	for (uint i = 0; i < MAX_HOSTAGES; ++i)
		hostages[i] = nullptr;
	LOG("Loading hostages");
}

ModuleHostage::~ModuleHostage()
{

}

bool ModuleHostage::Start()
{
	LOG("Loading hostages");
	texture = App->textures->Load("Assets/hostage.png");
	powerup = 0;
	return true;
}

Update_Status ModuleHostage::Update()
{
	HandleHostageSpawn();

	for (uint i = 0; i < MAX_HOSTAGES; ++i)
	{
		if (hostages[i] != nullptr)
			hostages[i]->Update();
	}
	if (App->input->keys[SDL_SCANCODE_F3] == KEY_DOWN)
	{
		collision = !collision;
	}

	HandleHostageDespawn();

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleHostage::PostUpdate()
{
	for (uint i = 0; i < MAX_HOSTAGES; ++i)
	{
		if (hostages[i] != nullptr)
			hostages[i]->Draw();
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleHostage::CleanUp()
{
	LOG("Freeing all hostages");

	for (uint i = 0; i < MAX_HOSTAGES; ++i)
	{
		if (hostages[i] != nullptr)
		{
			delete hostages[i];
			hostages[i] = nullptr;
		}
	}

	return true;
}

bool ModuleHostage::AddHostage(HOSTAGE_TYPE type, int x, int y)
{
	bool ret = false;

	for (uint i = 0; i < MAX_HOSTAGES; ++i)
	{
		if (spawnQueue[i].type == HOSTAGE_TYPE::NO_TYPE)
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

void ModuleHostage::HandleHostageSpawn()
{
	// Iterate all the hostages queue
	for (uint i = 0; i < MAX_HOSTAGES; ++i)
	{
		if (spawnQueue[i].type != HOSTAGE_TYPE::NO_TYPE)
		{
			// Spawn a new hostage if the screen has reached a spawn position
			if (spawnQueue[i].x * SCREEN_SIZE < App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN)
			{
				LOG("Spawning hostage at %d", spawnQueue[i].x * SCREEN_SIZE);

				SpawnHostage(spawnQueue[i]);
				spawnQueue[i].type = HOSTAGE_TYPE::NO_TYPE; // Removing the newly spawned hostage from the queue
			}
		}
	}
}

void ModuleHostage::HandleHostageDespawn()
{
	// Iterate existing hostages
	for (uint i = 0; i < MAX_HOSTAGES; ++i)
	{
		if (hostages[i] != nullptr)
		{
			// Delete the hostage when it has reached the end of the screen
			if (hostages[i]->position.x * SCREEN_SIZE < (App->render->camera.x) - SPAWN_MARGIN)
			{
				LOG("DeSpawning hostage at %d", hostages[i]->position.x * SCREEN_SIZE);

				delete hostages[i];
				hostages[i] = nullptr;
			}
		}
	}
}

void ModuleHostage::SpawnHostage(const HostageSpawnpoint& info)
{
	// Find an empty slot in the hostages array
	for (uint i = 0; i < MAX_HOSTAGES; ++i)
	{
		if (hostages[i] == nullptr)
		{
			switch (info.type)
			{
			case HOSTAGE_TYPE::HOSTAGE:
				hostages[i] = new Hostage_Hostage(info.x, info.y);
				break;
			}
			hostages[i]->texture = texture;
			hostages[i]->destroyedFx = hostageDestroyedFx;
			break;
		}
	}
}

void ModuleHostage::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_HOSTAGES; ++i)
	{
		if (hostages[i] != nullptr && hostages[i]->GetCollider() == c1)
		{
			if (c2->type == Collider::Type::PLAYER)
			{
				if (collision)
				{
					hostages[i]->OnCollision(c2); //Notify the hostage of a collision
					c1->pendingToDelete = true;
					break;
				}
				
			}
		}
	}
}