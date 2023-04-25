#include "ModuleFadeToBlack.h"

#include "Application.h"
#include "ModuleRender.h"

#include "SDL/include/SDL_render.h"

ModuleFadeToBlack::ModuleFadeToBlack(bool startEnabled) : Module(startEnabled)
{
	screenRect = {0, 0, SCREEN_WIDTH * SCREEN_SIZE, SCREEN_HEIGHT * SCREEN_SIZE};
}

ModuleFadeToBlack::~ModuleFadeToBlack()
{

}

bool ModuleFadeToBlack::Start()
{
	LOG("Preparing Fade Screen");

	fadeout[0].fade = App->textures->Load("Assets/fade/out/fadeout1.png");
	fadeout[1].fade = App->textures->Load("Assets/fade/out/fadeout2.png");
	fadeout[2].fade = App->textures->Load("Assets/fade/out/fadeout3.png");
	fadeout[3].fade = App->textures->Load("Assets/fade/out/fadeout4.png");
	fadeout[4].fade = App->textures->Load("Assets/fade/out/fadeout5.png");
	fadeout[5].fade = App->textures->Load("Assets/fade/out/fadeout6.png");
	fadeout[6].fade = App->textures->Load("Assets/fade/out/fadeout7.png");
	fadeout[7].fade = App->textures->Load("Assets/fade/out/fadeout8.png");
	fadeout[8].fade = App->textures->Load("Assets/fade/black.png");

	// Enable blending mode for transparency
	SDL_SetRenderDrawBlendMode(App->render->renderer, SDL_BLENDMODE_BLEND);
	return true;
}

Update_Status ModuleFadeToBlack::Update()
{
	// Exit this function if we are not performing a fade
	if (currentStep == Fade_Step::NONE) return Update_Status::UPDATE_CONTINUE;

	if (currentStep == Fade_Step::TO_BLACK)
	{
		++frameCount;
		if (frameCount >= maxFadeFrames)
		{
			moduleToDisable->Disable();
			moduleToEnable->Enable();
			currentStep = Fade_Step::FROM_BLACK;
		}
	}
	else
	{
		--frameCount;
		if (frameCount <= 0)
		{
			currentStep = Fade_Step::NONE;
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleFadeToBlack::PostUpdate()
{
	// Exit this function if we are not performing a fade
	if (currentStep == Fade_Step::NONE) return Update_Status::UPDATE_CONTINUE;

	float fadeRatio = (float)frameCount / (float)maxFadeFrames;

	// Render the black square with alpha on the screen
	SDL_SetRenderDrawColor(App->render->renderer, 0, 0, 0, (Uint8)(fadeRatio * 255.0f));
	SDL_RenderFillRect(App->render->renderer, &screenRect);

	if (currentStep == Fade_Step::TO_BLACK && fOut)
	{
		if (frameCount >= 5) App->render->Blit(fadeout[0].fade, 0, 0, SDL_FLIP_NONE, NULL);
		if (frameCount >= 10) App->render->Blit(fadeout[1].fade, 0, 0, SDL_FLIP_NONE, NULL);
		if (frameCount >= 15) App->render->Blit(fadeout[2].fade, 0, 0, SDL_FLIP_NONE, NULL);
		if (frameCount >= 20) App->render->Blit(fadeout[3].fade, 0, 0, SDL_FLIP_NONE, NULL);
		if (frameCount >= 25) App->render->Blit(fadeout[4].fade, 0, 0, SDL_FLIP_NONE, NULL);
		if (frameCount >= 30) App->render->Blit(fadeout[5].fade, 0, 0, SDL_FLIP_NONE, NULL);
		if (frameCount >= 35) App->render->Blit(fadeout[6].fade, 0, 0, SDL_FLIP_NONE, NULL);
		if (frameCount >= 40) App->render->Blit(fadeout[7].fade, 0, 0, SDL_FLIP_NONE, NULL);
	}
	else if (currentStep == Fade_Step::FROM_BLACK && fIn)
	{
		if (frameCount >= 40) App->render->Blit(fadeout[7].fade, 0, 0, SDL_FLIP_NONE, NULL);
		if (frameCount >= 35) App->render->Blit(fadeout[6].fade, 0, 0, SDL_FLIP_NONE, NULL);
		if (frameCount >= 30) App->render->Blit(fadeout[5].fade, 0, 0, SDL_FLIP_NONE, NULL);
		if (frameCount >= 25) App->render->Blit(fadeout[4].fade, 0, 0, SDL_FLIP_NONE, NULL);
		if (frameCount >= 20) App->render->Blit(fadeout[3].fade, 0, 0, SDL_FLIP_NONE, NULL);
		if (frameCount >= 15) App->render->Blit(fadeout[2].fade, 0, 0, SDL_FLIP_NONE, NULL);
		if (frameCount >= 10) App->render->Blit(fadeout[1].fade, 0, 0, SDL_FLIP_NONE, NULL);
		if (frameCount >= 5) App->render->Blit(fadeout[0].fade, 0, 0, SDL_FLIP_NONE, NULL);
	}

	return Update_Status::UPDATE_CONTINUE;
}

bool ModuleFadeToBlack::FadeToBlack(Module* moduleToDisable, Module* moduleToEnable, bool fadeOut, bool fadeIn, float frames)
{
	bool ret = false;

	// If we are already in a fade process, ignore this call
	if(currentStep == Fade_Step::NONE)
	{
		currentStep = Fade_Step::TO_BLACK;
		frameCount = 0;
		maxFadeFrames = frames;

		if (fadeOut) fOut = true;
		else fOut = false;

		if (fadeIn) fIn = true;
		else fIn = false;

		this->moduleToDisable = moduleToDisable;
		this->moduleToEnable = moduleToEnable;
		ret = true;
	}

	return ret;
}