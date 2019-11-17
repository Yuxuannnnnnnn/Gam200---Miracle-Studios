#pragma once

#include "../Animation/Animation.h"
#include <vector>
#include <string>

class AnimationComponent: public IComponentSystem
{
private:
	std::string _type;


	std::vector<int> _animations;
	std::vector<Animation*> _animation;
	int _currentAnimation;	//Current Playing Animation
	int _startingFrame;

public:
	void SetFilePath(const std::string path);
	std::string& GetFilePath();
	
	AnimationComponent(GameObject* parent = nullptr, size_t uId = 0, IComponentSystem* component = nullptr);

	void SerialiseComponent(Serialiser& document) override;
	std::string ComponentName() const override;
	virtual void Inspect() override;


	void AddAnimation(const Animation& animation);

	void SetCurrentAnim(int curr);

	void SetStartFrame(int frame);

	~AnimationComponent();


};

