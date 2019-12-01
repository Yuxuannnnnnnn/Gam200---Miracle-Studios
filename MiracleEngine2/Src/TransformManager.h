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
#include "GameObjectComponents/GraphicComponents/TransformComponent.h"

#include "IContainer.h"

class TransformManager final : public IContainer
{
private:
	std::unordered_map< size_t, TransformComponent*> _transformList;

public:
	TransformManager() = default;
	virtual ~TransformManager() {}

	TransformManager(const TransformManager& rhs) = delete;
	TransformManager& operator= (const TransformManager& rhs) = delete;

	void AddObject(size_t uId);
	void RemoveObject(size_t uId);

	static void UpdateTransformMartix(TransformComponent* transform);
	static Mtx44 GetTransformMartix(TransformComponent* transform);
};

#endif
