#pragma once

#include <string>

enum SoundType
{
	BGM,
	SFX
};

class Sound
{
public:
	Sound(const std::string& path = "", SoundType type = BGM);
	std::string& GetPath();
	SoundType GetType();
private:
	std::string _path;
	SoundType _type;
};