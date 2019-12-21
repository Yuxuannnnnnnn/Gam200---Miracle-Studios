#pragma once
#ifndef _AUDIO_MANAGER_H
#define _AUDIO_MANAGER_H

#include <unordered_map>
#include "Components/AudioComponent.h"

#include "Interfaces/IManager.h"

class AudioManager final : public IManager
{
private:
	std::unordered_map< size_t, AudioComponent*> _audioList;

public:
	AudioManager() = default;
	virtual ~AudioManager() {}

	AudioManager(const AudioManager& rhs) = delete;
	AudioManager& operator= (const AudioManager& rhs) = delete;

	void AddObject(size_t uId, void* component = 0) { (void)uId; (void)component;};
	void RemoveObject(size_t uId) { (void)uId; };
};

#endif