#include "PrecompiledHeaders.h"
#include "ButtonManager.h"
#include "Collision.h"


void ButtonManager::Update()
{
	Vector3  pos = EngineSystems::GetInstance()._inputSystem->GetMousePos();

	for (auto it : _buttonList)
	{
		if (!it.second->GetEnable() || !it.second->_componentEnable)
			continue;

		_engineSystems._collisionManager->UpdateColliderData(it.second);

		if (TestBoxVsPoint(*it.second, pos))
		{
			if (EngineSystems::GetInstance()._inputSystem->KeyDown(MOUSE_LBUTTON) ||
				(EngineSystems::GetInstance()._inputSystem->KeyHold(MOUSE_LBUTTON) && it.second->_pressed))
			{
				EventHandler::GetInstance().AddMouseClickEvent(it.first);
			}

			EventHandler::GetInstance().AddMouseHoverEvent(it.first);
		}
	}
}

void ButtonManager::Draw()
{
	for (auto it : _buttonList)
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

void ButtonManager::AddObject(size_t uId, void* component)
{
	_buttonList.insert({ uId, (ButtonComponent*)component });
}

void ButtonManager::RemoveObject(size_t uId)
{
	_buttonList.erase(uId);
}