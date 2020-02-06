#pragma once

#ifndef AUDIOSYSTEM_H
#define AUDIOSYSTEM_H

#include "../Dep/fmod/inc/fmod.h"
#include "../Dep/fmod/inc/fmod_errors.h"
#include "../Dep/fmod/inc/fmod.hpp"
#include "GameObject/Components/AudioComponent.h"

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

class AudioSystem
{
public:
	// call this every frame
	void Update();
	void Init();
	
	AudioSystem();
	~AudioSystem();

	void PlayBGM(const std::string& name, float volume = 1.0f);
	void PlaySFX(const std::string& name, float volume = 1.0f);


	void Play(const std::string& name, bool isBGM = false);

	void StopAllSound();
	void StopBGM();
	void StopSFX();

	FMOD_SYSTEM* _fmodSystem;
private:
	FMOD_CHANNEL* _channel1 = nullptr;
	FMOD_CHANNEL* _channel2 = nullptr;

	FMOD_CHANNELGROUP* _bgmGroup = nullptr;
	FMOD_CHANNELGROUP* _sfxGroup = nullptr;
};

#endif
