#include "ModuleCollisions.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleInput.h"
#include "SDL/include/SDL_Scancode.h"
#include <iostream>
using namespace std;

ModuleCollisions::ModuleCollisions(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[Collider::Type::WALL][Collider::Type::WALL] = false;
	matrix[Collider::Type::WALL][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::WALL][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::WALL][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::WALL][Collider::Type::ENEMY_SHOT] = true;
	matrix[Collider::Type::WALL][Collider::Type::HOSTAGE] = false;
	matrix[Collider::Type::WALL][Collider::Type::BOX] = false;
	matrix[Collider::Type::WALL][Collider::Type::GROUND] = false;
	matrix[Collider::Type::WALL][Collider::Type::GROUND2] = false;
	matrix[Collider::Type::WALL][Collider::Type::FEET] = false;
	matrix[Collider::Type::WALL][Collider::Type::ENEMY_NEAR] = false;
	matrix[Collider::Type::WALL][Collider::Type::ULTIMATE] = false;
	matrix[Collider::Type::WALL][Collider::Type::ULTI_SHOT] = false;

	matrix[Collider::Type::PLAYER][Collider::Type::WALL] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMY_SHOT] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::GROUND] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::GROUND2] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::HOSTAGE] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::BOX] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::FEET] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMY_NEAR] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::ULTI_SHOT] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::ULTIMATE] = false;

	matrix[Collider::Type::ENEMY][Collider::Type::WALL] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::HOSTAGE] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::BOX] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::FEET] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::GROUND] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::GROUND2] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::ENEMY_NEAR] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::ULTI_SHOT] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::ULTIMATE] = false;

	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::WALL] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::HOSTAGE] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::BOX] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::GROUND] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::GROUND2] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::FEET] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::ENEMY_NEAR] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::ULTI_SHOT] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::ULTIMATE] = false;


	matrix[Collider::Type::ULTI_SHOT][Collider::Type::WALL] = false;
	matrix[Collider::Type::ULTI_SHOT][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::ULTI_SHOT][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::ULTI_SHOT][Collider::Type::ULTI_SHOT] = false;
	matrix[Collider::Type::ULTI_SHOT][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::ULTI_SHOT][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::ULTI_SHOT][Collider::Type::HOSTAGE] = false;
	matrix[Collider::Type::ULTI_SHOT][Collider::Type::BOX] = false;
	matrix[Collider::Type::ULTI_SHOT][Collider::Type::GROUND] = false;
	matrix[Collider::Type::ULTI_SHOT][Collider::Type::GROUND2] = false;
	matrix[Collider::Type::ULTI_SHOT][Collider::Type::FEET] = false;
	matrix[Collider::Type::ULTI_SHOT][Collider::Type::ENEMY_NEAR] = false;
	matrix[Collider::Type::ULTI_SHOT][Collider::Type::ULTIMATE] = true;
	
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::WALL] = true;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::HOSTAGE] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::BOX] = true;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::GROUND] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::GROUND2] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::FEET] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::ENEMY_NEAR] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::ULTIMATE] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::ULTI_SHOT] = false;

	matrix[Collider::Type::HOSTAGE][Collider::Type::WALL] = false;
	matrix[Collider::Type::HOSTAGE][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::HOSTAGE][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::HOSTAGE][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::HOSTAGE][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::HOSTAGE][Collider::Type::HOSTAGE] = false;
	matrix[Collider::Type::HOSTAGE][Collider::Type::BOX] = false;
	matrix[Collider::Type::HOSTAGE][Collider::Type::GROUND] = true;
	matrix[Collider::Type::HOSTAGE][Collider::Type::GROUND2] = true;
	matrix[Collider::Type::HOSTAGE][Collider::Type::FEET] = false;
	matrix[Collider::Type::HOSTAGE][Collider::Type::ENEMY_NEAR] = false;
	matrix[Collider::Type::HOSTAGE][Collider::Type::ULTIMATE] = false;
	matrix[Collider::Type::HOSTAGE][Collider::Type::ULTI_SHOT] = false;

	matrix[Collider::Type::BOX][Collider::Type::WALL] = false;
	matrix[Collider::Type::BOX][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::BOX][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::BOX][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::BOX][Collider::Type::ENEMY_SHOT] = true;
	matrix[Collider::Type::BOX][Collider::Type::HOSTAGE] = false;
	matrix[Collider::Type::BOX][Collider::Type::BOX] = true;
	matrix[Collider::Type::BOX][Collider::Type::GROUND] = true;
	matrix[Collider::Type::BOX][Collider::Type::GROUND2] = true;
	matrix[Collider::Type::BOX][Collider::Type::FEET] = true;
	matrix[Collider::Type::BOX][Collider::Type::ENEMY_NEAR] = false;
	matrix[Collider::Type::BOX][Collider::Type::ULTIMATE] = false;
	matrix[Collider::Type::BOX][Collider::Type::ULTI_SHOT] = false;

	matrix[Collider::Type::GROUND][Collider::Type::WALL] = false;
	matrix[Collider::Type::GROUND][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::GROUND][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::GROUND][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::GROUND][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::GROUND][Collider::Type::HOSTAGE] = true;
	matrix[Collider::Type::GROUND][Collider::Type::BOX] = true;
	matrix[Collider::Type::GROUND][Collider::Type::GROUND] = false;
	matrix[Collider::Type::GROUND][Collider::Type::GROUND2] = false;
	matrix[Collider::Type::GROUND][Collider::Type::FEET] = true;
	matrix[Collider::Type::GROUND][Collider::Type::ENEMY_NEAR] = false;
	matrix[Collider::Type::GROUND][Collider::Type::ULTIMATE] = false;
	matrix[Collider::Type::GROUND][Collider::Type::ULTI_SHOT] = false;

	matrix[Collider::Type::GROUND2][Collider::Type::WALL] = false;
	matrix[Collider::Type::GROUND2][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::GROUND2][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::GROUND2][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::GROUND2][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::GROUND2][Collider::Type::HOSTAGE] = true;
	matrix[Collider::Type::GROUND2][Collider::Type::BOX] = true;
	matrix[Collider::Type::GROUND2][Collider::Type::GROUND] = false;
	matrix[Collider::Type::GROUND2][Collider::Type::GROUND2] = false;
	matrix[Collider::Type::GROUND2][Collider::Type::FEET] = true;
	matrix[Collider::Type::GROUND2][Collider::Type::ENEMY_NEAR] = false;
	matrix[Collider::Type::GROUND2][Collider::Type::ULTIMATE] = false;
	matrix[Collider::Type::GROUND2][Collider::Type::ULTI_SHOT] = false;

	matrix[Collider::Type::FEET][Collider::Type::GROUND] = true;
	matrix[Collider::Type::FEET][Collider::Type::GROUND2] = true;
	matrix[Collider::Type::FEET][Collider::Type::WALL] = false;
	matrix[Collider::Type::FEET][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::FEET][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::FEET][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::FEET][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::FEET][Collider::Type::HOSTAGE] = false;
	matrix[Collider::Type::FEET][Collider::Type::BOX] = true;
	matrix[Collider::Type::FEET][Collider::Type::FEET] = false;
	matrix[Collider::Type::FEET][Collider::Type::ENEMY_NEAR] = false;
	matrix[Collider::Type::FEET][Collider::Type::ULTIMATE] = false;
	matrix[Collider::Type::FEET][Collider::Type::ULTI_SHOT] = false;

	matrix[Collider::Type::ENEMY_NEAR][Collider::Type::GROUND] = false;
	matrix[Collider::Type::ENEMY_NEAR][Collider::Type::GROUND2] = false;
	matrix[Collider::Type::ENEMY_NEAR][Collider::Type::WALL] = false;
	matrix[Collider::Type::ENEMY_NEAR][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::ENEMY_NEAR][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::ENEMY_NEAR][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::ENEMY_NEAR][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::ENEMY_NEAR][Collider::Type::HOSTAGE] = false;
	matrix[Collider::Type::ENEMY_NEAR][Collider::Type::BOX] = false;
	matrix[Collider::Type::ENEMY_NEAR][Collider::Type::FEET] = false;
	matrix[Collider::Type::ENEMY_NEAR][Collider::Type::ULTIMATE] = false;
	matrix[Collider::Type::ENEMY_NEAR][Collider::Type::ULTI_SHOT] = false;

	matrix[Collider::Type::ULTIMATE][Collider::Type::GROUND] = false;
	matrix[Collider::Type::ULTIMATE][Collider::Type::GROUND2] = false;
	matrix[Collider::Type::ULTIMATE][Collider::Type::WALL] = false;
	matrix[Collider::Type::ULTIMATE][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::ULTIMATE][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ULTIMATE][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::ULTIMATE][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::ULTIMATE][Collider::Type::HOSTAGE] = false;
	matrix[Collider::Type::ULTIMATE][Collider::Type::BOX] = false;
	matrix[Collider::Type::ULTIMATE][Collider::Type::ULTIMATE] = false;
	matrix[Collider::Type::ULTIMATE][Collider::Type::FEET] = false;
	matrix[Collider::Type::ULTIMATE][Collider::Type::ULTI_SHOT] = true;

	matrix[Collider::Type::ULTI_SHOT][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::ULTI_SHOT][Collider::Type::ULTIMATE] = true;
	matrix[Collider::Type::ULTI_SHOT][Collider::Type::GROUND] = false;
	matrix[Collider::Type::ULTI_SHOT][Collider::Type::GROUND2] = false;
	matrix[Collider::Type::ULTI_SHOT][Collider::Type::WALL] = false;
	matrix[Collider::Type::ULTI_SHOT][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::ULTI_SHOT][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::ULTI_SHOT][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::ULTI_SHOT][Collider::Type::HOSTAGE] = false;
	matrix[Collider::Type::ULTI_SHOT][Collider::Type::BOX] = false;
	matrix[Collider::Type::ULTI_SHOT][Collider::Type::FEET] = false;
	matrix[Collider::Type::ULTI_SHOT][Collider::Type::ULTI_SHOT] = false;

	

}

