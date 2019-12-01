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


	void Serialise(std::string filepath)
	{
		Serialiser file(filepath);

		size_t NumOfFrames = file["NoofFrames"].GetInt();

		Frame* ptr = nullptr;
		float uv[4];	//buffer to contain the uv values temporary

		for (int i = 1; i <= NumOfFrames; i++)
		{
			// Array of U0, V0, U1, V1 - Array of 4 floats
			for (int a = 0; a < 4; a++)
			{
				uv[a] = file[std::to_string(i).c_str()][a].GetFloat();
			}

			ptr = new Frame(uv[0], uv[1], uv[2], uv[3]);

			frame.push_back(ptr);
		}

	}

private:

	// vector of sprite frame make up a sequence of images, each frame is 1 image
	std::vector<Frame*> frame;
	
	// ID to select which spritesheet
	int _textureID;


	
};

#endif

