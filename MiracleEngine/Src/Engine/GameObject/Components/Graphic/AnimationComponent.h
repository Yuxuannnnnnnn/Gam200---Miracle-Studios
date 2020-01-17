#pragma once

#include "SystemAnimation/Animation.h"
#include <map>
#include <string>
#include "Tools/Resource/ResourceSystem.h"


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

	typedef float timeDelay;
	std::map<std::string, timeDelay> _animations;	//Each animation has its own timedelay
	// let me know if got problem if vector change to map, i, e animation doesnt run.
	//std::vector<std::string> _animations;

	float _timeDelay;
	float _currentTimeDelay;

	int _currFrame;
	int _maxFrame;

	std::string _currentAnim;
	std::string _startingAnim;

	Animation* _currAnimation;	//only for optimisation

public:
	//float _timeDelay;	//remove

	// Starting get from seriailize file, i.e starting anim delay and maxframe. when current changed, update this fn
	// called when switching animation from idle to run, etc
	void GetTimeDelayFromCurrentAnim(/* take in args if needed */)
	{
		// TODO:: get timedelay and max frame from current anim serialized file
		// _timeDelay = ...
		_currentTimeDelay = _timeDelay;
		_currFrame = _maxFrame;
	}

	void UpdateTimeDelay(float dt);



	// get current playing animation
	std::string& GetCurrAnim();
	inline int GetCurrFrame() { return _currFrame; }


	timeDelay GetTimeDelay(std::string animationType)
	{
		if (_animations.find(animationType) != _animations.end())
		{
			return _animations[animationType];
		}

		throw std::exception{"Does not have AnimationType"};
	}
	

	virtual void Inspect() override
	{
		IComponent::Inspect();

		//Inspect list of animations - Add animations - remove animations - each animation with own time Delay

		ImGui::Spacing();
		
		static auto& AnimationList = MyResourceSystem.GetAnimationMap();
		
		int animationCount = 1;
		static std::vector<int> select(AnimationList.size(), 0);
		

		if (ImGui::Button("Add Animation"))
		{
			_animations.insert(std::pair<std::string, timeDelay>(" ", 0.0f));
			select.push_back(0);
		}



		
		for (auto currshader : _current_ShaderList)
		{
			ImGui::Spacing();
		
			auto shader = _shaderList.begin();
		
			std::vector<const char*> list(ShaderList.size() + 1);
			list[0] = " Choose a shader ";
		
			int i = 1;
			//static int select = 0;
			for (auto shaderPair = ShaderList.begin(); shaderPair != ShaderList.end(); shaderPair++)
			{
				const char* ptr = shaderPair->first.c_str();
				list[i] = ptr;
				if (shader != _shaderList.end())
				{
					if (strncmp(shaderPair->first.c_str(), shader->c_str(), 20) && currshader != nullptr)
					{
						select[shaderCount - 1] = i;
					}
				}
				i++;
			}
			//ImGui::Combo("Add Component", &item_current, items, (int)(ComponentId::COUNTCOMPONENT));
			currshader = list[select[shaderCount - 1]];            // Here our selection is a single pointer stored outside the object.
		
			std::string shaderCountString = " Shader " + std::to_string(shaderCount);
			if (ImGui::BeginCombo(shaderCountString.c_str(), currshader, 0)) // The second parameter is the label previewed before opening the combo.
			{
				for (int n = 0; n < list.size(); n++)
				{
					bool is_selected = (currshader == list[n]);
					if (ImGui::Selectable(list[n], is_selected))
					{
						currshader = list[n];
						select[shaderCount - 1] = n;
					}
		
					//if (is_selected);
					//ImGui::SetItemDefaultFocus();   // Set the initial focus when opening the combo (scrolling + for keyboard navigation support in the upcoming navigation branch)
		
				}
				ImGui::EndCombo();
			}
			if (shader != _shaderList.end())
			{
				shader++;
			}
			shaderCount++;
		}


		//Inspect starting animation - from the list of animations




		//ImGui::SetCursorPos(ImVec2((MyWindowsSystem.getWindow().GetWindowWidth() - (width / scale)) * 0.5f, (MyWindowsSystem.getWindow().GetWindowHeight() - (height / scale)) * 0.5f));
		ImGui::Image((void*)(intptr_t)(_currTexture)->GetTextureID(), ImVec2(width / scale, height / scale),
			ImVec2(0, 0), ImVec2(1, 1), ImVec4(1.0f, 1.0f, 1.0f, 1.0f), ImVec4(1.0f, 1.0f, 1.0f, 0.5f));


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
		if (document.HasMember("AnimationTypes"))
		{
			for (int i = 0; i < document["AnimationTypes"].Size(); i++)
			{
				//if (std::find(_animations.begin(), _animations.end(), document["AnimationTypes"][i].GetString()) == _animations.end())
				//{
				Serialiser datafile(document["AnimationTypes"][i]);

				_animations.insert(std::pair<std::string, timeDelay>(datafile["AnimationType"].GetString(), datafile["TimeDelay"].GetFloat()));
				//}
			}
		}

		if (document.HasMember("StartAnim"))
		{
			_startingAnim = document["StartAnim"].GetString();
			_currentAnim = _startingAnim;
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
				object.AddMember("AnimationType", rapidjson::StringRef(anim.first.c_str()), prototypeDoc.Allocator());
				object.AddMember("TimeDelay", rapidjson::Value(anim.second), prototypeDoc.Allocator());

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
				object.AddMember("AnimationType", rapidjson::StringRef(anim.first.c_str()), allocator);
				object.AddMember("TimeDelay", rapidjson::Value(anim.second), allocator);

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
			if (protoAnimCom->_animations.find(anim.first) == protoAnimCom->_animations.end() || protoAnimCom->_animations[anim.first] != anim.second)
			{
				addComponentIntoSceneFile = true;
				rapidjson::Value strVal;
				strVal.SetString(anim.first.c_str(), anim.first.length(), allocator);
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


	void AddAnimation(std::string animation, timeDelay delay);

	void SetCurrentAnim(std::string curr);

	void SetStartFrame(std::string frame);

	//~AnimationComponent();

	IComponent* CloneComponent() { return nullptr; }
};

