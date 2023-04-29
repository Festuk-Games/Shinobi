#include <iostream>
using namespace std;
#include "ModuleRender.h"

#include "Application.h"

#include "ModuleWindow.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModulePlayer.h"

#include "SDL/include/SDL_render.h"
#include "SDL/include/SDL_scancode.h"

#include "SceneIntro.h"

ModuleRender::ModuleRender(bool startEnabled) : Module(startEnabled)
{

}

ModuleRender::~ModuleRender()
{

}

bool ModuleRender::Init()
{
	LOG("Creating Renderer context");
	bool ret = true;	
	Uint32 flags = 0;

	if (VSYNC == true)
	{
		flags |= SDL_RENDERER_PRESENTVSYNC;
	}

	renderer = SDL_CreateRenderer(App->window->window, -1, flags);

	if (renderer == nullptr)
	{
		LOG("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

// Called every draw update
Update_Status ModuleRender::PreUpdate()
{
	//Set the color used for drawing operations
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	//Clear rendering target
	SDL_RenderClear(renderer);

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleRender::Update()
{
	//Handle positive vertical movement
	if (App->input->keys[SDL_SCANCODE_UP] == KEY_REPEAT)
		camera.y += cameraSpeed;

	//Handle negative vertical movement
	if (App->input->keys[SDL_SCANCODE_DOWN] == KEY_REPEAT)
		camera.y -= cameraSpeed;

	if (App->input->keys[SDL_SCANCODE_F2]== KEY_DOWN)
		posiciones = !posiciones;
	
	if (App->input->keys[SDL_SCANCODE_F3] == KEY_DOWN)
	{
		/*system("cls");
		cout << "logo.x: " << App->intro->logopos.x << endl;
		cout << "logo.y: " << App->intro->logopos.y << endl;*/
	}

	//Handle horizontal movement of the camera

	if (App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT)
	{	
		if (camera.x >= -4980)
		{
			if (App->player->position.x >= 180 && !App->player->isColliding)
			{
				camera.x -= cameraSpeed;
			}
		}
	}

	else if (App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT)
	{
		if (camera.x <= -1)
		{
			if (App->player->position.x <= 1840 && !App->player->isColliding)
			{
				camera.x += cameraSpeed;
			}
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleRender::PostUpdate()
{
	if (posiciones)
	{
		printPos();
	}
	//Update the screen
	SDL_RenderPresent(renderer);

	return Update_Status::UPDATE_CONTINUE;
}

void ModuleRender::printPos() {
	//cout << "Player.x: " << App->player->position.x << endl;
	cout << "Player.y: " << App->player->position.y << endl;
	//cout << "Camera.x: " << camera.x << endl;

}

bool ModuleRender::CleanUp()
{
	LOG("Destroying renderer");

	//Destroy the rendering context
	if (renderer != nullptr)
		SDL_DestroyRenderer(renderer);

	return true;
}

// Blit to screen
bool ModuleRender::Blit(SDL_Texture* texture, int x, int y, SDL_RendererFlip flip, SDL_Rect* section, float speed)
{
	bool ret = true;
	
	SDL_Rect rect {
		(int)(camera.x * speed) + x * SCREEN_SIZE,
		(int)(camera.y * speed) + y * SCREEN_SIZE,
		0, 0 };

	SDL_Point center = { rect.w / 2, rect.h / 2 };

	double angle = 0;
	
	if (section != nullptr)
	{
		rect.w = section->w;
		rect.h = section->h;
	}
	else
	{
		//Collect the texture size into rect.w and rect.h variables
		SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);
	}

	rect.w *= SCREEN_SIZE;
	rect.h *= SCREEN_SIZE;

	if (SDL_RenderCopyEx(renderer, texture, section, &rect, angle, &center, flip) != 0)
	{
		LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

bool ModuleRender::DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, float speed)
{
	bool ret = true;

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	SDL_Rect dstRect{
		(int)(-camera.x * speed) + rect.x * SCREEN_SIZE,
		(int)(-camera.y * speed) + rect.y * SCREEN_SIZE,
		rect.w * SCREEN_SIZE, rect.h * SCREEN_SIZE };

	if (SDL_RenderFillRect(renderer, &dstRect) != 0)
	{
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}