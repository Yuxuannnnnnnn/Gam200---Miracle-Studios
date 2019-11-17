#pragma once

#ifndef ANIMATION_H
#define ANIMATION_H

#include "Frame.h"
#include "../GraphicsSystem/QuadMesh.h"

class Animation
{
public:
	Animation();
	void Select();
	int _currentFrame = 0;
	float _frameDelay = 1.0f;
private:
	std::vector<Frame*> frame;
	int _textureID;

	
};

#endif

