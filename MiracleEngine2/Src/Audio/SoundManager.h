#pragma once
#include <map>
#include "Sound.h"
class SoundManager
{
public:
	std::map<std::string, Sound>& GetSoundMap();
	void AddSound(std::string& name, std::string& path, SoundType type);
private:
	std::map<std::string, Sound> _soundMap;
};