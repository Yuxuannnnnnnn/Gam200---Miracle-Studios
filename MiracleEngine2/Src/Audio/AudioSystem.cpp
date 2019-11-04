#include "PrecompiledHeaders.h"
#include "AudioSystem.h"

void AudioSystem::Init()
{
	//_soundManager.AddSound(name, filepath, type(bgm/sfx));
}

void AudioSystem::Update()
{
	FMOD_System_Update(_fmodSystem);
}



void AudioSystem::Play(SoundEnum sound)
{
	PlaySFX(sound);
}

AudioSystem::AudioSystem()
{
	_fmodSystem = nullptr;
	_level1 = nullptr;
	_channel1 = nullptr;
	_bgmGroup = nullptr;
	_sfxGroup = nullptr;
	FMOD_System_Create(&_fmodSystem);
	FMOD_System_Init(_fmodSystem, 32, FMOD_INIT_NORMAL, 0);
	FMOD_System_CreateChannelGroup(_fmodSystem, NULL, &_bgmGroup);
	FMOD_System_CreateChannelGroup(_fmodSystem, NULL, &_sfxGroup);
	PlayBGM();
	PlaySFX(SHOOT);
}

AudioSystem::~AudioSystem()
{
}

void AudioSystem::PlayBGM()
{
	FMOD_System_CreateStream(_fmodSystem, "Resources\\Audio\\Level1.ogg", FMOD_LOOP_NORMAL | FMOD_2D, NULL, &_level1);
	FMOD_System_PlaySound(_fmodSystem, _level1, _bgmGroup, 0, &_channel1);
}

void AudioSystem::Sound_CreateOneShot(const char* filename, FMOD_SOUND** sound)
{
	char* currentSound; /*currently played sound*/
	currentSound = (char*)filename;
	if (possible && on) {
		if (*sound != NULL)
		{
			FMOD_Sound_Release(*sound);
		}
		FMOD_System_CreateSound(_fmodSystem, currentSound, FMOD_LOOP_OFF | FMOD_2D, NULL, sound);

	}
}

void AudioSystem::PlaySFX(SoundEnum sound)
{
	if (sound == SoundEnum::SHOOT)
	{
		Sound_CreateOneShot("Resources\\Audio\\Coin.ogg", &_shoot);
		FMOD_System_PlaySound(_fmodSystem, _shoot, _sfxGroup, false, &_channel2);
	}
	else if (sound == SoundEnum::ENEMYDEATH)
	{
		Sound_CreateOneShot("Resources\\Audio\\Button.ogg", &_enemydeath);
		FMOD_System_PlaySound(_fmodSystem, _enemydeath, _sfxGroup, false, &_channel2);
	}
}