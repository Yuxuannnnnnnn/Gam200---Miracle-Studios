#include "PrecompiledHeaders.h"
#include "TransformManager.h"

void TransformManager::AddObject(size_t uId, void* component)
{
	_transformList.insert({ uId, (TransformComponent*)component });
}

void TransformManager::RemoveObject(size_t uId)
{
	_transformList.erase(uId);
}

TransformComponent* TransformManager::GetTransform(size_t uId)
{
	if (_transformList.find(uId) == _transformList.end())
		return nullptr;

	return _transformList[uId];
}

void TransformManager::UpdateTransformMartix(TransformComponent* transform)
{
}

Mtx44 TransformManager::GetTransformMartix(TransformComponent* transform)
{
	/*Mtx44 scale = Mtx44::CreateScale(transform->GetScale());
	Mtx44 rotation = Mtx44::CreateRotationZ(transform->GetRotate());
	Mtx44 translation = Mtx44::CreateTranslation(transform->GetPos());*/

	return Mtx44();
}
