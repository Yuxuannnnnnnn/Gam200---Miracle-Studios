#include "PrecompiledHeaders.h"
#include "../Engine/EngineSystems.h"
#include "../GameObjectComponents/LogicComponents/PrecompiledScriptType.h"

void Explosion::Update(double dt)
{
	if (_lifeTime > 0.0f)
		_lifeTime -= dt;

	if (_lifeTime < 0.0f && _lifeTime != -666.f)
		DestoryThis();
}

void Explosion::OnTrigger2DEnter(Collider2D* other)
{
	if (other->GetParentPtr()->Get_typeId() == (unsigned)TypeIdGO::ENEMY)
	{
		Enemy* enemy = reinterpret_cast<Enemy*>(other->GetParentPtr()->GetComponent(ComponentId::LOGIC_COMPONENT, ScriptId::ENEMY));
		enemy->DestoryThis();
	}
	if (other->GetParentPtr()->Get_typeId() == (unsigned)TypeIdGO::ENEMYTWO)
	{
		EnemyTwo* enemy = reinterpret_cast<EnemyTwo*>(other->GetParentPtr()->GetComponent(ComponentId::LOGIC_COMPONENT, ScriptId::ENEMYTWO));
		enemy->DestoryThis();
	}
}