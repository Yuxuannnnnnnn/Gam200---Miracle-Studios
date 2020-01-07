#include "PrecompiledHeaders.h"
#include "SoundManager.h"

std::map<std::string, Sound*>& SoundManager::GetSoundMap()
{
	return _soundMap;
}

Sound* SoundManager::GetSound(std::string& name)
{
	return _soundMap[name];
}

void SoundManager::AddSound(std::string& name, std::string& path, SoundType type)
{
	if (MyResourceSystem.AddNewAudioResource({ name,path }))
	{
		_soundMap[name] = MyResourceSystem.GetSoundResource(name);
	}
}
