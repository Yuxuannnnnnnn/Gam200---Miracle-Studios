#include "PrecompiledHeaders.h"
#include "ImGuizmoManager.h"

#include "..//Dep/Imgui/ImGuizmo.h"
#include "Collision.h"

void ImGuizmoManager::Update()
{
	if (_pickUId != 0 &&
		EngineSystems::GetInstance()._inputSystem->KeyHold(KEYB_Q) &&
		EngineSystems::GetInstance()._inputSystem->KeyHold(MOUSE_RBUTTON))
	{
		if (_pickList.find(_pickUId) == _pickList.end())
			return;

		TransformComponent* transform = _engineSystems._transforManager->GetTransform(_pickUId);
		Vector3  pos = EngineSystems::GetInstance()._inputSystem->GetMousePos();
		transform->SetPos(pos);

	}
	else if (_pickUId != 0 &&
		EngineSystems::GetInstance()._inputSystem->KeyHold(KEYB_W) &&
		EngineSystems::GetInstance()._inputSystem->KeyHold(MOUSE_RBUTTON))
	{
		if (_pickList.find(_pickUId) == _pickList.end())
			return;

		TransformComponent* transform = _engineSystems._transforManager->GetTransform(_pickUId);

		if (EngineSystems::GetInstance()._inputSystem->KeyHold(KEYB_A))
		{
			transform->GetRotate() += 0.3f;
		}
		else if (EngineSystems::GetInstance()._inputSystem->KeyHold(KEYB_D))
		{
			transform->GetRotate() -= 0.3f;
		}
	}
	else if (EngineSystems::GetInstance()._inputSystem->KeyDown(KEYB_S) &&
		EngineSystems::GetInstance()._inputSystem->KeyHold(MOUSE_RBUTTON))
	{
		InspectionImguiWindow::InspectGameObject(nullptr);
		_pickUId = 0;
	}
	else if (EngineSystems::GetInstance()._inputSystem->KeyDown(KEYB_A) &&
		EngineSystems::GetInstance()._inputSystem->KeyHold(MOUSE_RBUTTON))
	{
		Vector3  pos = EngineSystems::GetInstance()._inputSystem->GetMousePos();

		for (auto it : _pickList)
		{
			if (!it.second->GetEnable())
				continue;

			_engineSystems._collisionManager->UpdateColliderData(it.second);

			if (TestBoxVsPoint(*it.second, pos))
			{
				_pickUId = it.second->GetParentId();
				InspectionImguiWindow::InspectGameObject(it.second->GetParentPtr());
				return;
			}
		}
	}


	//_pickUId = 1002;

	//if (_pickUId != 0)
	//{
	//	TransformComponent* transform = _transformList[_pickUId];

	//	//ImGuizmo::SetOrthographic(true/false);
	//	ImGuizmo::BeginFrame();
	//	ImGui::SetNextWindowPos(ImVec2(10, 10));
	//	ImGui::SetNextWindowSize(ImVec2(320, 340));
	//	ImGui::Begin("Editor");

	//	const float* cameraView;
	//	float* cameraProjection;
	//	float* objectMatrix;
	//	EngineSystems::GetInstance()._graphicsSystem->TestFuction(_pickUId, cameraView, cameraProjection, objectMatrix);
	//	EditTransform(cameraView, cameraProjection, objectMatrix);

	//	float m[3] = { 0,0,0 };

	//	ImGuizmo::DecomposeMatrixToComponents(objectMatrix, transform->GetPos().m, m, transform->GetScale().m);

	//	//ImGuizmo::RecomposeMatrixFromComponents(matrixTranslation, matrixRotation, matrixScale, objectMatrix);

	//	ImGui::End();
	//}
}

void ImGuizmoManager::Draw()
{
	for (auto it : _pickList)
	{
		if (!it.second->GetEnable() || !it.second->_componentEnable)
			continue;

		_engineSystems._collisionManager->UpdateColliderData(it.second);

		BoxCollider2D* object = (BoxCollider2D*)it.second;

		DrawDebugLine(
			object->mCorner[0]._x, object->mCorner[0]._y,
			object->mCorner[1]._x, object->mCorner[1]._y);
		DrawDebugLine(
			object->mCorner[1]._x, object->mCorner[1]._y,
			object->mCorner[2]._x, object->mCorner[2]._y);
		DrawDebugLine(
			object->mCorner[2]._x, object->mCorner[2]._y,
			object->mCorner[3]._x, object->mCorner[3]._y);
		DrawDebugLine(
			object->mCorner[3]._x, object->mCorner[3]._y,
			object->mCorner[0]._x, object->mCorner[0]._y);

		DebugRenderer::GetInstance().DrawLine(
			object->mOrigin._x, object->mOrigin._y,
			object->mOrigin._x + object->mAxis[0]._x * 40.f,
			object->mOrigin._y + object->mAxis[0]._y * 40.f);
		DebugRenderer::GetInstance().DrawLine(
			object->mOrigin._x, object->mOrigin._y,
			object->mOrigin._x + object->mAxis[1]._x * 40.f,
			object->mOrigin._y + object->mAxis[1]._y * 40.f);
	}
}

