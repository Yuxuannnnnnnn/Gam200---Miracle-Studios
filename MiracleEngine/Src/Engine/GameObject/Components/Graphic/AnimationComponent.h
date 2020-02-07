#pragma once

#include "SystemAnimation/Animation.h"
#include <map>
#include <string>
#include "Tools/Resource/ResourceSystem.h"
#include "Editor/ImguiFunctions.h"




/* 
	animationcomponent: we want have each seperate time delay for each individual animation, e.g. run, walk, idle

	each seperate spritesheet have its own time delay and max number of frames

	each update loop, animation system will call UpdateTimeDelay, pass in dt.
*/


class AnimationComponent: public IComponent
{
	// let designer choose timedelay for individual anim

	// _timeDelay = the time delay for specific anim, can be diff for run and walk

	// _currentTimeDelay decrease every loop 

	// maxFrame = max number of frame for specific anim, can be diff for run and walk


private:



//For editor Variables

	typedef float timeDelay;
	typedef std::string AnimationName;
	typedef std::string AnimationFile;

	std::map<AnimationName, AnimationFile> animationFileNameList;
	std::map<AnimationName, timeDelay> _animations;	//Each animation has its own timedelay

	std::string _startingAnim;	//AnimationName

	// let me know if got problem if vector change to map, i, e animation doesnt run.
	//std::vector<std::string> _animations;

//For Smart component Variables
	bool _playOnce; 
	bool _animationPlaying;
	
	float _timeDelay;	//Factor to change from one frame to another frame
	float _currentTimeDelay; //Use to countdown the timeDelay of the specific frame
	int _currFrame;
	int _maxFrame;	//cap of the current animation



	std::string _currentAnim; //Logic Animation script will only touch and change this variable //Json FileName

	std::string _currenAnimName;
	Animation* _currAnimationResource;	//only for optimisation

public:
	//float _timeDelay;	//remove



	void SetAnimationPlaying(bool set)
	{
		_animationPlaying = set;
	}

	//Updates currentTimeDelay, as delay reaches 0, change to another frame
	//When reaches max frame, frame start from 0 again.
	void UpdateTimeDelay(float dt)
	{
		_currentTimeDelay -= dt;
		if (_currentTimeDelay < 0.0f)
		{
			_currentTimeDelay = _timeDelay;
			_currFrame = _currFrame + 1;

			if (_currFrame > _maxFrame)
				_currFrame = 0;
		}
	}


	// get current playing animation
	std::string& GetCurrAnim()
	{
		return _currentAnim;
	}

	inline int GetCurrFrame() { return _currFrame; }


	Texture2D* GetCurrentTexture()
	{
		if(!_currentAnim.empty())	//If currentAnimation is not empty
			return _currAnimationResource->GetSpriteSheet();
		return nullptr;
	}

	Animation* GetAnimationResource()
	{
		return _currAnimationResource;
	}

	int GetCurrentFrame();



	int GetMaxFrame();
	float GetTimeDelay();
	void SetTimeDelay(float time);

	bool IsPlayingOnce();
	void SetPlayingOnce(bool);
	// Starting get from seriailize file, i.e starting anim delay and maxframe. when current changed, update this fn
// called when switching animation from idle to run, etc
	//void GetTimeDelayFromCurrentAnim(/* take in args if needed */)
	//{
	//	// TODO:: get timedelay and max frame from current anim serialized file
	//	// _timeDelay = ...
	//	_currentTimeDelay = _timeDelay;
	//	_currFrame = _maxFrame;
	//}


//Only for Logic Animation script--------------------------------------
	void SetCurrentAnim(const std::string& AniamtionType);
	void SetCurrentAnimOnce(const std::string& AnimationType);
	bool IsAnimationPlaying();


//---------------------------------------------------------------------


private:
	void SetStartFrame()
	{
		_currFrame = 0;
	}

	void SetMaxFrame(int maxFrame)
	{
		_maxFrame = maxFrame;
	}

	void ResetCurrTimeDelay()
	{
		_currentTimeDelay = _timeDelay;
	}

	void SetTimeDelay(std::string AnimationName)
	{
		if (_animations.find(AnimationName) != _animations.end())
		{
			_timeDelay = _animations[AnimationName];
			return;
		}

		return;
		throw std::exception{ "Does not have AnimationType" };
	}

	void setCurrentAnimation(std::string AnimationName)
	{
		if (animationFileNameList.find(AnimationName) != animationFileNameList.end())
		{
			_currentAnim = animationFileNameList[AnimationName];
			return;
		}

		return;
		throw std::exception{ "Does not have AnimationType" };
	}

	void SetAnimationResource()
	{
		_currAnimationResource = MyResourceSystem.GetAnimationResource(_currentAnim);
	}


public:

	virtual void Inspect() override;



	const std::map<std::string, timeDelay>& GetAnimationDataFileList() const
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

		_animations.clear();
		animationFileNameList.clear();

		if (document.HasMember("AnimationComponent") && document["AnimationComponent"].IsBool())
			SetEnable(document["AnimationComponent"].GetBool());

