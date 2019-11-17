#pragma once

#ifndef ANIMATION_H
#define ANIMATION_H

#include "Frame.h"
#include "../GraphicsSystem/QuadMesh.h"

class Animation
{
public:
	void Select();
private:
	std::vector<Frame> frame;
	int _textureID;
	int _currentFrame;

	QuadMesh _quadMesh{ 2.0f / 12, 0.0f, 3.0f / 12, 1.0f };
};

#endif

