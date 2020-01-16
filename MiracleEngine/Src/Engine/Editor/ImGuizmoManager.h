#ifndef _IMGUIZMO_MANAGER_H
#define _IMGUIZMO_MANAGER_H

class ImGuizmoManager final
{
private:
	size_t _pickUId;
public:
	ImGuizmoManager() :_pickUId{ 0 } {}
	~ImGuizmoManager() {}

	void Update();

	void SetPickObjectUId(size_t uId);

private:
	void EditTransform(const float* cameraView, float* cameraProjection, float* matrix);

};

#endif
