#include "PrecompiledHeaders.h"
#include "ImGuizmoManager.h"

#include "..//Dep/Imgui/ImGuizmo.h"

void ImGuizmoManager::Update()
{
	if (EngineSystems::GetInstance()._inputSystem->KeyHold(MOUSE_RBUTTON))
	{
		Vector3  pos = EngineSystems::GetInstance()._inputSystem->GetMousePos();

		for (auto& it : GetComponentMap(Graphic))
		{
			if (!it.second->GetEnable())
				continue;

			TransformComponent* transform = (TransformComponent*)GetComponentMap(Transform)[it.second->GetParentId()];

			if (!transform)
				continue;

			BBox pickingBox = BBox::CreateBBoxFromData(transform->GetPos(), transform->GetScale(), transform->GetRotate());

			if (Collision::BBoxVsPoint(pickingBox, pos))
			{
				InspectionImguiWindow::InspectGameObject(it.second->GetParentPtr());
				_pickUId = it.first;
				return;
			}
		}

		for (auto& it : GetComponentMap(UI))
		{
			if (!it.second->GetEnable())
				continue;

			TransformComponent* transform = (TransformComponent*)GetComponentMap(Transform)[it.second->GetParentId()];

			if (!transform)
				continue;

			BBox pickingBox = BBox::CreateBBoxFromData(transform->GetPos(), transform->GetScale(), transform->GetRotate());

			if (Collision::BBoxVsPoint(pickingBox, pos))
			{
				InspectionImguiWindow::InspectGameObject(it.second->GetParentPtr());
				_pickUId = it.first;
				return;
			}
		}
	}

	if (_pickUId != 0)
	{
		TransformComponent* transform = (TransformComponent*)GetComponentMap(Transform)[_pickUId];

		if (!transform)
		{
			_pickUId = 0;
			return;
		}

		float cameraView[16] =
		{ 1.f, 0.f, 0.f, 0.f,
		  0.f, 1.f, 0.f, 0.f,
		  0.f, 0.f, 1.f, 0.f,
		  0.f, 0.f, 0.f, 1.f };

		float cameraProjection[16];

		float viewWidth = 8.f; // for orthographic
		float camYAngle = 90.f / 180.f * 3.14159f;
		float camXAngle = 0;
		float camDistance = 8.f;

		float viewHeight = viewWidth * _windowHeight / _windowWidth;
		OrthoGraphic(-viewWidth, viewWidth, -viewHeight, viewHeight, -viewWidth, viewWidth, cameraProjection);

		ImGuizmo::SetOrthographic(true);

		float eye[] = { cosf(camYAngle) * cosf(camXAngle) * camDistance, sinf(camXAngle) * camDistance, sinf(camYAngle) * cosf(camXAngle) * camDistance };
		float at[] = { 0.f, 0.f, 0.f };
		float up[] = { 0.f, 1.f, 0.f };
		LookAt(eye, at, up, cameraView);
		ImGuizmo::BeginFrame();


		//ImGuizmo::SetOrthographic(false);
		ImGuizmo::BeginFrame();
		ImGui::SetNextWindowPos(ImVec2(300, 0));
		ImGui::SetNextWindowSize(ImVec2(300, 400));
		ImGui::Begin("Editor");

		float* objectMatrix = Mtx44::CreateTranspose(transform->GetModel()).m;

		float matrix[16] =
		{ 1.f, 0.f, 0.f, 0.f,
		  0.f, 1.f, 0.f, 0.f,
		  0.f, 0.f, 1.f, 0.f,
		  0.f, 0.f, 0.f, 1.f };

		float matrixTranslation[3], matrixRotation[3], matrixScale[3];
		ImGuizmo::DecomposeMatrixToComponents(objectMatrix, matrixTranslation, matrixRotation, matrixScale);
		matrixTranslation[0] = matrixTranslation[0] / (_windowWidth / 2 /  viewWidth);
		matrixTranslation[1] = matrixTranslation[1] / (_windowHeight / 2 / viewHeight);
		ImGuizmo::RecomposeMatrixFromComponents(matrixTranslation, matrixRotation, matrixScale, matrix);

		EditTransform(cameraView, cameraProjection, matrix);

		ImGuizmo::DecomposeMatrixToComponents(matrix, matrixTranslation, matrixRotation, matrixScale);
		matrixTranslation[0] = matrixTranslation[0] * (_windowWidth / 2 / viewWidth);
		matrixTranslation[1] = matrixTranslation[1] * (_windowHeight / 2 / viewHeight);

		transform->SetPos(Vec3{ matrixTranslation[0],matrixTranslation[1],matrixTranslation[2] });
		transform->SetScale(Vec3{ matrixScale[0],matrixScale[1],matrixScale[2] });

		//ImGuizmo::RecomposeMatrixFromComponents(transform->GetPos().m, m, transform->GetScale().m, objectMatrix);

		ImGui::End();
	}
}

