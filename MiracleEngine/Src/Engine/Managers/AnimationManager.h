#pragma once
#ifndef _ANIMATION_MANAGER_H
#define _ANIMATION_MANAGER_H

#include <unordered_map>
#include "Components/AnimationComponent.h"

#include "Interfaces/IManager.h"

class AnimationManager final : public IManager
{
private:
	std::unordered_map< size_t, AnimationComponent*> _audioList;

public:
	AnimationManager() = default;
	virtual ~AnimationManager() {}

	AnimationManager(const AnimationManager& rhs) = delete;
	AnimationManager& operator= (const AnimationManager& rhs) = delete;

	void AddObject(size_t uId, void* component = 0) { (void)uId; (void)component; };
	void RemoveObject(size_t uId) { (void)uId; };
};

#endif
