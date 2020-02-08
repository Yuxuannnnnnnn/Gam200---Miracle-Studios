#include "PrecompiledHeaders.h"
#include "AudioEngine.h"

AudioEngine::AudioEngine()
    :
    maxChannel_{ 32 },
    fmodSystem_{ nullptr },
    sfxMasterChannel_{ nullptr },
    bgmMasterChannel_{ nullptr },
    channel_{ nullptr }
{
}
   

AudioEngine::~AudioEngine()
{
    FMOD_RESULT result;

    for (std::pair<const std::pair<std::string, AudioCategory>, FMOD::Sound*>& elem : _soundMap)
    {
        result = elem.second->release();

        if (result != FMOD_OK)
        {
            std::cout << "FMOD::RELEASE SOUND " + elem.first.first + " failed" << std::endl;
        }
    }

    result = sfxMasterChannel_->release();

    if (result != FMOD_OK)
    {
        std::cout << "FMOD::RELEASE SFX Master Channel failed" << std::endl;
    }

    result = bgmMasterChannel_->release();


    if (result != FMOD_OK)
    {
        std::cout << "FMOD::RELEASE BGM Master Channel failed" << std::endl;
    }

    result = fmodSystem_->release();


    if (result != FMOD_OK)
    {
        std::cout << "FMOD::RELEASE System failed" << std::endl;
    }

    Init();
}

void AudioEngine::Init()
{

    FMOD_RESULT result;

    result = FMOD::System_Create(&fmodSystem_);


    if (result != FMOD_OK)
    {
        std::cout << "FMOD::SYSTEM_CREATE failed" << std::endl;
    }

    int driverCount = 0;

    fmodSystem_->getNumDrivers(&driverCount);


    if (driverCount == 0)
    {
        std::cout << "No more driver count for FMOD::SYSTEM" << std::endl;

    }

    result = fmodSystem_->init(maxChannel_, FMOD_INIT_NORMAL, nullptr);


    if (result != FMOD_OK)
    {
        std::cout << "FMOD::INIT failed" << std::endl;

    }

    result = fmodSystem_->createChannelGroup("SFX Master Channel", &sfxMasterChannel_);


    if (result != FMOD_OK)
    {
        std::cout << "FMOD::CREATECHANNELGROUP for SFX Sound failed" << std::endl;
      
    }

    result = fmodSystem_->createChannelGroup("BGM Master Channel", &bgmMasterChannel_);

    if (result != FMOD_OK)
    {
        std::cout << "FMOD::CREATECHANNELGROUP for BGM Sound failed" << std::endl;
    }

}

float AudioEngine::dbToVolume(float dB)
{
    return powf(10.0f, 0.05f * dB);
}

float AudioEngine::VolumeTodB(float volume)
{
    return 20.0f * log10f(volume);
}

FMOD_VECTOR AudioEngine::VectorToFmod(const AudioVector3& vPosition) {
    FMOD_VECTOR fVec;
    fVec.x = vPosition._x;
    fVec.y = vPosition._y;
    fVec.z = vPosition._z;
    return fVec;
}

    //std::vector<AudioListener*>::iterator itr = audioListener_.begin();

    ////Take the first one for now
    //if (itr != audioListener_.end())
    //{
    //    Vector3 pos = (*itr)->GetGameObject()->GetComponent<Transform>()->GetGlobalTranslation();
    //    FMOD_VECTOR fmodPos;

    //    fmodPos.x = pos.x_;
    //    fmodPos.y = pos.y_;
    //    fmodPos.z = pos.z_;

    //    fmodSystem_->set3DListenerAttributes(0, &fmodPos, NULL, NULL, NULL);
    //}

    //fmodSystem_->update();
    //audioSource_.Update();








FMOD::Channel* AudioEngine::PlaySFX(const std::string& sound, AudioCategory categ, bool isLooping)
{
    std::pair<std::string, AudioCategory> selectedAudio = std::make_pair(sound, categ);

    if (isLooping)
    {
        _soundMap[selectedAudio]->setMode(FMOD_LOOP_NORMAL);
    }
    else
    {
        _soundMap[selectedAudio]->setMode(FMOD_LOOP_OFF);
    }

    fmodSystem_->playSound(_soundMap[selectedAudio], sfxMasterChannel_, true, &channel_);

    return channel_;
}

FMOD::Channel* AudioEngine::PlayBGM(const std::string& sound, AudioCategory categ, bool isLooping)
{
    std::pair<std::string, AudioCategory> selectedAudio = std::make_pair(sound, categ);

    if (isLooping)
    {
        _soundMap[selectedAudio]->setMode(FMOD_LOOP_NORMAL);
    }
    else
    {
        _soundMap[selectedAudio]->setMode(FMOD_LOOP_OFF);
    }

    fmodSystem_->playSound(_soundMap[selectedAudio], bgmMasterChannel_, true, &channel_);

    return channel_;
}

void AudioEngine::PauseAllSFX()
{
    sfxMasterChannel_->setPaused(true);
}

void AudioEngine::ResumeAllSFX()
{
    sfxMasterChannel_->setPaused(false);
}

void AudioEngine::StopAllSFX()
{
    sfxMasterChannel_->stop();
}

void AudioEngine::PauseAllBGM()
{
    bgmMasterChannel_->setPaused(true);
}

void AudioEngine::ResumeAllBGM()
{
    bgmMasterChannel_->setPaused(false);
}

void AudioEngine::StopAllBGM()
{
    bgmMasterChannel_->stop();
}

void AudioEngine::PauseAllSound()
{
    PauseAllSFX();
    PauseAllBGM();
}

void AudioEngine::ResumeAllSound()
{
    ResumeAllSFX();
    ResumeAllBGM();
}

void AudioEngine::StopAllSound()
{
    StopAllSFX();
    StopAllBGM();
}

void AudioEngine::SetAllSFXVolume(float volume)
{
    sfxMasterChannel_->setVolume(volume);
}

void AudioEngine::SetAllBGMVolume(float volume)
{
    bgmMasterChannel_->setVolume(volume);
}

void AudioEngine::SetAllSoundVolume(float volume)
{
    SetAllSFXVolume(volume);
    SetAllBGMVolume(volume);
}

FMOD::Sound* AudioEngine::Create3DAudio(const std::string& audioPath)
{
    FMOD::Sound* audio;

    FMOD_RESULT result = fmodSystem_->createSound(audioPath.c_str(), FMOD_DEFAULT | FMOD_3D, nullptr, &audio);

    if (result != FMOD_OK)
    {
        std::cout << "FMOD create audio failed" << std::endl;
  
    }

    return audio;
}

FMOD::Sound* AudioEngine::Create2DAudio(const std::string& audioPath)
{
    FMOD::Sound* audio;

    FMOD_RESULT result = fmodSystem_->createSound(audioPath.c_str(), FMOD_DEFAULT, nullptr, &audio);

    if (result != FMOD_OK)
    {
        std::cout << "FMOD create audio failed" << std::endl;

    }

    return audio;
}


