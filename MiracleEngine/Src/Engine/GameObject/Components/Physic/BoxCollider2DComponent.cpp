//
//	BoxCollider2DComponent.cpp
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#include "PrecompiledHeaders.h"
#include "BoxCollider2DComponent.h"

BoxCollider2DComponent::BoxCollider2DComponent() :
	_center{ Vec3{0.f,0.f,1.f} },
	_scale{ Vec3{1.f,1.f,1.f} },
	_angle{ 0.f }
{
	_type = (unsigned)ColliderType::BOX_COLLIDER;
}

std::string BoxCollider2DComponent::ComponentName() const
{
	return std::string("BoxCollider Component");
}



void BoxCollider2DComponent::Inspect()
{
	Collider2D::Inspect();

	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();

	Vec3 tempPos = _center;

	ImGui::InputFloat2("Box Center Pos X, Y", tempPos.m);
	ImGui::Spacing();
	ImGui::SliderFloat2("Box Center Pos X, Y ##slider", tempPos.m, -1000, 1000);
	_center = tempPos;

	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();

	ImGui::InputFloat2("Box Scale X, Y", _scale.m);
	ImGui::Spacing();
	ImGui::SliderFloat2("Box Scale X, Y ##slider", _scale.m, 1, 500);

	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();

	float DegAngle = RadToDeg(_angle);
	ImGui::InputFloat("Box Rotation Angle", &DegAngle);
	ImGui::Spacing();
	ImGui::SliderFloat("Box Rotation Angle ##slider", &DegAngle, -180, 180);
	_angle = DegToRad(DegAngle);

	ImGui::Spacing();
}

///////////////////////////////////////////////////////////////////////////////
	// Function Setting and Getting only