		if (document.HasMember("AnimationTypes"))
		{
			for (int i = 0; i < document["AnimationTypes"].Size(); i++)
			{
				//if (std::find(_animations.begin(), _animations.end(), document["AnimationTypes"][i].GetString()) == _animations.end())
				//{
				Serialiser datafile(document["AnimationTypes"][i]);

				_animations.insert(std::pair<AnimationName, timeDelay>(datafile["AnimationName"].GetString(), datafile["TimeDelay"].GetFloat()));
				animationFileNameList.insert(std::pair<AnimationName, AnimationFile>(datafile["AnimationName"].GetString(), datafile["AnimationType"].GetString()));
				//}
			}
		}

		if (document.HasMember("StartAnim"))
		{
			_startingAnim = document["StartAnim"].GetString();
			SetCurrentAnim(_startingAnim);
		}

		//_currAnimation = MyResourceManager.GetAnimationResource(_startingAnim);
	}


	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override
	{
		rapidjson::Value value;

		if (!animationFileNameList.empty())
		{
			value.SetBool(GetEnable());
			prototypeDoc.AddMember("AnimationComponent", value);


			value.SetArray();
			{
				rapidjson::Value object;
				for (auto& anim : _animations)
				{
					object.SetObject();
					object.AddMember("AnimationType", rapidjson::StringRef(animationFileNameList[anim.first].c_str()), prototypeDoc.Allocator());
					object.AddMember("TimeDelay", rapidjson::Value(anim.second), prototypeDoc.Allocator());
					object.AddMember("AnimationName", rapidjson::StringRef(anim.first.c_str()), prototypeDoc.Allocator());

					value.PushBack(object, prototypeDoc.Allocator());
				}
				prototypeDoc.AddMember("AnimationTypes", value);
			}

			value.SetString(rapidjson::StringRef(_startingAnim.c_str()));
			prototypeDoc.AddMember("StartAnim", value);
		}


	}


	void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator) 
	{
		rapidjson::Value value;


		if (!animationFileNameList.empty())
		{
			value.SetBool(GetEnable());
			prototypeDoc.AddMember("AnimationComponent", value, allocator);

	
			value.SetArray();
			{
				rapidjson::Value object;
				for (auto& anim : _animations)
				{
					object.SetObject();
					object.AddMember("AnimationType", rapidjson::StringRef(animationFileNameList[anim.first].c_str()), allocator);
					object.AddMember("TimeDelay", rapidjson::Value(anim.second), allocator);
					object.AddMember("AnimationName", rapidjson::StringRef(anim.first.c_str()), allocator);


					value.PushBack(object, allocator);
				}
				prototypeDoc.AddMember("AnimationTypes", value, allocator);
			}

			value.SetString(rapidjson::StringRef(_startingAnim.c_str()));
			prototypeDoc.AddMember("StartAnim", value, allocator);
		}
	}

	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
	{
		AnimationComponent* protoAnimCom = dynamic_cast<AnimationComponent*>(protoCom);

		if (!protoAnimCom)
		{
			DeSerialiseComponent(value, allocator);
			return;
		}


		bool addComponentIntoSceneFile = false;
		rapidjson::Value enable;
		rapidjson::Value animationsList;
		animationsList.SetArray();

		if (protoAnimCom->GetEnable() != this->GetEnable())
		{
			addComponentIntoSceneFile = true;
			enable.SetBool(GetEnable());
		}

		for (auto& anim: _animations)
		{
			//Search Prototype for animation file, if dont have then add. OR if time delay is different then add the pair
			//if (protoAnimCom->_animations.find(anim.first) == protoAnimCom->_animations.end() || protoAnimCom->_animations[anim.first] != anim.second)
			//{
				addComponentIntoSceneFile = true;
				rapidjson::Value Obj;
				Obj.SetObject();

				rapidjson::Value strVal;

				strVal.SetString(animationFileNameList[anim.first].c_str(), animationFileNameList[anim.first].length(), allocator);
				Obj.AddMember("AnimationType", strVal, allocator);

				strVal.SetFloat(anim.second);
				Obj.AddMember("TimeDelay", strVal, allocator);

				strVal.SetString(anim.first.c_str(), anim.first.length(), allocator);
				Obj.AddMember("AnimationName", strVal, allocator);

				animationsList.PushBack(Obj, allocator);
			//}
		}

		rapidjson::Value startingAnim;

		if (protoAnimCom->_startingAnim.compare(_startingAnim) && !_startingAnim.empty())	//If audiofile of Object is diff from prototype
		{
			addComponentIntoSceneFile = true;
			startingAnim.SetString(_startingAnim.c_str(), _startingAnim.length(), allocator);
		}


		if (addComponentIntoSceneFile)	//If anyone of component data of obj is different from Prototype
		{
			if (!enable.IsNull())
				value.AddMember("AnimationComponent", enable, allocator);
			else
				value.AddMember("AnimationComponent", protoAnimCom->GetEnable(), allocator);


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


//Editor or Serialisation
	//void AddAnimation(std::string animationType)
	//{
	//	_animations.insert(std::pair <AnimationName, timeDelay >(animation, delay));
	//	animationFileNameList.insert(std::pair < std::string, timeDelay >(animation, delay));
	//}



	//~AnimationComponent();

	AnimationComponent* CloneComponent() { return new AnimationComponent(*this); }
};













