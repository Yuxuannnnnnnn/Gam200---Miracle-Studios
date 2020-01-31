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

	std::string _startingAnim;

	// let me know if got problem if vector change to map, i, e animation doesnt run.
	//std::vector<std::string> _animations;

//For Smart component Variables
	float _timeDelay;	//Factor to change from one frame to another frame
	float _currentTimeDelay; //Use to countdown the timeDelay of the specific frame
	int _currFrame;
	int _maxFrame;	//cap of the current animation

	std::string _currentAnim; //Logic Animation script will only touch and change this variable

	//Animation* _currAnimation;	//only for optimisation

public:
	//float _timeDelay;	//remove


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
		_currentTimeDelay = 0;
	}

	void SetTimeDelay(std::string AnimationName)
	{
		if (_animations.find(AnimationName) != _animations.end())
		{
			 _timeDelay = _animations[AnimationName];
			 return;
		}

		throw std::exception{ "Does not have AnimationType" };
	}

	void setCurrentAnimation(std::string AnimationName)
	{
		if (animationFileNameList.find(AnimationName) != animationFileNameList.end())
		{
			_currentAnim = animationFileNameList[AnimationName];
			return;
		}

		throw std::exception{ "Does not have AnimationType" };
	}

public:

	virtual void Inspect() override
	{
		IComponent::Inspect();

		////Inspect list of animations - Add animations - remove animations - each animation with own time Delay

		static std::unordered_map<std::string, Animation*>& animationList = MyResourceSystem.GetAnimationMap();
		std::vector<const char*> AninmationTypeList(animationList.size());
		//list[0] = "Choose a Texture ";


		int a = 0;
		for (auto& animationGraphicPair : animationList)
		{
			const char* ptr = animationGraphicPair.first.c_str();

			AninmationTypeList[a] = ptr;
			a++;
		}

	
		int i = 0;
		int select = 0;

		for (const std::pair<AnimationName, timeDelay>& animation: _animations)
		{
			ImGui::Spacing();

			if (i < _animations.size())
			{
				for (int j = 0; j < AninmationTypeList.size(); j++)
				{
					if (!strncmp(AninmationTypeList[j], animationFileNameList[animation.first].c_str(), 100))
					{
						select = j;
					}
				}
			}

			static std::vector<ImGuiFunctions::ComboFilterState> s;

			static std::vector<char*> buf;

			//static std::vector< bool *(const char* id, char* buffer, int bufferlen, /*const char** hints*/ std::vector<const char*> hints,
			//	int num_hints, ImGuiFunctions::ComboFilterState & s, std::string & _filename)> 


			if (s.size() == i)
			{
				s.push_back(ImGuiFunctions::ComboFilterState{ select, 0 });
			}
			if (buf.size() == i)
			{
				buf.push_back(new char[128]);
			}

			if (animationFileNameList[animation.first].empty())
			{
				strncpy(buf[i], "Choose an Animation File here", 18);
			}
			else
			{
				strncpy(buf[i], animationFileNameList[animation.first].c_str(), animationFileNameList[animation.first].size());
			}

			if (ImGuiFunctions::ComboFilter("AnimationType", buf[i], 128, AninmationTypeList, AninmationTypeList.size(), s[i], animationFileNameList[animation.first]))
			{
				//puts(buf);
			}


			i++;
		}
		


		////ImGui::SetCursorPos(ImVec2((MyWindowsSystem.getWindow().GetWindowWidth() - (width / scale)) * 0.5f, (MyWindowsSystem.getWindow().GetWindowHeight() - (height / scale)) * 0.5f));
		//ImGui::Image((void*)(intptr_t)(_currTexture)->GetTextureID(), ImVec2(width / scale, height / scale),
		//	ImVec2(0, 0), ImVec2(1, 1), ImVec4(1.0f, 1.0f, 1.0f, 1.0f), ImVec4(1.0f, 1.0f, 1.0f, 0.5f));


	}



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

		value.SetBool(true);
		prototypeDoc.AddMember("AnimationComponent", rapidjson::Value(true));

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


	void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator) 
	{
		rapidjson::Value value;

		value.SetBool(true);
		prototypeDoc.AddMember("AnimationComponent", rapidjson::Value(true), allocator);

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

	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
	{
		AnimationComponent* protoAnimCom = dynamic_cast<AnimationComponent*>(protoCom);

		bool addComponentIntoSceneFile = false;
		rapidjson::Value animationsList;
		animationsList.SetArray();

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

				animationsList.PushBack(strVal, allocator);
			//}
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


//Editor or Serialisation
	//void AddAnimation(std::string animationType)
	//{
	//	_animations.insert(std::pair <AnimationName, timeDelay >(animation, delay));
	//	animationFileNameList.insert(std::pair < std::string, timeDelay >(animation, delay));
	//}



	//~AnimationComponent();

	AnimationComponent* CloneComponent() { return new AnimationComponent(*this); }
};













