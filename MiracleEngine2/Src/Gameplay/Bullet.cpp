#include "PrecompiledHeaders.h"
#include "../Engine/EngineSystems.h"
#include "../GameObjectComponents/LogicComponents/PrecompiledScriptType.h"

Bullet::Bullet() : _lifeTime{ -666.f }
{}


void Bullet::Update(double dt)
{
	if (_lifeTime > 0.0f)
		_lifeTime -= dt;

	if (_lifeTime < 0.0f && _lifeTime != -666.f)
		DestoryThis();
}

void Bullet::OnCollision2DTrigger(Collider2D* other )
{
	if (other->GetParentPtr()->Get_typeId() == (unsigned)TypeIdGO::ENEMY || other->GetParentPtr()->Get_typeId() == (unsigned)TypeIdGO::ENEMYTWO)
	{
		DestoryThis();
		Enemy* enemy = reinterpret_cast<Enemy*>(other->GetParentPtr()->GetComponent(ComponentId::LOGIC_COMPONENT, ScriptId::ENEMY));
		enemy->DecrementHealth();
	}
	if (other->GetParentPtr()->Get_typeId() == (unsigned)TypeIdGO::SPAWNER || 
		other->_tag == (unsigned)ColliderTag::BUILDING ||
		other->_tag == (unsigned)ColliderTag::EDGES)
	{
		DestoryThis();
	}
}