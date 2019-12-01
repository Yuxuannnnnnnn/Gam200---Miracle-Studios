#pragma once

#include <string>
#include "../Dep/fmod/inc/fmod.h"

enum SoundType
{
	BGM,
	SFX
};

class Sound
{
public:
	Sound();
	~Sound();

	std::string& GetPath();
	SoundType GetType();

	FMOD_SOUND* GetFSound();

	bool load(std::string path, int loop);
	void unload();

private:
	std::string _path;
	SoundType _type;

	FMOD_SOUND* _sound;
};