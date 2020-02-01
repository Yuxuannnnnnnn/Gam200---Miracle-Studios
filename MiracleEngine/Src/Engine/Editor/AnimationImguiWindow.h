#pragma once
#include "IBaseImguiWindow.h"




class AnimationImguiWindow : public IBaseImguiWindow
{
	std::string _animationName;
	float _timeDelay;
	std::string _animationType;

	float _currentTimeDelay; //Use to countdown the timeDelay of the specific frame
	int _currFrame;
	int _maxFrame;	//cap of the current animation
	float u0, v0, u1, v1;

	Texture2D* _currTexture;

	Animation* _animResource;
	
public:

	AnimationImguiWindow(bool open = false, ImGuiWindowFlags flags = 0)
		:IBaseImguiWindow("Animation", 1040, 10, 500, 500, open, flags, ImGuiCond_Once)
	{
	}

	void Update() override; //Play one frame per animation based on timedelay


	void UpdateTimeDelay(float dt)
	{
		_currentTimeDelay -= dt;
		if (_currentTimeDelay < 0.0f)
		{
			_currentTimeDelay = _timeDelay;
			_currFrame = _currFrame + 1;

			if (_currFrame > _maxFrame)
				_currFrame = 0;
		}

		Frame* currFrame = _animResource->GetCurrFrame(_currFrame);
		u0 = currFrame->_u0;
		v0 = currFrame-> _v0;
		u1 = currFrame->_u1;
		v1 = currFrame->_v1;
	}


	void SetAnimationWindow(std::string animationName, float timeDelay, std::string animationType)	//Set time delay...., animationfile
	{
		SetWindowTrue();
		_animationName = animationName;
		_timeDelay = timeDelay;
		_animationType = animationType;

		_currFrame = 0;
		_currentTimeDelay = timeDelay;
		_animResource = MyResourceSystem.GetAnimationResource(animationType);
		_maxFrame = (_animResource->GetMaxFrame());
		_currTexture = _animResource->GetSpriteSheet();
	}
};

