#include "PrecompiledHeaders.h"
#include "AnimationSystem.h"

void AnimationSystem::Update(double dt)
{
	
	for (auto& animCompPair : GetComponentMap(Animation))
	{
		AnimationComponent* GC = (AnimationComponent*)animCompPair.second;

		GC->UpdateTimeDelay(dt);
		
		if (GC->IsPlayingOnce())
		{
			if (GC->GetCurrFrame() >= GC->GetMaxFrame())
			{
				GC->SetEnable(false);
				GC->SetPlayingOnce(false);
			}
		}
	}
	
	/*if (MyInputSystem.KeyDown(KeyCode::KEYB_M))
	{
		MyAudioSystem.PlayBGM("Button.ogg");
	}

	if (MyInputSystem.KeyDown(KeyCode::KEYB_N))
	{
		MyAudioSystem.PlayBGM("Coin.ogg");
	}

	if (MyInputSystem.KeyDown(KeyCode::KEYB_B))
	{
		MyAudioSystem.PlayBGM("Level1.ogg", 0.5f);
	}*/
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