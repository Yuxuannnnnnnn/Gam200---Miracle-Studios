#pragma once
#include "PrecompiledHeaders.h"
#include "AudioComponent.h"



AudioComponent::AudioComponent() :
	_typeIdAudio{ (unsigned)TypeIdAudio::NONE },
	_fileName{ std::string() },
	_fileTrackLength{ 0 },
	_lifetimeCurrent{ 0 },
	_loop{ false },
	_lifetimeTotal{ 0 }
{
}



AudioComponent::AudioComponent(GameObject* parent, size_t uId, IComponentSystem* component)
	: IComponentSystem(parent, uId),
	_typeIdAudio{ (unsigned)TypeIdAudio::NONE },
	_fileName{ std::string() },
	_fileTrackLength{ 0 },
	_lifetimeCurrent{ 0 },
	_loop{ false },
	_lifetimeTotal{ 0 }
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

bool AudioComponent::IsBGM()
{
	return _isBGM;
}

void AudioComponent::SetIsBGM(bool isbgm)
{
	_isBGM = isbgm;
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

	if (document.HasMember("IsBGM") && document["IsBGM"].IsBool())
		_isBGM = document["IsBGM"].GetBool();

}

void AudioComponent::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{
	rapidjson::Value value;

	value.SetInt(_typeIdAudio);
	prototypeDoc.AddMember("A.TypeId", value);

	value.SetString(rapidjson::StringRef(_fileName.c_str()));
	prototypeDoc.AddMember("A.FileName", value);

	value.SetBool(_isBGM);
	prototypeDoc.AddMember("IsBGM", value);
}

void AudioComponent::Inspect()
{
	IComponentSystem::Inspect();
}
