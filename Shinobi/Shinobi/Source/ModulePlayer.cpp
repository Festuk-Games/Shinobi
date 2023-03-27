#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"

#include "SDL/include/SDL_scancode.h"

// Street Fighter reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer()
{
	position.x = 100;
	position.y = 220;

	// idle animation (arcade sprite sheet)
	idleAnim.PushBack({13, 39, 48 - 13, 99 - 39 });

	// walk forward animation (arcade sprite sheet)
	forwardAnim.PushBack({5, 112, 40 - 5, 172 - 112});
	forwardAnim.PushBack({ 41, 112, 72 - 41, 172 - 112 });
	forwardAnim.PushBack({ 73, 112, 108 - 73, 172 - 112 });
	forwardAnim.PushBack({ 109, 112, 144 - 109, 172 - 112 });
	forwardAnim.PushBack({ 145, 112, 177 - 145, 172 - 112 });
	forwardAnim.PushBack({ 178, 112, 213 - 178, 172 - 112 });
	forwardAnim.speed = 0.1f;

	// TODO 4: Make ryu walk backwards with the correct animations
	backwardAnim.PushBack({ 5, 112, 40 - 5, 172 - 112 });
	backwardAnim.PushBack({ 41, 112, 72 - 41, 172 - 112 });
	backwardAnim.PushBack({ 73, 112, 108 - 73, 172 - 112 });
	backwardAnim.PushBack({ 109, 112, 144 - 109, 172 - 112 });
	backwardAnim.PushBack({ 145, 112, 177 - 145, 172 - 112 });
	backwardAnim.PushBack({ 178, 112, 213 - 178, 172 - 112 });
	backwardAnim.speed = 0.1f;
}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Assets/main.png"); // arcade version

	return ret;
}

update_status ModulePlayer::Update()
{
	//Reset the currentAnimation back to idle before updating the logic
	currentAnimation = &idleAnim;

	if(App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT)
	{
		currentAnimation = &forwardAnim;
		position.x += speed;
	}

	// TODO 4: Make ryu walk backwards with the correct animations
	if (App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT)
	{
		currentAnimation = &backwardAnim;
		position.x -= speed;
	}

	currentAnimation->Update();

	return update_status::UPDATE_CONTINUE;
}

update_status ModulePlayer::PostUpdate()
{
	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	App->render->Blit(texture, position.x, position.y - rect.h, &rect);

	return update_status::UPDATE_CONTINUE;
}