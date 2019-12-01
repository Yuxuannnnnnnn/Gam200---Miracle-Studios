#include "PrecompiledHeaders.h"
#include "Sound.h"

Sound::Sound(const std::string& path, SoundType type)
	:
	_path{path},
	_type{type}
{
}

std::string& Sound::GetPath()
{
	return _path;
}

SoundType Sound::GetType()
{
	return _type;
}
