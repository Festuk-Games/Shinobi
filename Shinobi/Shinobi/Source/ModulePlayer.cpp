#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"

#include "SDL/include/SDL_scancode.h"


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
	forwardAnim.loop = false;
	forwardAnim.speed = 0.1f;

	backwardAnim.PushBack({ 5, 112, 40 - 5, 172 - 112 });
	backwardAnim.PushBack({ 41, 112, 72 - 41, 172 - 112 });
	backwardAnim.PushBack({ 73, 112, 108 - 73, 172 - 112 });
	backwardAnim.PushBack({ 109, 112, 144 - 109, 172 - 112 });
	backwardAnim.PushBack({ 145, 112, 177 - 145, 172 - 112 });
	backwardAnim.PushBack({ 178, 112, 213 - 178, 172 - 112 });
	backwardAnim.loop = false;
	backwardAnim.speed = 0.1f;

	jumpAnim.PushBack({ 11, 410, 46 - 11, 470 - 410 });
	jumpAnim.PushBack({ 47, 384, 82 - 47, 470 - 384 });
	jumpAnim.PushBack({ 83, 410, 118 - 83, 470 - 410 });
	jumpAnim.loop = false;
	jumpAnim.speed = 0.08f;
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

	if(App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT)
	{
		currentAnimation = &forwardAnim;
		position.x += speed;
	}

	if (App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT)
	{
		currentAnimation = &backwardAnim;
		position.x -= speed;
	}

	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_REPEAT)
	{
		currentAnimation = &jumpAnim;
	}

	// Spawn explosion particles when pressing B
	if (App->input->keys[SDL_SCANCODE_B] == KEY_STATE::KEY_DOWN)
	{
		App->particles->AddParticle(App->particles->explosion, position.x, position.y + 25);
		App->particles->AddParticle(App->particles->explosion, position.x - 25, position.y, 30);
		App->particles->AddParticle(App->particles->explosion, position.x, position.y - 25, 60);
		App->particles->AddParticle(App->particles->explosion, position.x + 25, position.y, 90);
	}

	//Reset the currentAnimation back to idle before updating the logic
	if (App->input->keys[SDL_SCANCODE_D] == KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_A] == KEY_IDLE 
		&& App->input->keys[SDL_SCANCODE_SPACE] == KEY_IDLE)
		currentAnimation = &idleAnim;

	currentAnimation->Update();

	return update_status::UPDATE_CONTINUE;
}

update_status ModulePlayer::PostUpdate()
{
	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	App->render->Blit(texture, position.x, position.y - rect.h, &rect);

	return update_status::UPDATE_CONTINUE;
}