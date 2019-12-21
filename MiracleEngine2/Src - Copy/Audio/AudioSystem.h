#pragma once

#ifndef AUDIOSYSTEM_H
#define AUDIOSYSTEM_H

#include "SoundManager.h"

#include "../Dep/fmod/inc/fmod.h"
#include "../Dep/fmod/inc/fmod_errors.h"
#include "../Dep/fmod/inc/fmod.hpp"
#include "../GameObjectComponents/AudioComponent.h"

#include "IContainer.h"

#include "SoundEnum.h"

static bool on = true;
static bool possible = true;

/*FMOD-specific stuff*/
//static FMOD_RESULT	result;
//static FMOD_SYSTEM* fmodsystem = NULL;
//static FMOD_SOUND* mainTheme, * level1, * sfx;
//static FMOD_CHANNEL* bgmChannel1, * sfxChannel1;
//static FMOD_CHANNELGROUP* soundMusic;
//static FMOD_CHANNELGROUP* soundEffects;

class AudioSystem : public IContainer
{
public:
	// call this every frame
	void Update();
	void Init();
	
	AudioSystem();
	~AudioSystem();

	void Play(std::string& name);

	void StopAllSound();

	void AddObject(size_t uId, void* component = 0);
	void RemoveObject(size_t uId);

	std::unordered_map < size_t, AudioComponent*> _soundList;

	FMOD_SYSTEM* _fmodSystem;
private:

	SoundManager _soundManager;

	FMOD_CHANNEL* _channel1;
	FMOD_CHANNEL* _channel2;

	FMOD_CHANNELGROUP* _bgmGroup;
	FMOD_CHANNELGROUP* _sfxGroup;
};

#endif