// Destructor
ModuleCollisions::~ModuleCollisions()
{

}

Update_Status ModuleCollisions::PreUpdate()
{
	/*int a = 0;*/
	// Remove all colliders scheduled for deletion
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] != nullptr && colliders[i]->pendingToDelete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
		/*if (colliders[i] != nullptr) a++;*/
	}
	//cout << "total: " << a << endl;
	//a = 0;

	Collider* c1;
	Collider* c2;

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if(colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		// avoid checking collisions already checked
		for(uint k = i+1; k < MAX_COLLIDERS; ++k)
		{
			// skip empty colliders
			if(colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if(c1->Intersects(c2->rect))
			{
				if(matrix[c1->type][c2->type] && c1->listener) 
					c1->listener->OnCollision(c1, c2);
				
				if(matrix[c2->type][c1->type] && c2->listener) 
					c2->listener->OnCollision(c2, c1);
			}
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleCollisions::Update()
{
	/*if (App->input->keys[SDL_SCANCODE_F1] == KEY_DOWN)
		debug = !debug;*/
	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleCollisions::PostUpdate()
{
	if (debug) {
		DebugDraw();
	}
	
	return Update_Status::UPDATE_CONTINUE;
}

void ModuleCollisions::DebugDraw()
{
	Uint8 alpha = 80;
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == nullptr)
			continue;
		
		switch(colliders[i]->type)
		{
			case Collider::Type::NONE: // white
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha, -1.0f);
			break;
			case Collider::Type::WALL: // blue
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha, -1.0f);
			break;
			case Collider::Type::PLAYER: // green
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha, -1.0f);
			break;
			case Collider::Type::ENEMY: // red
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha, -1.0f);
			break;
			case Collider::Type::PLAYER_SHOT: // yellow
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha, -1.0f);
			break;
			case Collider::Type::ENEMY_SHOT: // magenta
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha, -1.0f);
			break;
			case Collider::Type::HOSTAGE: // green
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha, -1.0f);
			break;
			case Collider::Type::BOX: // blue
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha, -1.0f);
			break;
			case Collider::Type::GROUND: // magenta
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha, -1.0f);
			break;
			case Collider::Type::GROUND2: // magenta
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha, -1.0f);
			break;
			case Collider::Type::FEET: // magenta
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha, -1.0f);
			break;
			case Collider::Type::ENEMY_NEAR: // white
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha, -1.0f);
			break;
			case Collider::Type::ULTIMATE: // green
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha, -1.0f);
			break;
		}
	}
}

// Called before quitting
bool ModuleCollisions::CleanUp()
{
	LOG("Freeing all colliders");

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* ModuleCollisions::AddCollider(SDL_Rect rect, Collider::Type type, Module* listener)
{
	Collider* ret = nullptr;

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, listener);
			break;
		}
	}

	return ret;
}
