#include "PrecompiledHeaders.h"
#include "Script/Explosion.h"
#include "Script/Enemy.h"

Explosion::Explosion() : _lifeTime{ -666.f }
{}

Explosion* Explosion::Clone()
{
	return new Explosion(*this);
}

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
		GetParentPtr()->SetDestory();
}

void Explosion::OnTrigger2DEnter(Collider2D* other)
{
	IdentityComponent* IdCom = dynamic_cast<IdentityComponent*>(other->GetSibilingComponent(ComponentId::CT_Identity));
	std::string Id = IdCom->ObjectType();

	if (Id.compare("Enemy") || Id.compare("EnemyTwo"))
	{
		Enemy* enemy = reinterpret_cast<Enemy*>(
			((LogicComponent*)other->GetParentPtr()->GetComponent(ComponentId::CT_Logic))->GetScript2Id(ScriptType::SCRIPT_Enemy)
			);
		enemy->GetParentPtr()->SetDestory();
	}
}
