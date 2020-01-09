#include "PrecompiledHeaders.h"
#include "AnimationSystem.h"

void AnimationSystem::Update(double dt)
{
	
	for (auto& animCompPair : MyComponentManger._AnimationComponents)
	{
		AnimationComponent* GC = animCompPair.second;
		GC->_timeDelay = GC->_timeDelay - dt;
		if (GC->_timeDelay < 0.0f)
		{
			GC->_timeDelay = 0.5f;
			GC->_currFrame = GC->_currFrame + 1;

			if (GC->_currFrame > 6)
				GC->_currFrame = 0;
		}
	}
	
	//for (auto& e : MyComponentManger._AnimationComponents)
	//{
	//	if (e.second->GetParentId() < 1000 || e.second->GetParentPtr()->GetDestory())
	//		continue;
	//
	//	e.second->testanim->_frameDelay -= 0.35f;
	//	
	//	if (e.second->testanim->_frameDelay < 0.0f)
	//	{
	//		e.second->testanim->_frameDelay = 1.0f;
	//		e.second->testanim->_currentFrame += 1;
	//		if (e.second->testanim->_currentFrame > 7)
	//			e.second->testanim->_currentFrame = 0;
	//	}
	//
	//}
	// if  ___ ms > 10
	// animation.update();
}

void AnimationSystem::Exit()
{
}