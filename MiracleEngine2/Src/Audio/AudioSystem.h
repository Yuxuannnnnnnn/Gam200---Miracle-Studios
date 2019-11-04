#pragma once

#ifndef AUDIOSYSTEM_H
#define AUDIOSYSTEM_H

#include "SoundManager.h"

#include "../Dep/fmod/inc/fmod.h"
#include "../Dep/fmod/inc/fmod_errors.h"
#include "../Dep/fmod/inc/fmod.hpp"


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

	void Play(SoundEnum sound);
private:
	void PlaySFX(SoundEnum sound);
	void PlayBGM();
	void Sound_CreateOneShot(const char* filename, FMOD_SOUND** sound);
	SoundManager _soundManager;

	FMOD_SYSTEM* _fmodSystem;
	FMOD_SOUND* _level1;
	FMOD_SOUND* _shoot;
	FMOD_SOUND* _enemydeath;
	FMOD_CHANNEL* _channel1;
	FMOD_CHANNEL* _channel2;

	FMOD_CHANNELGROUP* _bgmGroup;
	FMOD_CHANNELGROUP* _sfxGroup;
};

#endif
