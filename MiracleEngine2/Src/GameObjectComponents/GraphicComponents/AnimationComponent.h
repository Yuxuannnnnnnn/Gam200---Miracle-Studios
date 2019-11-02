#pragma once

#include "../Animation/Animation.h"
#include <vector>

class AnimationComponent: public IComponentSystem
{
public:
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
private:
	std::vector<Animation*> _animation;
	int _currentAnimation;
	int _startingFrame;
};

