///////////////////////////////////////////////////////////////////////////////////////
//
//	PhysicsSystem.h
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#ifndef _IMGUIZMO_MANAGER_H
#define _IMGUIZMO_MANAGER_H

#include <unordered_map>
#include "GameObjectComponents/PickingCollider.h"

#include "IContainer.h"

class ImGuizmoManager final : public IContainer
{
public:
	std::unordered_map< size_t, PickingCollider*> _pickList;
private:
	size_t _pickUId;
public:
	ImGuizmoManager() :_pickUId{ 0 } {}
	~ImGuizmoManager() {}

	ImGuizmoManager(const ImGuizmoManager& rhs) = delete;
	ImGuizmoManager& operator= (const ImGuizmoManager& rhs) = delete;

	void Update();
	void Draw();

	void AddObject(size_t uId);
	void RemoveObject(size_t uId);

private:
	void EditTransform(const float* cameraView, float* cameraProjection, float* matrix);

};

#endif
