#include "PrecompiledHeaders.h"
#include "TransformManager.h"

void TransformManager::AddObject(size_t uId)
{
}

void TransformManager::RemoveObject(size_t uId)
{
	_transformList.erase(uId);
}

TransformComponent* TransformManager::GetTransform(size_t uId)
{
	return _transformList[uId];
}

void TransformManager::UpdateTransformMartix(TransformComponent* transform)
{
}

Mtx44 TransformManager::GetTransformMartix(TransformComponent* transform)
{
	return Mtx44();
}
