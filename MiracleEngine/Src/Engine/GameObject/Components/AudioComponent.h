#pragma once
#include "../IComponent.h"


// For both audio componentand graphic component, serialize a string and a typeid
enum class TypeIdAudio {
	NONE = 0,

};

class AudioComponent : public IComponent
{
private:

	//std::string _fileName;
	//int numOfLoops;
	//float volume;


	typedef std::string fileName;
	typedef float volume;
	typedef int NumOfloops;
	typedef std::string audioName;

	std::map<audioName, std::tuple<fileName, volume, NumOfloops>> SFXList;	//Add SoundEffects

	std::map<audioName, std::tuple<fileName, volume>> BackgroundSoundList;	//Add BackgroundMusic

	audioName currentBGMName;	//When inspection changes the values, have to inform the audioSystem incase the soundtrack is playing currently
	audioName currentSFXName;



public:

//Script Usage
	void PlayBGM(const std::string& soundName);
	void PlaySFX(const std::string& soundName);

	AudioComponent(GameObject* parent, size_t uId, IComponent* component = nullptr);

	void StopBGM();
	void StopSFX();
	void StopAllSound();

	// not used
	bool IsBGM();
	void SetIsBGM(bool isbgm);

	std::string ComponentName() const override;
	void SerialiseComponent(Serialiser& document) override;
	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override;
	void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator);
	//SceneFile Sent in must be Document[ClonableObjects][objectfile or i]
	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator);


	void Inspect() override;

	AudioComponent();
	~AudioComponent() = default;

	unsigned& GetTypeId();

	std::string& GetFileName();

	AudioComponent* CloneComponent() { return new AudioComponent(*this); }
};

