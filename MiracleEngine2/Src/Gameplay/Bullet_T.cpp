#include "PrecompiledHeaders.h"
#include "../Engine/EngineSystems.h"
#include "../GameObjectComponents/LogicComponents/PrecompiledScriptType.h"

void Bullet_T::Update(double dt)
{
	if (_lifeTime > 0.0f)
		_lifeTime -= dt;

	if (_lifeTime < 0.0f && _lifeTime != -666.f)
		DestoryThis();
}

void Bullet_T::OnCollision2DTrigger(Collider2D* other)
{
	DestoryThis();
	GameObject* explosion = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()[TypeIdGO::EXPLOSION]);
	((TransformComponent*)explosion->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetPos(
		((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetPos());
}