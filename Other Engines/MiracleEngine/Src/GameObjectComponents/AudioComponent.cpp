#pragma once
#include "PrecompiledHeaders.h"
#include "AudioComponent.h"



AudioComponent::AudioComponent(GameObject* parent, size_t uId, IComponentSystem* component)
	:	IComponentSystem(parent, uId),
	_typeIdAudio{ (unsigned)TypeIdAudio::NONE },
	_fileName { std::string() },
	_fileTrackLength{ 0 },
	_lifetimeCurrent{ 0 },
	_loop{ false }
{
	if (component)//Cloning Component
	{
		AudioComponent* audioComponent = dynamic_cast<AudioComponent*>(component);
		_typeIdAudio = audioComponent->_typeIdAudio;
		_fileName = audioComponent->_fileName;
		_fileTrackLength = audioComponent->_fileTrackLength;
		_lifetimeCurrent = audioComponent->_lifetimeCurrent;
		_loop = audioComponent->_loop;
	}
}

unsigned& AudioComponent::GetTypeId()
{
	return _typeIdAudio;
}

std::string& AudioComponent::GetFileName()
{
	return _fileName;
}

std::string AudioComponent::ComponentName() const
{
	return "Audio Component";
}

void AudioComponent::SerialiseComponent(Serialiser& document)
{
	if (document.HasMember("A.TypeId") && document["A.TypeId"].IsInt())
		_typeIdAudio = document["A.TypeId"].GetUint();

	if (document.HasMember("A.FileName") && document["A.FileName"].IsString())
		_fileName = std::string(document["A.FileName"].GetString());

}

void AudioComponent::Inspect()
{
}
