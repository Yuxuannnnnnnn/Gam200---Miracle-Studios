#pragma once

#ifndef ANIMATIONSYSTEM_H
#define ANIMATIONSYSTEM_H

#include <map>
#include "Components/AnimationComponent.h"

#include "Interfaces/IManager.h"

/* ------------------------------------------------------

	loop through each animationcompoent, for each animation
	inisde check if current frame time has passed, if 
	passed, move to next frame

 --------------------------------------------------------*/


class AnimationSystem : public IManager
{
public:
	void Update(std::unordered_map < size_t, AnimationComponent*>& _animationList, double dt);
	void Exit();

	void AddObject(size_t uId, void* component = 0);
	void RemoveObject(size_t uId);
};

#endif

