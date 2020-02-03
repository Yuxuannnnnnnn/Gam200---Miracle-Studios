#include "PrecompiledHeaders.h"
#include "Sound.h"

Sound::Sound() :
	_sound{nullptr}
{
	//FMOD_System_CreateStream(_fmodSystem, "Resources\\Audio\\Level1.ogg", FMOD_LOOP_NORMAL | FMOD_2D, NULL, &_level1);
	//FMOD_System_CreateSound(_fmodSystem, currentSound, FMOD_LOOP_OFF | FMOD_2D, NULL, sound);

}

Sound::~Sound()
{
	FMOD_Sound_Release(_sound);
}


FMOD_SOUND* Sound::GetFSound()
{
	return _sound;
}

bool Sound::load(std::string path, int loop)
{
	 _engineSystems._audioSystem->_fmodSystem;

	if (loop)
		FMOD_System_CreateStream(_engineSystems._audioSystem->_fmodSystem, path.c_str(), FMOD_LOOP_NORMAL | FMOD_2D, NULL, &_sound);
	else
		FMOD_System_CreateSound(_engineSystems._audioSystem->_fmodSystem, path.c_str(), FMOD_LOOP_OFF | FMOD_2D, NULL, &_sound);

	if (_sound)
		return true;

	return false;
}

void Sound::unload()
{
	FMOD_Sound_Release(_sound);
}