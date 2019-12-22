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
	
	void SetFilePath(const std::string path);
	std::string& GetFilePath();
	
	AnimationComponent(GameObject* parent = nullptr, size_t uId = 0, IComponent* component = nullptr);

	void SerialiseComponent(Serialiser& document) override;
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


	std::string ComponentName() const override;
	virtual void Inspect() override;


	void AddAnimation(std::string animation);

	void SetCurrentAnim(std::string curr);

	void SetStartFrame(std::string frame);

	//~AnimationComponent();


};