void ImGuizmoManager::SetPickObjectUId(size_t uId)
{
	_pickUId = uId;
}

void ImGuizmoManager::SetWindowSize(float width, float height)
{
	_windowWidth = width;
	_windowHeight = height;
}

void ImGuizmoManager::EditTransform(const float* cameraView, float* cameraProjection, float* matrix)
{
	static ImGuizmo::OPERATION mCurrentGizmoOperation(ImGuizmo::TRANSLATE);
	static ImGuizmo::MODE mCurrentGizmoMode(ImGuizmo::LOCAL);
	/*static bool useSnap = false;
	static float snap[3] = { 1.f, 1.f, 1.f };*/
	//static float bounds[] = { -0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f };
	//static float boundsSnap[] = { 0.1f, 0.1f, 0.1f };
	//static bool boundSizing = false;
	//static bool boundSizingSnap = false;

	if (ImGui::IsKeyPressed(KEYB_Q))
		mCurrentGizmoOperation = ImGuizmo::TRANSLATE;
	/*if (ImGui::IsKeyPressed(KEYB_W))
		mCurrentGizmoOperation = ImGuizmo::ROTATE;*/
	if (ImGui::IsKeyPressed(KEYB_E))
		mCurrentGizmoOperation = ImGuizmo::SCALE;
	if (ImGui::RadioButton("Translate", mCurrentGizmoOperation == ImGuizmo::TRANSLATE))
		mCurrentGizmoOperation = ImGuizmo::TRANSLATE;
	ImGui::SameLine();
	/*if (ImGui::RadioButton("Rotate", mCurrentGizmoOperation == ImGuizmo::ROTATE))
		mCurrentGizmoOperation = ImGuizmo::ROTATE;*/
	ImGui::SameLine();
	if (ImGui::RadioButton("Scale", mCurrentGizmoOperation == ImGuizmo::SCALE))
		mCurrentGizmoOperation = ImGuizmo::SCALE;
	float matrixTranslation[3], matrixRotation[3], matrixScale[3];
	ImGuizmo::DecomposeMatrixToComponents(matrix, matrixTranslation, matrixRotation, matrixScale);
	ImGui::InputFloat3("Tr", matrixTranslation, 3);
	ImGui::InputFloat3("Rt", matrixRotation, 3);
	ImGui::InputFloat3("Sc", matrixScale, 3);


	//if (mCurrentGizmoOperation != ImGuizmo::SCALE)
	//{
	//	if (ImGui::RadioButton("Local", mCurrentGizmoMode == ImGuizmo::LOCAL))
	//		mCurrentGizmoMode = ImGuizmo::LOCAL;
	//	ImGui::SameLine();
	//	if (ImGui::RadioButton("World", mCurrentGizmoMode == ImGuizmo::WORLD))
	//		mCurrentGizmoMode = ImGuizmo::WORLD;
	//}
	//if (ImGui::IsKeyPressed(83))
	//	useSnap = !useSnap;
	//ImGui::Checkbox("", &useSnap);
	//ImGui::SameLine();

	/*switch (mCurrentGizmoOperation)
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
	}*/

	ImGuiIO& io = ImGui::GetIO();
	ImGuizmo::SetRect(0, 0, io.DisplaySize.x, io.DisplaySize.y);
	//ImGuizmo::Manipulate(cameraView, cameraProjection, mCurrentGizmoOperation, mCurrentGizmoMode, matrix, NULL, useSnap ? &snap[0] : NULL, boundSizing ? bounds : NULL, boundSizingSnap ? boundsSnap : NULL);

	ImGuizmo::Manipulate(cameraView, cameraProjection, mCurrentGizmoOperation, mCurrentGizmoMode, matrix, NULL, NULL, NULL, NULL);
}