void ImGuizmoManager::AddObject(size_t uId, void* component)
{
	_pickList.insert({ uId, (PickingCollider*)component });
}

void ImGuizmoManager::RemoveObject(size_t uId)
{
	_pickList.erase(uId);
}

void ImGuizmoManager::EditTransform(const float* cameraView, float* cameraProjection, float* matrix)
{
	static ImGuizmo::OPERATION mCurrentGizmoOperation(ImGuizmo::TRANSLATE);
	static ImGuizmo::MODE mCurrentGizmoMode(ImGuizmo::LOCAL);
	static bool useSnap = false;
	static float snap[3] = { 1.f, 1.f, 1.f };
	static float bounds[] = { -0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f };
	static float boundsSnap[] = { 0.1f, 0.1f, 0.1f };
	static bool boundSizing = false;
	static bool boundSizingSnap = false;

	if (ImGui::IsKeyPressed(90))
		mCurrentGizmoOperation = ImGuizmo::TRANSLATE;
	if (ImGui::IsKeyPressed(69))
		mCurrentGizmoOperation = ImGuizmo::ROTATE;
	if (ImGui::IsKeyPressed(82)) // r Key
		mCurrentGizmoOperation = ImGuizmo::SCALE;
	if (ImGui::RadioButton("Translate", mCurrentGizmoOperation == ImGuizmo::TRANSLATE))
		mCurrentGizmoOperation = ImGuizmo::TRANSLATE;
	ImGui::SameLine();
	if (ImGui::RadioButton("Rotate", mCurrentGizmoOperation == ImGuizmo::ROTATE))
		mCurrentGizmoOperation = ImGuizmo::ROTATE;
	ImGui::SameLine();
	if (ImGui::RadioButton("Scale", mCurrentGizmoOperation == ImGuizmo::SCALE))
		mCurrentGizmoOperation = ImGuizmo::SCALE;
	float matrixTranslation[3], matrixRotation[3], matrixScale[3];
	ImGuizmo::DecomposeMatrixToComponents(matrix, matrixTranslation, matrixRotation, matrixScale);
	ImGui::InputFloat3("Tr", matrixTranslation, 3);
	ImGui::InputFloat3("Rt", matrixRotation, 3);
	ImGui::InputFloat3("Sc", matrixScale, 3);
	ImGuizmo::RecomposeMatrixFromComponents(matrixTranslation, matrixRotation, matrixScale, matrix);

	if (mCurrentGizmoOperation != ImGuizmo::SCALE)
	{
		if (ImGui::RadioButton("Local", mCurrentGizmoMode == ImGuizmo::LOCAL))
			mCurrentGizmoMode = ImGuizmo::LOCAL;
		ImGui::SameLine();
		if (ImGui::RadioButton("World", mCurrentGizmoMode == ImGuizmo::WORLD))
			mCurrentGizmoMode = ImGuizmo::WORLD;
	}
	if (ImGui::IsKeyPressed(83))
		useSnap = !useSnap;
	ImGui::Checkbox("", &useSnap);
	ImGui::SameLine();

	switch (mCurrentGizmoOperation)
	{
	case ImGuizmo::TRANSLATE:
		ImGui::InputFloat3("Snap", &snap[0]);
		break;
	case ImGuizmo::ROTATE:
		ImGui::InputFloat("Angle Snap", &snap[0]);
		break;
	case ImGuizmo::SCALE:
		ImGui::InputFloat("Scale Snap", &snap[0]);
		break;
	}
	ImGui::Checkbox("Bound Sizing", &boundSizing);
	if (boundSizing)
	{
		ImGui::PushID(3);
		ImGui::Checkbox("", &boundSizingSnap);
		ImGui::SameLine();
		ImGui::InputFloat3("Snap", boundsSnap);
		ImGui::PopID();
	}

	ImGuiIO& io = ImGui::GetIO();
	ImGuizmo::SetRect(0, 0, io.DisplaySize.x, io.DisplaySize.y);
	ImGuizmo::Manipulate(cameraView, cameraProjection, mCurrentGizmoOperation, mCurrentGizmoMode, matrix, NULL, useSnap ? &snap[0] : NULL, boundSizing ? bounds : NULL, boundSizingSnap ? boundsSnap : NULL);

}
