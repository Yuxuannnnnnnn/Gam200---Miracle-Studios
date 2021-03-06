#include "PrecompiledHeaders.h"
#include "GameObject/Components/Logic/PrecompiledScriptType.h"

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
	IdentityComponent* IdCom = dynamic_cast<IdentityComponent*>(other->GetSibilingComponent(ComponentId::CT_Identity));
	std::string Id = IdCom->ObjectType();

	if (Id.compare("Enemy") || Id.compare("EnemyTwo"))
	{
		Enemy* enemy = reinterpret_cast<Enemy*>(other->GetParentPtr()->GetComponent(ComponentId::CT_Logic, ScriptId::ENEMY));
		enemy->DestoryThis();
	}
}
