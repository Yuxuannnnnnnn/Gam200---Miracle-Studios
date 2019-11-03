#pragma once

#include "../Animation/Animation.h"
#include <vector>

class AnimationComponent: public IComponentSystem
{
private:
	std::vector<Animation*> _animation;
	int _currentAnimation;
	int _startingFrame;

public:
	AnimationComponent(GameObject* parent = nullptr, size_t uId = 0, IComponentSystem* component = nullptr);

	void SerialiseComponent(Serialiser& document) override;
	std::string ComponentName() const override;
	virtual void Inspect() override;


	void AddAnimation(const Animation& animation)
	{
		_animation.push_back(new Animation(animation));
	}
	void SetCurrentAnim(int curr)
	{
		_currentAnimation = curr;
	}
	void SetStartFrame(int frame)
	{
		_startingFrame = frame;
	}
	~AnimationComponent()
	{
		for (auto e : _animation)
		{
			delete e;
		}
	}

};

