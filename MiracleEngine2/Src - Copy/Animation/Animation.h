#pragma once

#ifndef ANIMATION_H
#define ANIMATION_H

#include "Frame.h"
#include "../GraphicsSystem/QuadMesh.h"
#include "Tools/FileIO/DeSerialiser.h"

/* ------------------------------------------------------

	resource manager hold a container of animation pointers

	each animation contain a vector of frames

 --------------------------------------------------------*/

class Animation
{
public:
	Animation();
	void Select();

	// current frame to play
	int _currentFrame = 0;
	
	// delay between frames
	float _frameDelay = 1.0f;

	bool load(std::string path);
	void unload();

private:

	// vector of sprite frame make up a sequence of images, each frame is 1 image
	std::vector<Frame*>* frame;
	
	// ID to select which spritesheet
	int _textureID;
};

#endif

