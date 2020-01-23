#include "PrecompiledHeaders.h"
#include "ImGuizmoManager.h"

#include "..//Dep/Imgui/ImGuizmo.h"

void ImGuizmoManager::Update()
{
	if (_dragCamera)
	{
		if (EngineSystems::GetInstance()._inputSystem->KeyDown(MOUSE_RBUTTON))
		{
			_prevPos = MyInputSystem.GetMousePos();
			_currPos = _prevPos;
		}
		else if (EngineSystems::GetInstance()._inputSystem->KeyHold(MOUSE_RBUTTON) ||
			EngineSystems::GetInstance()._inputSystem->KeyRelease(MOUSE_RBUTTON))
		{
			_currPos = MyInputSystem.GetMousePos();
			Vec3 diff = _currPos - _prevPos;
			MyCameraSystem.GetPos_CamEditor() += diff;
			_prevPos = _currPos;
		}
	}
	else if (EngineSystems::GetInstance()._inputSystem->KeyDown(MOUSE_RBUTTON))
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
				SetPickObjectUId(it.first);
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
				SetPickObjectUId( it.first);
				return;
			}
		}
	}

	ImGuizmo::SetOrthographic(true);
	ImGuizmo::BeginFrame();
	ImGui::SetNextWindowPos(ImVec2(350, 0));
	ImGui::SetNextWindowSize(ImVec2(880, 55));
	ImGui::Begin("ToolBar");
	RenderToolBar();
	ImGui::End();
}

void ImGuizmoManager::Draw()
{
	if (_pickUId != 0)
	{
		TransformComponent* transform = (TransformComponent*)GetComponentMap(Transform)[_pickUId];

		if (!transform)
		{
			_pickUId = 0;
			return;
		}

		if (!_dragCamera)
		{
			float cameraView[16];
			float cameraProjection[16];

			Vector3 cameraPos = MyCameraSystem.GetPos_CamEditor();
			float cameraZoom = MyCameraSystem.GetZoom_CamEditor();

			cameraPos /= cameraZoom;

			float viewWidth = _windowWidth / 2.f / cameraZoom;
			float viewHeight = _windowHeight / 2.f / cameraZoom;

			float camYAngle = 90.f / 180.f * 3.14159f;
			float camXAngle = 0;
			float camDistance = 8.f;

			// for orthographic
			OrthoGraphic(-viewWidth, viewWidth, -viewHeight, viewHeight, -viewWidth, viewWidth, cameraProjection);

			float eye[] = { -cameraPos._x + cosf(camYAngle) * cosf(camXAngle) * camDistance,  -cameraPos._y + sinf(camXAngle) * camDistance, -cameraPos._z + sinf(camYAngle) * cosf(camXAngle) * camDistance };
			float at[] = { -cameraPos._x  , -cameraPos._y, -cameraPos._z };
			float up[] = { 0.f, 1.f, 0.f };
			LookAt(eye, at, up, cameraView);

			float* objectMatrix = Mtx44::CreateTranspose(transform->GetModel()).m;

			EditTransform(cameraView, cameraProjection, objectMatrix);

			float matrixTranslation[3], matrixRotation[3], matrixScale[3];
			ImGuizmo::DecomposeMatrixToComponents(objectMatrix, matrixTranslation, matrixRotation, matrixScale);
			transform->SetPos(Vec3{ matrixTranslation[0],matrixTranslation[1],matrixTranslation[2] });
			transform->SetScale(Vec3{ matrixScale[0],matrixScale[1],matrixScale[2] });
			transform->SetRotate(DegToRad(matrixRotation[2]));
			//ImGuizmo::RecomposeMatrixFromComponents(transform->GetPos().m, m, transform->GetScale().m, objectMatrix);
		}
	}
}

void ImGuizmoManager::SetPickObjectUId(size_t uId)
{
	if (_dragCamera)
	{
		_dragCamera = false;
		_mCurrentGizmoOperation = ImGuizmo::TRANSLATE;
	}
	_pickUId = uId;
}

void ImGuizmoManager::SetWindowSize(float width, float height)
{
	_windowWidth = width;
	_windowHeight = height;
}

void ImGuizmoManager::RenderToolBar()
{
	if (ImGui::IsKeyPressed(KEYB_Q))
	{
		_dragCamera = true;
		_pickUId = 0;
	}
	if (ImGui::IsKeyPressed(KEYB_W))
	{
		_dragCamera = false;
		_mCurrentGizmoOperation = ImGuizmo::TRANSLATE;
	}
	if (ImGui::IsKeyPressed(KEYB_E))
	{
		_dragCamera = false;
		_mCurrentGizmoOperation = ImGuizmo::ROTATE;
	}
	if (ImGui::IsKeyPressed(KEYB_R))
	{
		_dragCamera = false;
		_mCurrentGizmoOperation = ImGuizmo::SCALE;
	}
	if (ImGui::IsKeyPressed(KEYB_F))
		MyCameraSystem.SetPos_CamEditor(_pickUId);


	ImGui::SameLine();
	if (ImGui::RadioButton("Camera", _dragCamera == true))
	{
		_dragCamera = true;
		_pickUId = 0;
	}
	ImGui::SameLine();
	if (ImGui::RadioButton("Translate", !_dragCamera && _mCurrentGizmoOperation == ImGuizmo::TRANSLATE))
	{
		_dragCamera = false;
		_mCurrentGizmoOperation = ImGuizmo::TRANSLATE;
	}
	ImGui::SameLine();
	if (ImGui::RadioButton("Rotate", !_dragCamera && _mCurrentGizmoOperation == ImGuizmo::ROTATE))
	{
		_dragCamera = false;
		_mCurrentGizmoOperation = ImGuizmo::ROTATE;
	}
	ImGui::SameLine();
	if (ImGui::RadioButton("Scale", !_dragCamera && _mCurrentGizmoOperation == ImGuizmo::SCALE))
	{
		_dragCamera = false;
		_mCurrentGizmoOperation = ImGuizmo::SCALE;
	}
	ImGui::SameLine();
	if (ImGui::Button("Go To Object"))
		MyCameraSystem.SetPos_CamEditor(_pickUId);
}

void ImGuizmoManager::EditTransform(const float* cameraView, float* cameraProjection, float* matrix)
{
	ImGuiIO& io = ImGui::GetIO();
	ImGuizmo::SetRect(0, 0, io.DisplaySize.x, io.DisplaySize.y);
	ImGuizmo::Manipulate(cameraView, cameraProjection, _mCurrentGizmoOperation, ImGuizmo::LOCAL, matrix, NULL, NULL, NULL, NULL);
}


