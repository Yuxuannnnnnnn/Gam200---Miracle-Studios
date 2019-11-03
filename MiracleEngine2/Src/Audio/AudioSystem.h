#pragma once

#ifndef AUDIOSYSTEM_H
#define AUDIOSYSTEM_H

#include "../Dep/fmod/inc/fmod.h"
#include "../Dep/fmod/inc/fmod_errors.h"
#include "../Dep/fmod/inc/fmod.hpp"


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
	
	AudioSystem();
	~AudioSystem();

	void PlayBGM();
	void PlaySFX();

	void Play();
private:

	FMOD_SYSTEM* _fmodSystem;
	FMOD_SOUND* _level1;
	FMOD_CHANNEL* _channel1;
	FMOD_CHANNELGROUP* channelGroup;

};

#endif
