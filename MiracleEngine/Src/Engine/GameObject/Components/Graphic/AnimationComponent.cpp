#include "PrecompiledHeaders.h"
#include "AnimationComponent.h"


//void AnimationComponent::SetFilePath(const std::string path)
//{
//	_type = path;
//}
//
//std::string& AnimationComponent::GetFilePath()
//{
//	return _type;
//}


void AnimationComponent::UpdateTimeDelay(float dt)
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

std::string& AnimationComponent::GetCurrAnim()
{
	return _currentAnim;
}

AnimationComponent::AnimationComponent(GameObject* parent, size_t uId, IComponent* component)
	: IComponent(parent, uId), _currentAnim{ "/0" }, _startingAnim{ "/0" }, _currAnimation{ nullptr }, _currFrame{ 0 }, _timeDelay{ 0.5f }, _currentTimeDelay{0.5f}, _maxFrame{6}
{
	if (component)
	{
		AnimationComponent* animationComponent = dynamic_cast<AnimationComponent*>(component);
	}


	// temporary test
	//testanim = new Animation();
	//testanim->load("./Resources/TextFiles/AnimationData/CatAnimation.json");
}



std::string AnimationComponent::ComponentName() const
{
	return std::string("Animation Component");
}



void AnimationComponent::AddAnimation(std::string animation)
{
	_animations.push_back(animation);
}

void AnimationComponent::SetCurrentAnim(std::string curr)
{
	_currentAnim = curr;
}

void AnimationComponent::SetStartFrame(std::string frame)
{
	_startingAnim = frame;
}
