#pragma once

#include "SystemAnimation/Animation.h"
#include <map>
#include <string>

class AnimationComponent: public IComponent
{
private:
	std::unordered_map<std::string, Animation*> _animations;

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

	}
	std::string ComponentName() const override;
	virtual void Inspect() override;


	void AddAnimation(const Animation& animation);

	void SetCurrentAnim(int curr);

	void SetStartFrame(int frame);

	~AnimationComponent();


};

