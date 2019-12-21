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
#include "Components/ImGuizmoComponent.h"

#include "Interfaces/IManager.h"

class ImGuizmoManager final : public IManager
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

	void AddObject(size_t uId, void* component = 0);
	void RemoveObject(size_t uId);

	void SetPickObjectUId(size_t uId);

private:
	void EditTransform(const float* cameraView, float* cameraProjection, float* matrix);

};

#endif
