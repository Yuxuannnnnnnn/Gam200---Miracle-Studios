#pragma once
#include "IComponentSystem.h"


#ifndef AUDIOCOMPONENT_H
#define	AUDIOCOMPONENT_H

// For both audio componentand graphic component, serialize a string and a typeid
enum class TypeIdAudio {
	NONE = 0,

};

class AudioComponent : public IComponentSystem
{
private:
	unsigned _typeIdAudio;	//Serialised
	std::string _fileName;	//Serialised

	unsigned _fileTrackLength;
	size_t _lifetimeTotal;
	size_t _lifetimeCurrent;
	bool _loop;
public:
	AudioComponent(GameObject* parent, size_t uId, IComponentSystem* component = nullptr);

	std::string ComponentName() const override;
	void SerialiseComponent(Serialiser& document) override;
	void Inspect() override;

	~AudioComponent() = default;

	unsigned& GetTypeId();

	std::string& GetFileName();

};


#endif
