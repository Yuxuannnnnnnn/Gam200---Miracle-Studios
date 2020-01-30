#include "PrecompiledHeaders.h"
#include "AnimationComponent.h"

#include "Editor/ImguiFunctions.h"

//void AnimationComponent::SetFilePath(const std::string path)
//{
//	_type = path;
//}
//
//std::string& AnimationComponent::GetFilePath()
//{
//	return _type;
//}






void AnimationComponent::SetCurrentAnim(const std::string& AniamtionType)
{
	_currentAnim = AniamtionType;
	SetStartFrame();
	ResetCurrTimeDelay();
	SetTimeDelay(AniamtionType);

	Animation* animResource = MyResourceManager.GetAnimationResource(AniamtionType);
	SetMaxFrame(animResource->GetMaxFrame());
}

AnimationComponent::AnimationComponent(GameObject* parent, size_t uId, IComponent* component)
	: IComponent(parent, uId), _currentAnim{ "/0" }, _startingAnim{ "/0" }, /*_currAnimation{ nullptr },*/ _currFrame{ 0 }, _timeDelay{ 0.5f }, _currentTimeDelay{0.5f}, _maxFrame{6}
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



