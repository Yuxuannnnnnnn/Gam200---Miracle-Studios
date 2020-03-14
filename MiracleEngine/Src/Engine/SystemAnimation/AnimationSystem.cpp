#include "PrecompiledHeaders.h"
#include "AnimationSystem.h"

void AnimationSystem::Update(double dt)
{
	if (dt < 0)
		return;

	
	for (auto& animCompPair : GetComponentMap(Animation))
	{
		if (!animCompPair.second->GetEnable())
			continue;

		AnimationComponent* GC = (AnimationComponent*)animCompPair.second;

		GC->UpdateTimeDelay(dt);
		
		//if (GC->IsPlayingOnce()) //if animation is mentioned to play only once.
		//{
		//	if (GC->GetCurrFrame() >= GC->GetMaxFrame()) //if curr frame is same as max frame
		//	{
		//		//GC->SetEnable(false); //Disable the animation component
		//		GC->SetPlayingOnce(false); //set playing once to false
		//		GC->SetAnimationPlaying(false); //turn off animation playing
		//	}
		//}
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

void AnimationSystem::UpdatePlayOnce()
{
	for (auto& animCompPair : GetComponentMap(Animation))
	{
		if (!animCompPair.second->GetEnable())
			continue;

		AnimationComponent* GC = (AnimationComponent*)animCompPair.second;

		if (GC->IsPlayingOnce()) //if animation is mentioned to play only once.
		{
			if (GC->GetCurrFrame() >= GC->GetMaxFrame()) //if curr frame is same as max frame
			{
				//GC->SetEnable(false); //Disable the animation component
				GC->SetPlayingOnce(false); //set playing once to false
				GC->SetAnimationPlaying(false); //turn off animation playing
			}
		}
	}
}

void AnimationSystem::Exit()
{
}