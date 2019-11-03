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



void AudioSystem::Play()
{
	//FMOD_System_CreateStream(_fmodSystem, "Level1.ogg", FMOD_LOOP_NORMAL | FMOD_2D, NULL, &_level1);
	//FMOD_System_PlaySound(_fmodSystem, _level1, channelGroup, 0, &_channel1);
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
	Play();

}

AudioSystem::~AudioSystem()
{
}

void AudioSystem::PlayBGM()
{
}

void AudioSystem::PlaySFX()
{
}