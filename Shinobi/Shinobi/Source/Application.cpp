#include "Application.h"

#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleScene.h"
#include "ModuleAuxScene.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleUI.h"
#include "ModuleHostage.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModuleFadeToBlack.h"
#include "SceneMission.h"
#include "SceneIntro.h"
#include "InitialScene.h"
#include "LogoScene.h"
#include "MissionNumScene.h"
#include "ModuleScene2.h"
#include "SceneRanking.h"

Application::Application()
{
	// The order in which the modules are added is very important.
	// It will define the order in which Pre/Update/Post will be called
	// Render should always be last, as our last action should be updating the screen
	modules[0] = window = new ModuleWindow(true);
	modules[1] = input = new ModuleInput(true);
	modules[2] = textures = new ModuleTextures(true);

	modules[3] = ranking = new SceneRanking(true);
	//modules[3] = logo = new LogoScene(true);
	modules[4] = initial = new InitialScene(false);
	modules[5] = intro = new SceneIntro(false);
	modules[6] = missionNum = new MissionNumScene(false);
	modules[7] = mission = new SceneMission(false);

	modules[8] = scene = new ModuleScene(false);
	modules[9] = scene2 = new ModuleScene2(false);
	modules[10] = particles = new ModuleParticles(false);
	modules[11] = player = new ModulePlayer(false);
	modules[12] = hostage = new ModuleHostage(false);
	modules[13] = enemies = new ModuleEnemies(false);

	modules[14] = auxscene = new ModuleAuxScene(false);
	modules[15] = ui = new ModuleUI(false);
	modules[16] = collisions = new ModuleCollisions(false);
	modules[17] = fade = new ModuleFadeToBlack(true);
	modules[18] = render = new ModuleRender(true);
	modules[19] = audio = new ModuleAudio(true);

}

Application::~Application()
{
	for (int i = 0; i < NUM_MODULES; ++i)
	{
		//Important: when deleting a pointer, set it to nullptr afterwards
		//It allows us for null check in other parts of the code
		delete modules[i];
		modules[i] = nullptr;
	}
}


bool Application::Init()
{
	bool ret = true;

	// All modules (active and disabled) will be initialized
	for (int i = 0; i < NUM_MODULES && ret; ++i)
		ret = modules[i]->Init();

	// Only active modules will be 'started'
	for (int i = 0; i < NUM_MODULES && ret; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

Update_Status Application::Update()
{
	Update_Status ret = Update_Status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == Update_Status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : Update_Status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == Update_Status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : Update_Status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == Update_Status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : Update_Status::UPDATE_CONTINUE;

	SDL_Delay(16.666);

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for (int i = NUM_MODULES - 1; i >= 0 && ret; --i)
		ret = modules[i]->IsEnabled() ? modules[i]->CleanUp() : true;

	return ret;
}
