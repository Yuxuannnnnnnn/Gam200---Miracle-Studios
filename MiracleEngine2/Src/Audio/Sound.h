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
	Sound(const std::string& path = "", SoundType type = BGM);
	~Sound();

	std::string& GetPath();
	SoundType GetType();

	FMOD_SOUND* GetFSound();

private:
	std::string _path;
	SoundType _type;

	FMOD_SOUND* _sound;
};