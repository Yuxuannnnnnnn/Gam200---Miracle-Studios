#pragma once
#include "PrecompiledHeaders.h"
#include "AudioComponent.h"



AudioComponent::AudioComponent() :
	_typeIdAudio{ TypeIdAudio::NONE },
	_fileName { std::string() },
	_fileTrackLength{ 0 },
	_lifetimeCurrent{ 0 },
	_loop{ false }
{
}

AudioComponent::~AudioComponent()
{
}

std::string AudioComponent::ComponentName() const
{
	return "Audio Component";
}