#include "PrecompiledHeaders.h"
#include "AnimationComponent.h"


void AnimationComponent::SetFilePath(const std::string path)
{
	_type = path;
}

std::string& AnimationComponent::GetFilePath()
{
	return _type;
}


AnimationComponent::AnimationComponent(GameObject* parent, size_t uId, IComponent* component)
	: IComponent(parent, uId), _currentAnimation{ 0 }, _startingFrame{ 0 }
{
	if (component)
	{
		AnimationComponent* animationComponent = dynamic_cast<AnimationComponent*>(component);
	}


	// temporary test
	testanim = new Animation();
	testanim->load("./Resources/TextFiles/AnimationData/CatAnimation.json");
}

void AnimationComponent::SerialiseComponent(Serialiser& document)
{
	if (document.HasMember("Type") && document["Type"].IsString())
	{
		_type = document["Type"].GetString();
	}
}



std::string AnimationComponent::ComponentName() const
{
	return std::string("Animation Component");
}

void AnimationComponent::Inspect()
{
	IComponent::Inspect();
}

void AnimationComponent::AddAnimation(const Animation& animation)
{
	_animation.push_back(new Animation(animation));
}
void AnimationComponent::SetCurrentAnim(int curr)
{
	_currentAnimation = curr;
}
void AnimationComponent::SetStartFrame(int frame)
{
	_startingFrame = frame;
}

AnimationComponent::~AnimationComponent()
{
	for (auto e : _animation)
	{
		delete e;
	}
}