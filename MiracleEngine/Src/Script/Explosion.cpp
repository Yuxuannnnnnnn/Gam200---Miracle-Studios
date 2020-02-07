#include "PrecompiledHeaders.h"
#include "Script/Explosion.h"
#include "Script/Enemy.h"

Explosion::Explosion() : _init{ false }, _lifeTime { -666.f }, _radius{ 0 }
{}

Explosion* Explosion::Clone()
{
	return new Explosion(*this);
}

void Explosion::SerialiseComponent(Serialiser& document)
{
	if (document.HasMember("Lifetime") && document["Lifetime"].IsDouble())	//Checks if the variable exists in .Json file
	{
		_lifeTime = (document["Lifetime"].GetDouble());
	}
	if (document.HasMember("Radius") && document["Radius"].IsInt())	//Checks if the variable exists in .Json file
	{
		_radius = (document["Radius"].GetInt());
	}
}
void Explosion::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{
	rapidjson::Value value;

	value.SetDouble(_lifeTime);
	prototypeDoc.AddMember("Lifetime", value);
	value.Clear();
	value.SetInt(_radius);
	prototypeDoc.AddMember("Radius", value);
	value.Clear();
}

void Explosion::Inspect()
{
	ImGui::Spacing();
	ImGui::InputDouble("Lifetime ", &_lifeTime);
	ImGui::Spacing();
	ImGui::InputInt("Radius ", &_radius);
	ImGui::Spacing();
}

void Explosion::Update(double dt)
{
	if (!_init)
	{
		_init = true;
		//((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->SetCurrentAnimOnce("boom");
		_lifeTime = ((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->GetTimeDelay() * ((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->GetMaxFrame();
	//	((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->SetTimeDelay(
	//		_lifeTime / ((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->GetMaxFrame() );
	}
	if (_lifeTime > 0.0f)
		_lifeTime -= dt;

	if (_lifeTime < 0.0f && _lifeTime != -666.f)
		GetParentPtr()->SetDestory();
}

void Explosion::OnTrigger2DEnter(Collider2D* other)
{
	//IdentityComponent* IdCom = dynamic_cast<IdentityComponent*>(other->GetSibilingComponent(ComponentId::CT_Identity));
	//std::string Id = IdCom->ObjectType();

	//if (Id.compare("Enemy") || Id.compare("EnemyTwo"))
	//{
	//	Enemy* enemy = reinterpret_cast<Enemy*>(
	//		((LogicComponent*)other->GetParentPtr()->GetComponent(ComponentId::CT_Logic))->GetScript2Id(ScriptType::SCRIPT_Enemy)
	//		);
	//	enemy->GetParentPtr()->SetDestory();
	//}
}

void Explosion::OnCollision2DStay(Collider2D* other)
{
	//IdentityComponent* IdCom = dynamic_cast<IdentityComponent*>(other->GetSibilingComponent(ComponentId::CT_Identity));
	//std::string Id = IdCom->ObjectType();

	//if (Id.compare("Enemy") || Id.compare("EnemyTwo"))
	//{
	//	Enemy* enemy = reinterpret_cast<Enemy*>(
	//		((LogicComponent*)other->GetParentPtr()->GetComponent(ComponentId::CT_Logic))->GetScript2Id(ScriptType::SCRIPT_Enemy)
	//		);
	//	enemy->GetParentPtr()->SetDestory();
	//}
}
