#include <iostream>
using namespace std;
#include "ModuleRender.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleWindow.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL_render.h"
#include "SDL/include/SDL_scancode.h"

#include "SceneIntro.h"
#include "ModuleScene.h"
#include "ModuleScene2.h"
#include "BossScene.h"
#include "ModuleUI.h"
#include "ModuleCollisions.h"

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

	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH*3, SCREEN_HEIGHT*3);

	menu = App->textures->Load("Assets/menu_intro_shinobi.png");
	menuPlayer = App->textures->Load("Assets/menu_game_shinobi.png");
	menuEnemies = App->textures->Load("Assets/menu_enemy_shinobi.png");

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
	GamePad& pad = App->input->pads[0];
	////Handle positive vertical movement
	//if (App->input->keys[SDL_SCANCODE_UP] == KEY_REPEAT)
	//	camera.y += cameraSpeed;

	////Handle negative vertical movement
	//if (App->input->keys[SDL_SCANCODE_DOWN] == KEY_REPEAT)
	//	camera.y -= cameraSpeed;

	//menu intro
	if (App->input->keys[SDL_SCANCODE_F1] == KEY_DOWN && App->intro->IsEnabled() && openMenu)
	{
		openMenu = false;
	}
	else if (App->input->keys[SDL_SCANCODE_F1] == KEY_DOWN && App->intro->IsEnabled() && !openMenu)
	{
		openMenu = true;
	}
	if (App->input->keys[SDL_SCANCODE_F2] == KEY_DOWN && App->intro->IsEnabled()&& openMenu) {

		App->fade->FadeToBlack((Module*)App->intro, (Module*)App->mission, true, false, 50);

		//posiciones = !posiciones;
	}
	if (App->input->keys[SDL_SCANCODE_F3] == KEY_DOWN && App->intro->IsEnabled() && openMenu)
	{
		App->fade->FadeToBlack((Module*)App->intro, (Module*)App->mission2, true, false, 50);
	}

	if (App->input->keys[SDL_SCANCODE_F4] == KEY_DOWN && App->intro->IsEnabled() && openMenu)
	{
		App->fade->FadeToBlack((Module*)App->intro, (Module*)App->missionBoss, true, false, 50);
	}

	//menu player

	if (App->input->keys[SDL_SCANCODE_F1] == KEY_DOWN && (App->scene->IsEnabled() || App->scene2->IsEnabled() || App->sceneboss->IsEnabled()) && openMenu2)
	{
		openMenu2 = false;
	}
	else if (App->input->keys[SDL_SCANCODE_F1] == KEY_DOWN && (App->scene->IsEnabled() || App->scene2->IsEnabled()|| App->sceneboss->IsEnabled()) && !openMenu2)
	{
		openMenu2 = true;
	}
	if (App->input->keys[SDL_SCANCODE_F2] == KEY_DOWN && (App->scene->IsEnabled() || App->scene2->IsEnabled() || App->sceneboss->IsEnabled()) && openMenu2)
	{
		showColliders = !showColliders;
	}
	if (App->input->keys[SDL_SCANCODE_F4] == KEY_DOWN && (App->scene->IsEnabled() || App->scene2->IsEnabled() || App->sceneboss->IsEnabled()) && openMenu2)
	{
		App->player->isPowerUp = !App->player->isPowerUp;
	}

	if (App->input->keys[SDL_SCANCODE_F5] == KEY_DOWN && App->scene->IsEnabled() && openMenu2)
	{
		App->scene->nextStage = true;
		win = true;
	}
	else if (App->input->keys[SDL_SCANCODE_F5] == KEY_DOWN && App->scene2->IsEnabled() && openMenu2)
	{
		App->scene2->nextStage = true;
		win = true;
	}
	else if (App->input->keys[SDL_SCANCODE_F5] == KEY_DOWN && App->sceneboss->IsEnabled() && openMenu2)
	{
		App->sceneboss->nextStage = true;
		win = true;
	}

	if (App->input->keys[SDL_SCANCODE_F6] == KEY_DOWN && (App->scene->IsEnabled() || App->scene2->IsEnabled() || App->sceneboss->IsEnabled()) && openMenu2)
	{
		App->ui->lose = true;
	}
	if (App->input->keys[SDL_SCANCODE_F7] == KEY_DOWN && (App->scene->IsEnabled() || App->scene2->IsEnabled() || App->sceneboss->IsEnabled()) && openMenu2)
	{
		openMenu2 = false;
		openMenu3 = true;
	}

	// Menu enemigos

	if (App->input->keys[SDL_SCANCODE_F1] == KEY_DOWN && (App->scene->IsEnabled() || App->scene2->IsEnabled() || App->sceneboss->IsEnabled()) && openMenu3)
	{
		openMenu3 = false;
		openMenu2 = true;
		control = false;
	}
	if (App->input->keys[SDL_SCANCODE_F2] == KEY_DOWN && (App->scene->IsEnabled() || App->scene2->IsEnabled() || App->sceneboss->IsEnabled()) && openMenu3)
	{
		App->enemies->AddEnemy(ENEMY_TYPE::FIGHTER, App->player->position.x + 200, 120);
	}
	if (App->input->keys[SDL_SCANCODE_F3] == KEY_DOWN && (App->scene->IsEnabled() || App->scene2->IsEnabled() || App->sceneboss->IsEnabled()) && openMenu3)
	{
		App->enemies->AddEnemy(ENEMY_TYPE::SOLDIER, App->player->position.x + 200, 120);
	}
	if (App->input->keys[SDL_SCANCODE_F4] == KEY_DOWN && (App->scene->IsEnabled() || App->scene2->IsEnabled() || App->sceneboss->IsEnabled()) && openMenu3)
	{
		App->enemies->AddEnemy(ENEMY_TYPE::GUNNER, App->player->position.x + 200, 120);
	}
	if (App->input->keys[SDL_SCANCODE_F5] == KEY_DOWN && (App->scene->IsEnabled() || App->scene2->IsEnabled() || App->sceneboss->IsEnabled()) && openMenu3)
	{
		App->enemies->AddEnemy(ENEMY_TYPE::SITTGUNNER, App->player->position.x + 200, 120);
	}
	if (App->input->keys[SDL_SCANCODE_F6] == KEY_DOWN && (App->scene->IsEnabled() || App->scene2->IsEnabled() || App->sceneboss->IsEnabled()) && openMenu3)
	{
		App->enemies->AddEnemy(ENEMY_TYPE::PURPLE, App->player->position.x + 200, 120);
	}
	if (App->input->keys[SDL_SCANCODE_F7] == KEY_DOWN && (App->scene->IsEnabled() || App->scene2->IsEnabled() || App->sceneboss->IsEnabled()) && openMenu3 && control)
	{
		App->enemies->AddEnemy(ENEMY_TYPE::GREEN, App->player->position.x + 200, 120);
	}
	if (App->input->keys[SDL_SCANCODE_F8] == KEY_DOWN && (App->scene->IsEnabled() || App->scene2->IsEnabled() || App->sceneboss->IsEnabled()) && openMenu3)
	{
		App->enemies->AddEnemy(ENEMY_TYPE::SPIDERMAN, App->player->position.x + 200, 120);
	}

	

	//Handle horizontal movement of the camera

	if ((App->scene->IsEnabled() || App->scene2->IsEnabled() || App->sceneboss->IsEnabled())
		&& App->player->alive && (App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT||pad.l_x>0.2f) && App->input->keys[SDL_SCANCODE_A] == KEY_IDLE && !App->player->isJumpingUp2 && !App->player->isJumpingDown2)
	{	
		if (((App->scene->IsEnabled() || App->scene2->IsEnabled())  && camera.x >= -5182)
			|| (App->sceneboss->IsEnabled() && camera.x >= -570))
		{
			if (App->player->position.x >= 100 && !App->player->isCollidingRight)
			{
				camera.x -= cameraSpeed;
				colPos += 3;
			}
		}
	}

	else if ((App->scene->IsEnabled() || App->scene2->IsEnabled() || App->sceneboss->IsEnabled())
		&& App->player->alive && (App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT || pad.l_x <-0.2f) && App->input->keys[SDL_SCANCODE_D] == KEY_IDLE && !App->player->isJumpingUp2 && !App->player->isJumpingDown2)
	{
		if (camera.x <= -1)
		{
			if (App->player->position.x <= 1840 && !App->player->isCollidingLeft)
			{
				camera.x += cameraSpeed;
				colPos -= 3;
			}
		}
	}

	if (App->scene->IsEnabled() || App->sceneboss->IsEnabled())
	{
		cameracol->SetPos(colPos, 0);
		cameracol2->SetPos(319 + colPos, 0);
		cameracol3->SetPos(colPos, 223);
		cameracol4->SetPos(colPos, 0);
	}

	

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleRender::PostUpdate()
{
	if (showColliders)
	{
		App->collisions->DebugDraw();
	}
	if (posiciones)
	{
		printPos();
	}

	if ((App->scene->IsEnabled() || App->scene2->IsEnabled()|| App->sceneboss->IsEnabled()) && openMenu2)
	{
		Blit(menuPlayer, 5, 5, SDL_FLIP_NONE, NULL,0.0f);
		openMenu2 = true;
	}
	if ((App->scene->IsEnabled() || App->scene2->IsEnabled() || App->sceneboss->IsEnabled()) && !openMenu2 && openMenu3)
	{
		Blit(menuEnemies, 5, 5, SDL_FLIP_NONE, NULL, 0.0f);
		openMenu3 = true;
		control = true;
	}
	if (App->intro->IsEnabled() && openMenu) {
		Blit(menu, 5, 5, SDL_FLIP_NONE, NULL);
		openMenu = true;
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