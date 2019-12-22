///////////////////////////////////////////////////////////////////////////////////////
//
//	PhysicsSystem.h
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#ifndef _TRANSFORM_MANAGER_H
#define _TRANSFORM_MANAGER_H

#include <unordered_map>
#include "GameObject/Components/Graphic/TransformComponent.h"

#include "IContainer.h"

class TransformManager final
{

public:
	TransformManager() = default;
	virtual ~TransformManager() {}

	TransformManager(const TransformManager& rhs) = delete;
	TransformManager& operator= (const TransformManager& rhs) = delete;

	TransformComponent* GetTransform(size_t uId);

	static void UpdateTransformMartix(TransformComponent* transform);
	static Mtx44 GetTransformMartix(TransformComponent* transform);
};

#endif
