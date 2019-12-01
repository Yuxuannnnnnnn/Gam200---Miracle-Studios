#include "PrecompiledHeaders.h"
#include "../Engine/EngineSystems.h"
#include "../GameObjectComponents/LogicComponents/PrecompiledScriptType.h"

Explosion::Explosion() : _lifeTime{ -666.f }
{}
void Explosion::SerialiseComponent(Serialiser& document)
{
	if (document.HasMember("Lifetime") && document["Lifetime"].IsFloat())	//Checks if the variable exists in .Json file
	{
		_lifeTime = (document["Lifetime"].GetFloat());
	}
}

void Explosion::Update(double dt)
{
	if (_lifeTime > 0.0f)
		_lifeTime -= dt;

	if (_lifeTime < 0.0f && _lifeTime != -666.f)
		DestoryThis();
}

void Explosion::OnTrigger2DEnter(Collider2D* other)
{
	if (other->GetParentPtr()->Get_typeId() == (unsigned)TypeIdGO::ENEMY ||
		other->GetParentPtr()->Get_typeId() == (unsigned)TypeIdGO::ENEMYTWO)
	{
		Enemy* enemy = reinterpret_cast<Enemy*>(other->GetParentPtr()->GetComponent(ComponentId::LOGIC_COMPONENT, ScriptId::ENEMY));
		enemy->DestoryThis();
	}
	if (other->GetParentPtr()->Get_typeId() == (unsigned)TypeIdGO::ENEMYTHREE)
	{
		EnemyThree* enemy = reinterpret_cast<EnemyThree*>(other->GetParentPtr()->GetComponent(ComponentId::LOGIC_COMPONENT, ScriptId::ENEMYTHREE));
		enemy->DestoryThis();
	}
}
