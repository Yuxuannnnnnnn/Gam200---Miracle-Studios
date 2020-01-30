#include "PrecompiledHeaders.h"
#include "CameraComponent.h"


CameraComponent::CameraComponent(GameObject* parent, size_t uId, IComponent* component)
	: IComponent(parent, uId),
	_isCurrentCamera{ false },
	_cameraZoom{1.f}
{
	if (component)
	{
		CameraComponent* cameraComponent = dynamic_cast<CameraComponent*>(component);

	}
}



std::string CameraComponent::ComponentName() const
{
	return std::string("Camera Component");
}


void CameraComponent::Inspect()
{
	IComponent::Inspect();

	ImGui::Spacing();
	bool temp = _isCurrentCamera;
	ImGui::Checkbox("MainCamera", &temp);
	ImGui::Spacing();
	SetMainCamera(temp);


	ImGui::Spacing();
	ImGui::SliderFloat("Camera Zoom", &_cameraZoom, 0.1, 15);
	ImGui::Spacing();
}


void CameraComponent::SetMainCamera(bool main)
{
	if (main)
	{
		MyCameraSystem.SetMainCamera(this->GetParentId());
		_isCurrentCamera = true;
	}
	else
	{
		if (MyCameraSystem.GetMainCameraUId() != this->GetParentId())
			_isCurrentCamera = false;
	}
}