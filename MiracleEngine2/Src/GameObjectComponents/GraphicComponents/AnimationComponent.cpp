#include "PrecompiledHeaders.h"
#include "AnimationComponent.h"


void AnimationComponent::SetFilePath(const std::string path)
{
	_filePath = path;
}

std::string& AnimationComponent::GetFilePath()
{
	return _filePath;
}


AnimationComponent::AnimationComponent(GameObject* parent, size_t uId, IComponentSystem* component)
	: IComponentSystem(parent, uId)
{
	if (component)
	{
		AnimationComponent* animationComponent = dynamic_cast<AnimationComponent*>(component);
	}
}

void AnimationComponent::SerialiseComponent(Serialiser& document)
{

}



std::string AnimationComponent::ComponentName() const
{
	return std::string("Animation Component");
}

void AnimationComponent::Inspect()
{
	IComponentSystem::Inspect();
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