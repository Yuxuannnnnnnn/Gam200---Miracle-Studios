#pragma once

#ifndef ANIMATIONSYSTEM_H
#define ANIMATIONSYSTEM_H

#include <map>
#include "GameObjectComponents/GraphicComponents/AnimationComponent.h"

class AnimationSystem
{
public:
	void Update(std::unordered_map < size_t, AnimationComponent*>& _animationList, double dt);
	void Exit();
};

#endif

