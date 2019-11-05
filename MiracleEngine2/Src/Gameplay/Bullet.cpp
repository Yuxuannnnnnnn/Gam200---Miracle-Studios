#include "PrecompiledHeaders.h"
#include "../Engine/EngineSystems.h"
#include "../GameObjectComponents/LogicComponents/PrecompiledScriptType.h"

void Bullet::Update(double dt)
{
	if (_lifeTime > 0.0f)
		_lifeTime -= dt;

	if (_lifeTime < 0.0f && _lifeTime != -666.f)
		DestoryThis();
}

void Bullet::OnCollision2DTrigger(Collider2D* other)
{
	if (other->GetParentPtr()->Get_typeId() == (unsigned)TypeIdGO::ENEMY)
	{
		DestoryThis();
		Enemy* enemy = reinterpret_cast<Enemy*>(other->GetParentPtr()->GetComponent(ComponentId::LOGIC_COMPONENT, ScriptId::ENEMY));
		enemy->_health--;
	}
	if (other->GetParentPtr()->Get_typeId() == (unsigned)TypeIdGO::ENEMYTWO)
	{
		DestoryThis();
		EnemyTwo* enemy = reinterpret_cast<EnemyTwo*>(other->GetParentPtr()->GetComponent(ComponentId::LOGIC_COMPONENT, ScriptId::ENEMYTWO));
		enemy->_health--;
	}
	if (other->GetParentPtr()->Get_typeId() == (unsigned)TypeIdGO::SPAWNER || other->GetParentPtr()->Get_typeId() == (unsigned)TypeIdGO::WALL)
	{
		DestoryThis();
	}
}