#pragma once
#include "PrecompiledHeaders.h"
#include "IComponentSystem.h"


// For both audio componentand graphic component, serialize a string and a typeid
enum class TypeIdAudio {
	NONE = 0,

};

class AudioComponent : public IComponentSystem
{
private:
	TypeIdAudio _typeIdAudio;
	std::string _fileName;

	unsigned _fileTrackLength;
	size_t _lifetimeTotal;
	size_t _lifetimeCurrent;
	bool _loop;
public:
	AudioComponent();
	~AudioComponent();

	std::string ComponentName() const override;
};

