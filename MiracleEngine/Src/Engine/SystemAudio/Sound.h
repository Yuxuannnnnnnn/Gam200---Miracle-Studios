#pragma once

#include <string>
#include "../Dep/fmod/inc/fmod.h"

class Sound
{
public:
	Sound();
	~Sound();

	FMOD_SOUND* GetFSound();

	bool load(std::string path, int loop);
	void unload();

private:
	FMOD_SOUND* _sound;
};