#include "PrecompiledHeaders.h"
#include "AudioSystem.h"

AudioSystem::AudioSystem()
{
	_fmodSystem = nullptr;
	_channel1 = nullptr;
	_channel2 = nullptr;
	_bgmGroup = nullptr;
	_sfxGroup = nullptr;
	FMOD_System_Create(&_fmodSystem);
	FMOD_System_Init(_fmodSystem, 32, FMOD_INIT_NORMAL, 0);


	FMOD_System_CreateChannelGroup(_fmodSystem, NULL, &_bgmGroup);
	FMOD_System_CreateChannelGroup(_fmodSystem, NULL, &_sfxGroup);
	
}

void AudioSystem::PlayBGM(const std::string& name, float volume)
{
	auto sound = MyResourceManager.GetLoopSoundResource(name);

	if (sound != nullptr)
	{
		FMOD_ChannelGroup_Stop(_bgmGroup);
		FMOD_System_PlaySound(_fmodSystem, sound->GetFSound(), _bgmGroup, 0, &_channel1);

		FMOD_Channel_SetVolume(_channel1, volume);
		//FMOD_Channel_SetLoopCount(_channel2, 3);
		FMOD_Channel_SetPaused(_channel1, false);
	}
}

void AudioSystem::PlaySFX(const std::string& name, float volume)
{
	auto sound = MyResourceManager.GetSoundResource(name);

	
	if(sound != nullptr)
		FMOD_System_PlaySound(_fmodSystem, sound->GetFSound(), _sfxGroup, false, &_channel2);

	FMOD_Channel_SetVolume(_channel2, volume);
	//FMOD_Channel_SetLoopCount(_channel2, 3);
	FMOD_Channel_SetPaused(_channel2, false);
}

AudioSystem::~AudioSystem()
{
}

void AudioSystem::Init()
{
	//_soundManager.AddSound(name, filepath, type(bgm/sfx));
}

void AudioSystem::Update()
{
	FMOD_System_Update(_fmodSystem);
}

void AudioSystem::Play(const std::string& name, bool isBGM)
{
	
	auto sound = MyResourceManager.GetSoundResource(name);

	if (isBGM)
	{
		FMOD_ChannelGroup_Stop(_bgmGroup);
		FMOD_System_PlaySound(_fmodSystem, sound->GetFSound(), _bgmGroup, 0, &_channel1);
	}
	else
	{
		FMOD_System_PlaySound(_fmodSystem, sound->GetFSound(), _sfxGroup, false, &_channel2);
	}

}

void AudioSystem::StopAllSound()
{
	FMOD_ChannelGroup_Stop(_bgmGroup);
	FMOD_ChannelGroup_Stop(_sfxGroup);
}


void AudioSystem::StopBGM()
{
	FMOD_ChannelGroup_Stop(_bgmGroup);
}

void AudioSystem::StopSFX()
{
	FMOD_ChannelGroup_Stop(_sfxGroup);
}