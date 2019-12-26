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
public:
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


	virtual void DeserialiseComponentSceneFile(IComponent* protoCom, DeSerialiser& SceneFile) override
	{
		AnimationComponent* protoAnimCom = dynamic_cast<AnimationComponent*>(protoCom);

		bool addComponentIntoSceneFile = false;
		rapidjson::Value animationsList;
		animationsList.SetArray();

		rapidjson::Value startingAnim;

		if (protoAnimCom->_startingAnim.compare(_startingAnim))	//If audiofile of Object is diff from prototype
		{
			addComponentIntoSceneFile = true;
			startingAnim.SetString(rapidjson::StringRef(_startingAnim.c_str()));
		}

		
		for (auto& anim: _animations)
		{
			//Search Prototype for animation file, if dont have then add.
			if (std::find(protoAnimCom->_animations.begin(), protoAnimCom->_animations.end(), anim) == protoAnimCom->_animations.end())
			{
				addComponentIntoSceneFile = true;
				animationsList.PushBack(rapidjson::StringRef(anim.c_str()), SceneFile.Allocator());
			}
		}


		if (addComponentIntoSceneFile)	//If anyone of component data of obj is different from Prototype
		{
			SceneFile.AddMember("AnimationComponent", rapidjson::Value(true));

			if (!animationsList.IsNull())	//if rapidjson::value container is not empty
			{
				SceneFile.AddMember("AnimationTypes", animationsList);
			}

			if (!startingAnim.IsNull())
			{
				SceneFile.AddMember("StartAnim", startingAnim);
			}
		}
	}



	std::string ComponentName() const override;
	virtual void Inspect() override;


	void AddAnimation(std::string animation);

	void SetCurrentAnim(std::string curr);

	void SetStartFrame(std::string frame);

	//~AnimationComponent();


};

