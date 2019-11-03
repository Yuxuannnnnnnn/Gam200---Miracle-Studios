#include "PrecompiledHeaders.h"
#include "SoundManager.h"

std::map<std::string, Sound>& SoundManager::GetSoundMap()
{
	return _soundMap;
}

void SoundManager::AddSound(std::string& name, std::string& path, SoundType type)
{
	_soundMap[name] = Sound{ path, type };
}
