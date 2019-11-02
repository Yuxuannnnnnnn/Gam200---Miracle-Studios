#pragma once

#ifndef ANIMATION_H
#define ANIMATION_H

#include "Frame.h"

class Animation
{
public:
	
private:
	std::vector<Frame> frame;
	int _textureID;
	int _currentFrame;
};

#endif

