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

AudioSystem::~AudioSystem()
{
}

void AudioSystem::Init()
{
	//_soundManager.AddSound(name, filepath, type(bgm/sfx));
}

void AudioSystem::Update()
{
	int a = 0;
	for (auto& e : _soundList)
	{
		int x = 0;
	}
	FMOD_System_Update(_fmodSystem);
}

void AudioSystem::Play(std::string& name)
{
	Sound* sound = _soundManager.GetSound(name);

	if (sound->GetType() == SoundType::BGM)
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

void AudioSystem::AddObject(size_t uId, void* component)
{
	_soundList.insert({ uId, (AudioComponent*)component });
}

void AudioSystem::RemoveObject(size_t uId)
{
	_soundList.erase(uId);
}