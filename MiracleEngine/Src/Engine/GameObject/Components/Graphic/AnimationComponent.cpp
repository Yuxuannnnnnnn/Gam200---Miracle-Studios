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


AnimationComponent::AnimationComponent(GameObject* parent, size_t uId, IComponent* component)
	: IComponent(parent, uId), _currentAnim{"/0"}, _startingAnim{ "/0" }
{
	if (component)
	{
		AnimationComponent* animationComponent = dynamic_cast<AnimationComponent*>(component);
	}


	// temporary test
	//testanim = new Animation();
	//testanim->load("./Resources/TextFiles/AnimationData/CatAnimation.json");
}

void AnimationComponent::SerialiseComponent(Serialiser& document)
{
	//if (document.HasMember("Type") && document["Type"].IsString())
	//{
	//	_type = document["Type"].GetString();
	//}
	if (document.HasMember("AnimationTypes"))
	{
		for(int i = 0; i < document["AnimationTypes"].Size(); i++)
			_animations.push_back(document["AnimationTypes"][i].GetString());
	}

	if (document.HasMember("StartAnim"))
	{
		_startingAnim = document["StartAnim"].GetString();
		_currentAnim = _startingAnim;
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
