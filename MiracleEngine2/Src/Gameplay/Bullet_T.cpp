#include "PrecompiledHeaders.h"
#include "../Engine/EngineSystems.h"
#include "../GameObjectComponents/LogicComponents/PrecompiledScriptType.h"

Bullet_T::Bullet_T() : _lifeTime{ -666.f }
{}
void Bullet_T::SerialiseComponent(Serialiser& document)
{
	if (document.HasMember("Lifetime") && document["Lifetime"].IsFloat())	//Checks if the variable exists in .Json file
	{
		_lifeTime = (document["Lifetime"].GetFloat());
	}
}

void Bullet_T::Update(double dt)
{
	if (_lifeTime > 0.0f)
		_lifeTime -= dt;

	if (_lifeTime < 0.0f && _lifeTime != -666.f)
		DestoryThis();
}

void Bullet_T::OnCollision2DTrigger(Collider2D* other)
{
	GameObject* explosion = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()[TypeIdGO::EXPLOSION]);
	((TransformComponent*)explosion->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetPos(
		((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetPos());
	DestoryThis();
}