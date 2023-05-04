#ifndef __MODULE_AUDIO_H__
#define __MODULE_AUDIO_H__

#include "Module.h"
#include "SDL/include/SDL.h"
#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment(lib, "SDL_mixer/libx86/SDL2_mixer.lib")

#define DEFAULT_MUSIC_FADE_TIME 2.0f
#define MAX_FX 200

class ModuleAudio : public Module
{
public:

	ModuleAudio(bool startEnabled);
	~ModuleAudio();

	bool Init();

	bool CleanUp();


	// Play a music file
	bool PlayMusic(const char* path, float fade_time = DEFAULT_MUSIC_FADE_TIME);

	// Load a WAV in memory
	int LoadFx(const char* path);
	bool UnLoadFx(int id);

	// Play a previously loaded WAV
	bool PlayFx(unsigned int fx, int repeat = 0);

	bool isPlaying = false;

	unsigned int shuriken;
	unsigned int write;

private:

	Mix_Music* music = nullptr;
	Mix_Chunk* fx[MAX_FX];
	int			last_fx = 1;
};
#endif
