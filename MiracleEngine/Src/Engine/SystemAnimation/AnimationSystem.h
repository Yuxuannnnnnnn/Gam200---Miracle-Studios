#pragma once

#ifndef ANIMATIONSYSTEM_H
#define ANIMATIONSYSTEM_H

#include <map>
#include "GameObject/Components/Graphic/AnimationComponent.h"
/* ------------------------------------------------------

	loop through each animationcompoent, for each animation
	inisde check if current frame time has passed, if 
	passed, move to next frame

 --------------------------------------------------------*/


class AnimationSystem
{
public:
	void Update(double dt);


	void UpdatePlayOnce();
	void Exit();
};

#endif

