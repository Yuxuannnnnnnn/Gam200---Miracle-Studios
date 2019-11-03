#include "PrecompiledHeaders.h"
#include "AnimationComponent.h"


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
