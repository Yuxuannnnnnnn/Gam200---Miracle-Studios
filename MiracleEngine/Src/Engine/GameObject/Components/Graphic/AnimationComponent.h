#pragma once

#include "SystemAnimation/Animation.h"
#include <map>
#include <string>

class AnimationComponent: public IComponent
{
private:
	std::vector<std::string> _animations;

	std::string _currentAnim;
	std::string _startingAnim;

	Animation* _currAnimation;

public:
	int _currFrame;
	float _timeDelay;
	std::string& GetCurrAnim();
	
	// temporary test, wait for resource manager

	const std::vector<std::string>& GetAnimationDataFileList() const
	{
		return _animations;
	}


	
	AnimationComponent(GameObject* parent = nullptr, size_t uId = 0, IComponent* component = nullptr);

	void SerialiseComponent(Serialiser& document) override
	{
		//if (document.HasMember("Type") && document["Type"].IsString())
		//{
		//	_type = document["Type"].GetString();
		//}
		if (document.HasMember("AnimationTypes"))
		{
			for (int i = 0; i < document["AnimationTypes"].Size(); i++)
			{
				//if (std::find(_animations.begin(), _animations.end(), document["AnimationTypes"][i].GetString()) == _animations.end())
				//{
					_animations.push_back(document["AnimationTypes"][i].GetString());
				//}
			}
		}

		if (document.HasMember("StartAnim"))
		{
			_startingAnim = document["StartAnim"].GetString();
			_currentAnim = _startingAnim;
		}
	}


	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override
	{
		rapidjson::Value value;

		value.SetBool(true);
		prototypeDoc.AddMember("AnimationComponent", rapidjson::Value(true));

		value.SetArray();
		{
			for (auto& anim : _animations)
			{
				value.PushBack(rapidjson::StringRef(anim.c_str()), prototypeDoc.Allocator());
			}
			prototypeDoc.AddMember("AnimationTypes", value);
		}

		value.SetString(rapidjson::StringRef(_startingAnim.c_str()));
		prototypeDoc.AddMember("StartAnim", value);
	}



	void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator) 
	{
		rapidjson::Value value;

		value.SetBool(true);
		prototypeDoc.AddMember("AnimationComponent", rapidjson::Value(true), allocator);

		value.SetArray();
		{
			for (auto& anim : _animations)
			{
				value.PushBack(rapidjson::StringRef(anim.c_str()), allocator);
			}
			prototypeDoc.AddMember("AnimationTypes", value, allocator);
		}

		value.SetString(rapidjson::StringRef(_startingAnim.c_str()));
		prototypeDoc.AddMember("StartAnim", value, allocator);
	}

	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
	{
		AnimationComponent* protoAnimCom = dynamic_cast<AnimationComponent*>(protoCom);

		bool addComponentIntoSceneFile = false;
		rapidjson::Value animationsList;
		animationsList.SetArray();

		for (auto& anim: _animations)
		{
			//Search Prototype for animation file, if dont have then add.
			if (std::find(protoAnimCom->_animations.begin(), protoAnimCom->_animations.end(), anim) == protoAnimCom->_animations.end())
			{
				addComponentIntoSceneFile = true;
				rapidjson::Value strVal;
				strVal.SetString(anim.c_str(), anim.length(), allocator);
				animationsList.PushBack(strVal, allocator);
			}
		}

		rapidjson::Value startingAnim;

		if (protoAnimCom->_startingAnim.compare(_startingAnim))	//If audiofile of Object is diff from prototype
		{
			addComponentIntoSceneFile = true;
			startingAnim.SetString(_startingAnim.c_str(), _startingAnim.length(), allocator);
		}


		if (addComponentIntoSceneFile)	//If anyone of component data of obj is different from Prototype
		{
			value.AddMember("AnimationComponent", rapidjson::Value(true), allocator);

			if (!animationsList.IsNull())	//if rapidjson::value container is not empty
			{
				value.AddMember("AnimationTypes", animationsList, allocator);
			}

			if (!startingAnim.IsNull())
			{
				value.AddMember("StartAnim", startingAnim, allocator);
			}
		}
	}



	std::string ComponentName() const override;
	virtual void Inspect() override;


	void AddAnimation(std::string animation);

	void SetCurrentAnim(std::string curr);

	void SetStartFrame(std::string frame);

	//~AnimationComponent();

	IComponent* CloneComponent() { return nullptr; }
};

