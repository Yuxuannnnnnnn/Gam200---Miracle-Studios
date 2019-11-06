#include "PrecompiledHeaders.h"
#include "../Engine/EngineSystems.h"
#include "../GameObjectComponents/LogicComponents/PrecompiledScriptType.h"

void Bullet_E::Update(double dt)
{
	if (_lifeTime > 0.0f)
		_lifeTime -= dt;

	if (_lifeTime < 0.0f && _lifeTime != -666.f)
		DestoryThis();
}

void Bullet_E::OnCollision2DTrigger(Collider2D* other)
{
	if (other->GetParentPtr()->Get_typeId() == (unsigned)TypeIdGO::PLAYER)
	{
		DestoryThis();
		Player* player = reinterpret_cast<Player*>(other->GetParentPtr()->GetComponent(ComponentId::LOGIC_COMPONENT, ScriptId::PLAYER));
		int hp = player->GetHealth();
		hp -= 2;
		player->SetHealth(hp);
	}
	if (other->GetParentPtr()->Get_typeId() == (unsigned)TypeIdGO::SPAWNER || other->GetParentPtr()->Get_typeId() == (unsigned)TypeIdGO::WALL)
	{
		DestoryThis();
	}
}