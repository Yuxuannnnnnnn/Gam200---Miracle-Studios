#include "PrecompiledHeaders.h"
#include "AnimationSystem.h"

void AnimationSystem::Update(std::unordered_map < size_t, AnimationComponent*>& _animationList, double dt)
{

	for (auto& e : _animationList)
	{
		e.second->testanim->_frameDelay -= 0.35f;
		
		if (e.second->testanim->_frameDelay < 0.0f)
		{
			e.second->testanim->_frameDelay = 1.0f;
			e.second->testanim->_currentFrame += 1;
			if (e.second->testanim->_currentFrame > 7)
				e.second->testanim->_currentFrame = 0;
		}

	}
	// if  ___ ms > 10
	// animation.update();
}

void AnimationSystem::Exit()
{
}


void AnimationSystem::AddObject(size_t uId, void* component)
{
	(void)uId;
	(void)component;
}

void AnimationSystem::RemoveObject(size_t uId)
{
	(void)uId;
}