#pragma once

#include "../Dep/fmod/inc/fmod.h"
#include "../Dep/fmod/inc/fmod_errors.h"
#include "../Dep/fmod/inc/fmod.hpp"
#include <string>
#include <vector>
#include <map>

struct AudioVector3
{
	float _x;
	float _y;
	float _z;
};

enum AudioCategory
{
    _3DAUDIO,
    _2DAUDIO
};

class AudioEngine
{
public:
    AudioEngine();
    ~AudioEngine();

    FMOD_VECTOR VectorToFmod(const AudioVector3& vPosition);

    float dbToVolume(float dB);
    float VolumeTodB(float volume);

    bool IsPlaying(int nChannelId) const;
    bool IsEventPlaying(const std::string& strEventName) const;

    void Init();

    FMOD::Channel* PlaySFX(const std::string& sound, AudioCategory categ, bool isLooping = false);
    FMOD::Channel* PlayBGM(const std::string& sound, AudioCategory categ, bool isLooping = true);

    void PauseAllSFX();
    void ResumeAllSFX();
    void StopAllSFX();

    void PauseAllBGM();
    void ResumeAllBGM();
    void StopAllBGM();

    void PauseAllSound();
    void ResumeAllSound();
    void StopAllSound();

    void SetAllSFXVolume(float volume);
    void SetAllBGMVolume(float volume);
    void SetAllSoundVolume(float volume);

    FMOD::Sound* Create3DAudio(const std::string& audio);
    FMOD::Sound* Create2DAudio(const std::string& audio);
  

private:
    std::vector<std::string> vecOfFilename_;

    const int maxChannel_;
    FMOD::System* fmodSystem_;


    FMOD::ChannelGroup* sfxMasterChannel_;
    FMOD::ChannelGroup* bgmMasterChannel_;

    FMOD::Channel* channel_;
    std::map<std::pair<std::string, AudioCategory>, FMOD::Sound*> _soundMap;
    
};
