#include "PrecompiledHeaders.h"
#include "AnimationSystem.h"

void AnimationSystem::Update(double dt)
{
	
	for (auto& animCompPair : MyComponentManger._AnimationComponents)
	{
		AnimationComponent* GC = animCompPair.second;

		GC->UpdateTimeDelay(dt);
		
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