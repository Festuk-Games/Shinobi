#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 20

class Module;
class ModuleWindow;
class ModuleAudio;
class ModuleInput;
class ModuleTextures;
class ModulePlayer;
class ModuleScene;
class ModuleParticles;
class ModuleRender;
class ModuleAuxScene;
class ModuleUI;
class ModuleHostage;
class ModuleCollisions;
class ModuleEnemies;
class ModuleFadeToBlack;
class SceneMission;
class SceneIntro;
class InitialScene;
class LogoScene;
class MissionNumScene;
class ModuleScene2;
class SceneRanking;

class Application
{

public:

	//Constructor. Creates all necessary modules for the application
	Application();

	//Destructor. Removes all module objects
	~Application();

	//Initializes all modules
	bool Init();

	//Updates all modules (PreUpdate, Update and PostUpdate)
	Update_Status Update();

	//Releases all the application data
	bool CleanUp();

public:
	// An array to store all modules
	Module* modules[NUM_MODULES];

	// All the modules stored individually
	ModuleWindow* window = nullptr;
	ModuleAudio* audio = nullptr;
	ModuleInput* input = nullptr;
	ModuleTextures* textures = nullptr;

	ModulePlayer* player = nullptr;
	ModuleScene* scene = nullptr;
	ModuleParticles* particles = nullptr;

	ModuleAuxScene* auxscene = nullptr;
	ModuleUI* ui = nullptr;
	ModuleRender* render = nullptr;
	ModuleCollisions* collisions = nullptr;

	ModuleEnemies* enemies = nullptr;

	ModuleHostage* hostage = nullptr;

	ModuleFadeToBlack* fade = nullptr;

	SceneMission* mission = nullptr;
	SceneIntro* intro = nullptr;

	InitialScene* initial = nullptr;
	LogoScene* logo = nullptr;
	MissionNumScene* missionNum = nullptr;

	ModuleScene2* scene2 = nullptr;

	SceneRanking* ranking = nullptr;
};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__