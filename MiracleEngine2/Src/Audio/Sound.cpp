#include "PrecompiledHeaders.h"
#include "Sound.h"

Sound::Sound(const std::string& path, SoundType type)
	:
	_path{path},
	_type{type}
{
	//FMOD_System_CreateStream(_fmodSystem, "Resources\\Audio\\Level1.ogg", FMOD_LOOP_NORMAL | FMOD_2D, NULL, &_level1);
	//FMOD_System_CreateSound(_fmodSystem, currentSound, FMOD_LOOP_OFF | FMOD_2D, NULL, sound);

}

Sound::~Sound()
{
	FMOD_Sound_Release(_sound);
}

std::string& Sound::GetPath()
{
	return _path;
}

SoundType Sound::GetType()
{
	return _type;
}

FMOD_SOUND* Sound::GetFSound()
{
	return _sound;
}