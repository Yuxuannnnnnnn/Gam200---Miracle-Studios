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

void Explosion::OnTrigger2DEnter(ICollider2D* other)
{
	IdentityComponent* IdCom = dynamic_cast<IdentityComponent*>(other->GetSibilingComponent(ComponentId::IDENTITY_COMPONENT));
	std::string Id = IdCom->ObjectType();

	if (Id.compare("Enemy") || Id.compare("EnemyTwo"))
	{
		Enemy* enemy = reinterpret_cast<Enemy*>(other->GetParentPtr()->GetComponent(ComponentId::LOGIC_COMPONENT, ScriptId::ENEMY));
		enemy->DestoryThis();
	}
}
