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

		SFXList.clear();
		BackgroundSoundList.clear();

		if (document.HasMember("AudioComponent") && document["AudioComponent"].IsBool())
			SetEnable(document["AudioComponent"].GetBool());

		if (document.HasMember("SFXList"))
		{
			for (int i = 0; i < document["SFXList"].Size(); i++)
			{
				//if (std::find(_animations.begin(), _animations.end(), document["AnimationTypes"][i].GetString()) == _animations.end())
				//{
				Serialiser datafile(document["SFXList"][i]);

				SFXList.insert(std::pair<audioName, std::tuple<fileName, volume, NumOfloops>>(datafile["SFXName"].GetString(),
					{ datafile["fileName"].GetString() , datafile["volume"].GetFloat() , datafile["NumOfloops"].GetInt() }));
				//}
			}
		}

		if (document.HasMember("BackgroundSoundList"))
		{
			for (int i = 0; i < document["BackgroundSoundList"].Size(); i++)
			{
				//if (std::find(_animations.begin(), _animations.end(), document["AnimationTypes"][i].GetString()) == _animations.end())
				//{
				Serialiser datafile(document["BackgroundSoundList"][i]);

				BackgroundSoundList.insert(std::pair<audioName, std::tuple<fileName, volume>>(datafile["BGMName"].GetString(),
					{ datafile["fileName"].GetString() , datafile["volume"].GetFloat() }));
				//}
			}
		}
	}


	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override 
	{
		rapidjson::Value value;

			value.SetBool(GetEnable());
			prototypeDoc.AddMember("AudioComponent", value);

		if (!SFXList.empty())	//If the object has the component but no sound is added to the list, do not deserialise
		{
			value.SetArray();
			{
				rapidjson::Value object;
				for (auto& anim : SFXList)
				{
					object.SetObject();
					object.AddMember("SFXName", rapidjson::StringRef(anim.first.c_str()), prototypeDoc.Allocator());
					object.AddMember("fileName", rapidjson::StringRef(std::get<0>(anim.second).c_str()), prototypeDoc.Allocator());
					object.AddMember("volume", rapidjson::Value(std::get<1>(anim.second)), prototypeDoc.Allocator());
					object.AddMember("NumOfloops", rapidjson::Value(std::get<2>(anim.second)), prototypeDoc.Allocator());

					value.PushBack(object, prototypeDoc.Allocator());
				}
				prototypeDoc.AddMember("SFXList", value);
			}
		}

		if (!BackgroundSoundList.empty())	//If the object has the component but no sound is added to the list, do not deserialise the component
		{
			value.SetArray();
			{
				rapidjson::Value object;
				for (auto& anim : BackgroundSoundList)
				{
					object.SetObject();
					object.AddMember("BGMName", rapidjson::StringRef(anim.first.c_str()), prototypeDoc.Allocator());
					object.AddMember("fileName", rapidjson::StringRef(std::get<0>(anim.second).c_str()), prototypeDoc.Allocator());
					object.AddMember("volume", rapidjson::Value(std::get<1>(anim.second)), prototypeDoc.Allocator());

					value.PushBack(object, prototypeDoc.Allocator());
				}
				prototypeDoc.AddMember("BackgroundSoundList", value);
			}
		}

	}

	void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator)
	{
		rapidjson::Value value;


			value.SetBool(GetEnable());
			prototypeDoc.AddMember("AudioComponent", value, allocator);

		if (!SFXList.empty())	//If the object has the component but no sound is added to the list, do not deserialise
		{
			value.SetArray();
			{
				rapidjson::Value object;
				for (auto& anim : SFXList)
				{
					object.SetObject();
					object.AddMember("SFXName", rapidjson::StringRef(anim.first.c_str()), allocator);
					object.AddMember("fileName", rapidjson::StringRef(std::get<0>(anim.second).c_str()), allocator);
					object.AddMember("volume", rapidjson::Value(std::get<1>(anim.second)), allocator);
					object.AddMember("NumOfloops", rapidjson::Value(std::get<2>(anim.second)), allocator);

					value.PushBack(object, allocator);
				}
				prototypeDoc.AddMember("SFXList", value, allocator);
			}
		}

		if (!BackgroundSoundList.empty())	//If the object has the component but no sound is added to the list, do not deserialise the component
		{
			value.SetArray();
			{
				rapidjson::Value object;
				for (auto& anim : BackgroundSoundList)
				{
					object.SetObject();
					object.AddMember("BGMName", rapidjson::StringRef(anim.first.c_str()), allocator);
					object.AddMember("fileName", rapidjson::StringRef(std::get<0>(anim.second).c_str()), allocator);
					object.AddMember("volume", rapidjson::Value(std::get<1>(anim.second)), allocator);

					value.PushBack(object, allocator);
				}
				prototypeDoc.AddMember("BackgroundSoundList", value, allocator);
			}
		}
	}


	void Inspect() override;
	

	//SceneFile Sent in must be Document[ClonableObjects][objectfile or i]
	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
	{
		AudioComponent* protoAnimCom = dynamic_cast<AudioComponent*>(protoCom);

		if (!protoAnimCom)
		{
			DeSerialiseComponent(value, allocator);
			return;
		}


		bool addComponentIntoSceneFile = false;
		rapidjson::Value enable;
		rapidjson::Value jsonSFXList;
		jsonSFXList.SetArray();

		rapidjson::Value jsonBackgroundSoundList;
		jsonBackgroundSoundList.SetArray();


		if (protoAnimCom->GetEnable() != this->GetEnable())
		{
			addComponentIntoSceneFile = true;
			enable.SetBool(GetEnable());
		}

		for (auto& anim : SFXList)
		{
			//Search Prototype for animation file, if dont have then add. OR if time delay is different then add the pair
			//if (protoAnimCom->_animations.find(anim.first) == protoAnimCom->_animations.end() || protoAnimCom->_animations[anim.first] != anim.second)
			//{
			addComponentIntoSceneFile = true;
			rapidjson::Value Obj;
			Obj.SetObject();

			rapidjson::Value strVal;

			strVal.SetString(anim.first.c_str(), anim.first.length(), allocator);
			Obj.AddMember("SFXName", strVal, allocator);

			strVal.SetString(std::get<0>(anim.second).c_str(), std::get<0>(anim.second).length(), allocator);
			Obj.AddMember("fileName", strVal, allocator);

			strVal.SetFloat(std::get<1>(anim.second));
			Obj.AddMember("volume", strVal, allocator);

			strVal.SetInt(std::get<2>(anim.second));
			Obj.AddMember("NumOfloops", strVal, allocator);

			jsonSFXList.PushBack(Obj, allocator);
			//}
		}

		for (auto& anim : BackgroundSoundList)
		{
			//Search Prototype for animation file, if dont have then add. OR if time delay is different then add the pair
			//if (protoAnimCom->_animations.find(anim.first) == protoAnimCom->_animations.end() || protoAnimCom->_animations[anim.first] != anim.second)
			//{
			addComponentIntoSceneFile = true;
			rapidjson::Value Obj;
			Obj.SetObject();

			rapidjson::Value strVal;

			strVal.SetString(anim.first.c_str(), anim.first.length(), allocator);
			Obj.AddMember("SFXName", strVal, allocator);

			strVal.SetString(std::get<0>(anim.second).c_str(), std::get<0>(anim.second).length(), allocator);
			Obj.AddMember("fileName", strVal, allocator);

			strVal.SetFloat(std::get<1>(anim.second));
			Obj.AddMember("volume", strVal, allocator);

			jsonBackgroundSoundList.PushBack(Obj, allocator);
			//}
		}



		if (addComponentIntoSceneFile)	//If anyone of component data of obj is different from Prototype
		{
			if (!enable.IsNull())
				value.AddMember("AudioComponent", enable, allocator);
			else
				value.AddMember("AudioComponent", protoAnimCom->GetEnable(), allocator);


			if (!jsonSFXList.IsNull())	//if rapidjson::value container is not empty
			{
				value.AddMember("SFXList", jsonSFXList, allocator);
			}

			if (!jsonBackgroundSoundList.IsNull())
			{
				value.AddMember("BackgroundSoundList", jsonBackgroundSoundList, allocator);
			}
		}
	}


	AudioComponent();
	~AudioComponent() = default;

	unsigned& GetTypeId();

	std::string& GetFileName();

	AudioComponent* CloneComponent() { return new AudioComponent(*this); }
};

