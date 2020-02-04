///////////////////////////////////////////////////////////////////////////////////////
//
//	CircleCollider2DComponent.cpp
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#include "PrecompiledHeaders.h"
#include "CircleCollider2DComponent.h"
//#include "GraphicsSystem/DebugRenderer.h"

CircleCollider2DComponent::CircleCollider2DComponent() :
	_center{ Vec3{0.f,0.f,1.f} },
	_radius{ 0.f }
{
	_type = (unsigned)ColliderType::CIRCLE_COLLIDER;
}

std::string CircleCollider2DComponent::ComponentName() const
{
	return std::string("CircleCollider Component");
}




void CircleCollider2DComponent::Inspect()
{
	Collider2D::Inspect();

	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();

	ImGui::InputFloat2("Circle Center Pos X, Y", _center.m);
	ImGui::Spacing();
	ImGui::SliderFloat2("Circle Center Pos X, Y", _center.m, -1000, 1000);

	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();

	ImGui::InputFloat("Circle Radius", &_radius);
	ImGui::Spacing();
	ImGui::SliderFloat("Circle Radius", &_radius, 0, 500);

	ImGui::Spacing();
}

///////////////////////////////////////////////////////////////////////////////
	// Function Setting and Getting only
