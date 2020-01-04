#pragma once
#include "../IComponent.h"


// For both audio componentand graphic component, serialize a string and a typeid
enum class TypeIdAudio {
	NONE = 0,

};

class AudioComponent : public IComponent
{
private:
	unsigned _typeIdAudio;

	std::string _fileName;
	bool _isBGM;
	unsigned _fileTrackLength;
	size_t _lifetimeTotal;
	size_t _lifetimeCurrent;
	bool _loop;

public:
	AudioComponent(GameObject* parent, size_t uId, IComponent* component = nullptr);

	bool IsBGM();
	void SetIsBGM(bool isbgm);

	std::string ComponentName() const override;
	void SerialiseComponent(Serialiser& document) override 
	{
		if (document.HasMember("A.TypeId") && document["A.TypeId"].IsInt())
			_typeIdAudio = document["A.TypeId"].GetUint();

		if (document.HasMember("A.FileName") && document["A.FileName"].IsString())
			_fileName = std::string(document["A.FileName"].GetString());

		if (document.HasMember("IsBGM") && document["IsBGM"].IsBool())
			_isBGM = document["IsBGM"].GetBool();
	}


	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override 
	{
		rapidjson::Value value;

		value.SetBool(true);
		prototypeDoc.AddMember("AudioComponent", rapidjson::Value(true));


		value.SetInt(_typeIdAudio);
		prototypeDoc.AddMember("A.TypeId", value);

		value.SetString(rapidjson::StringRef(_fileName.c_str()));
		prototypeDoc.AddMember("A.FileName", value);

		value.SetBool(_isBGM);
		prototypeDoc.AddMember("IsBGM", value);
	}


	void Inspect() override;
	

	//SceneFile Sent in must be Document[ClonableObjects][objectfile or i]
	void DeserialiseComponentSceneFile(IComponent* protoCom, DeSerialiser& SceneFile) override
	{
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
			SceneFile.AddMember("AudioComponent", rapidjson::Value(true));

			if (!audioFileName.IsNull())	//if rapidjson::value container is not empty
			{
				SceneFile.AddMember("A.TypeId", audioFileName);
			}

			if (!isBGM.IsNull())
			{
				SceneFile.AddMember("IsBGM", audioFileName);
			}
		}
	}


	AudioComponent();
	~AudioComponent() = default;

	unsigned& GetTypeId();

	std::string& GetFileName();

};

