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
	_soundMap[name] = new Sound{ path, type };
}
