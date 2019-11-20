#pragma once

#ifndef ANIMATIONSYSTEM_H
#define ANIMATIONSYSTEM_H

#include <map>
#include "GameObjectComponents/GraphicComponents/AnimationComponent.h"


/* ------------------------------------------------------

	loop through each animationcompoent, for each animation
	inisde check if current frame time has passed, if 
	passed, move to next frame

 --------------------------------------------------------*/


class AnimationSystem
{
public:
	void Update(std::unordered_map < size_t, AnimationComponent*>& _animationList, double dt);
	void Exit();
};

#endif

