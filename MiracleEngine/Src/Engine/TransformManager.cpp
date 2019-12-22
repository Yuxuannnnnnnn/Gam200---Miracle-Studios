#include "PrecompiledHeaders.h"
#include "TransformManager.h"


TransformComponent* TransformManager::GetTransform(size_t uId)
{
	if (MyComponentManger._transformComponents.find(uId) == MyComponentManger._transformComponents.end())
		return nullptr;

	return MyComponentManger._transformComponents[uId];
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
