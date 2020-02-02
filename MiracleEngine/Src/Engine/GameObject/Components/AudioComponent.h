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

	std::map<audioName, std::tuple<fileName, volume, NumOfloops>> SoundList;

	std::string currentBGM;
	std::string currentSFX;

public:

//Script Usage
	void PlayBGM(const std::string& soundName);
	void PlaySFX(const std::string& soundName);

	AudioComponent(GameObject* parent, size_t uId, IComponent* component = nullptr);

	bool IsBGM();
	void SetIsBGM(bool isbgm);

	std::string ComponentName() const override;
	void SerialiseComponent(Serialiser& document) override 
	{
		//if (document.HasMember("A.TypeId") && document["A.TypeId"].IsInt())
		//	_typeIdAudio = document["A.TypeId"].GetUint();

		/*
		if (document.HasMember("A.FileName") && document["A.FileName"].IsString())
			_fileName = std::string(document["A.FileName"].GetString());

		if (document.HasMember("IsBGM") && document["IsBGM"].IsBool())
			_isBGM = document["IsBGM"].GetBool();
			*/
	}


	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override 
	{/*
		rapidjson::Value value;

		value.SetBool(true);
		prototypeDoc.AddMember("AudioComponent", rapidjson::Value(true));


		//value.SetInt(_typeIdAudio);
		//prototypeDoc.AddMember("A.TypeId", value);

		value.SetString(rapidjson::StringRef(_fileName.c_str()));
		prototypeDoc.AddMember("A.FileName", value);

		value.SetBool(_isBGM);
		prototypeDoc.AddMember("IsBGM", value);
		*/
	}

	void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator)
	{/*
		rapidjson::Value value;

		value.SetBool(true);
		prototypeDoc.AddMember("AudioComponent", rapidjson::Value(true), allocator);


		//value.SetInt(_typeIdAudio);
		//prototypeDoc.AddMember("A.TypeId", value);

		value.SetString(rapidjson::StringRef(_fileName.c_str()));
		prototypeDoc.AddMember("A.FileName", value, allocator);

		value.SetBool(_isBGM);
		prototypeDoc.AddMember("IsBGM", value, allocator);
		*/
	}


	void Inspect() override;
	

	//SceneFile Sent in must be Document[ClonableObjects][objectfile or i]
	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
	{/*
		AudioComponent* protoAudioCom = dynamic_cast<AudioComponent*>(protoCom);

		bool addComponentIntoSceneFile = false;
		rapidjson::Value audioFileName;
		rapidjson::Value isBGM;

		if (protoAudioCom->_fileName.compare(_fileName))	//If audiofile of Object is diff from prototype
		{
			addComponentIntoSceneFile = true;
			//Deserialise _fileName
			audioFileName.SetString(rapidjson::StringRef(_fileName.c_str()));
		}


		if (protoAudioCom->_isBGM != _isBGM)	//If bool for bgm of object is diff from prototype
		{
			addComponentIntoSceneFile = true;
			//Deserialise _fileName
			isBGM.SetBool(_isBGM);
		}


		if (addComponentIntoSceneFile)	//If anyone of component data of obj is different from Prototype
		{
			value.AddMember("AudioComponent", rapidjson::Value(true), allocator);

			if (!audioFileName.IsNull())	//if rapidjson::value container is not empty
			{
				value.AddMember("A.TypeId", audioFileName, allocator);
			}

			if (!isBGM.IsNull())
			{
				value.AddMember("IsBGM", audioFileName, allocator);
			}
		}*/
	}


	AudioComponent();
	~AudioComponent() = default;

	unsigned& GetTypeId();

	std::string& GetFileName();

	AudioComponent* CloneComponent() { return new AudioComponent(*this); }
};

