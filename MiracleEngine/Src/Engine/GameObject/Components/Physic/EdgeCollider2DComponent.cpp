#include "PrecompiledHeaders.h"
#include"EdgeCollider2DComponent.h"

EdgeCollider2DComponent::EdgeCollider2DComponent() :
	_center{ Vec3{0.f,0.f,1.f} },
	_start{ Vec3{0.f,0.f,1.f} },
	_end{ Vec3{0.f,0.f,1.f} }
{
	_type = (unsigned)ColliderType::EDGE_COLLIDER;
}

std::string EdgeCollider2DComponent::ComponentName() const
{
	return std::string("EdgeCollider Component");
}


void EdgeCollider2DComponent::Inspect()
{
	Collider2D::Inspect();

	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();

	ImGui::InputFloat2("Edge Center Pos X, Y", _center.m);
	ImGui::Spacing();
	ImGui::SliderFloat2("Edge Center Pos X Y", _center.m, -1000, 1000);

	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();

	ImGui::InputFloat2("Edge Start Pos X, Y", _start.m);
	ImGui::Spacing();
	ImGui::SliderFloat2("Edge Start Pos X Y", _start.m, -1000, 1000);

	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();

	ImGui::InputFloat2("Edge End Pos X, Y", _end.m);
	ImGui::Spacing();
	ImGui::SliderFloat2("Edge End Pos X Y", _end.m, -1000, 1000);

	ImGui::Spacing();
}

///////////////////////////////////////////////////////////////////////////////
// Function Setting and Getting only
 
