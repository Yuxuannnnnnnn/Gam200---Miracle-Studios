#include "PrecompiledHeaders.h"
#include "Script/Bullet.h"
#include "Script/Enemy.h"
#include "Script/Player.h"

void Bullet::SerialiseComponent(Serialiser& document)
{
	if (document.HasMember("Lifetime") && document["Lifetime"].IsDouble())	//Checks if the variable exists in .Json file
	{
		_lifeTime = (document["Lifetime"].GetDouble());
	}
	if (document.HasMember("BulletType") && document["BulletType"].IsString())	//Checks if the variable exists in .Json file
	{
		std::string temp = (document["BulletType"].GetString());
		_bulletType = StringToInt(temp);
	}
}
void Bullet::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{
	rapidjson::Value value;

	value.SetDouble(_lifeTime);
	prototypeDoc.AddMember("Lifetime", value);
	value.Clear();
	value.SetInt(_bulletType);
	prototypeDoc.AddMember("BulletType", value);
	value.Clear();
	value.SetDouble(_bulletSpeed);
	prototypeDoc.AddMember("BulletSpeed", value);
	value.Clear();
}
void Bullet::Inspect()
{
	ImGui::Spacing();
	ImGui::InputDouble("Lifetime ", &_lifeTime);
	ImGui::Spacing();
	ImGui::Text("BulletType ", IntToString(_bulletType));
	ImGui::Spacing();
	ImGui::InputDouble("BulletSpeed ", &_bulletSpeed);
	ImGui::Spacing();
}

Bullet::Bullet() : _lifeTime{ 0.0 }, _bulletType{ 0 }, _bulletSpeed{ 0.0 }{}

Bullet* Bullet::Clone()
{
	return new Bullet(*this);
}

int Bullet::StringToInt(std::string& in)
{
	if (in == "BulletPlayer")
		return 1;
	else if (in == "BulletTurret")
		return 2;
	else if (in == "BulletEnemy")
		return 3;
	else // unknown
		return 0;
}
std::string Bullet::IntToString(int bulletType)
{
	std::string temp;
	switch (bulletType)
	{
	case 1:
		temp = "BulletPlayer";
		return temp;
	case 2:
		temp = "BulletTurret";
		return temp;
	case 3:
		temp = "BulletEnemy";
		return temp;
	default:
		temp = "BulletUnknown";
		return temp;
	}
}

void Bullet::Update(double dt)
{
	if (_lifeTime > 0.0f)
		_lifeTime -= dt;

	if (_lifeTime < 0.0f && _lifeTime != -666.f)
		GetParentPtr()->SetDestory();
}

void Bullet::BulletCollisionPlayer(Collider2D* other)
{
	IdentityComponent* IdCom = dynamic_cast<IdentityComponent*>(other->GetSibilingComponent(ComponentId::CT_Identity));
	std::string Id = IdCom->ObjectType();
	//(((LogicComponent*)other->GetParentPtr()->GetComponent(ComponentId::CT_Logic))->GetScript2Id(ScriptType::SCRIPT_Enemy))
	if (
		//Id->GetObjectType().compare("Enemy") == 0 && 
		(((LogicComponent*)other->GetParentPtr()->GetComponent(ComponentId::CT_Logic))->GetScript2Id(ScriptType::SCRIPT_Enemy))
	)
	{
		GetParentPtr()->SetDestory();
		//IScript2* GetSibilingScript(ScriptType type);
		Enemy* enemy = reinterpret_cast<Enemy*>(
			((LogicComponent*)other->GetParentPtr()->GetComponent(ComponentId::CT_Logic))->GetScript2Id(ScriptType::SCRIPT_Enemy)
		);
		enemy->DecrementHealth();
		enemy->SetStunned();
	}
	//if (Id.compare("EnemyThree") == 0)
	//{
	//	GetParentPtr()->SetDestory();
	//	EnemyThree* enemy = reinterpret_cast<EnemyThree*>(other->GetParentPtr()->GetComponent(ComponentId::CT_Logic, ScriptId::ENEMYTHREE));
	//	enemy->DecrementHealth();
	//}

	//if (Id.compare("Spawner") == 0 ||
	//	other->_tag == (unsigned)ColliderTag::BUILDING ||
	//	other->_tag == (unsigned)ColliderTag::EDGES)
	//{
	//	DestoryThis();
	//}
}
void Bullet::BulletCollisionTurret(Collider2D* other)
{
	//GameObject* explosion = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(MyResourceSystem.GetPrototypeMap()["Explosion"]);
	//((TransformComponent*)explosion->GetComponent(ComponentId::CT_Transform))->SetPos(
	//	((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetPos());
	//DestoryThis();
}
void Bullet::BulletCollisionEnemy(Collider2D* other)
{
	IdentityComponent* IdCom = dynamic_cast<IdentityComponent*>(other->GetSibilingComponent(ComponentId::CT_Identity));

	if (IdCom->ObjectType().compare("Player") == 0)
	{
		GetParentPtr()->SetDestory();
		Player* player = reinterpret_cast<Player*>(
			((LogicComponent*)other->GetParentPtr()->GetComponent(ComponentId::CT_Logic))->GetScript2Id(ScriptType::SCRIPT_Player)
		);
		int hp = player->GetHealth();
		hp -= 2;
		player->SetHealth(hp);
	}
	else if (IdCom->ObjectType().compare("Spawner") == 0 ||
		IdCom->ObjectType().compare("Wall") == 0 ||
		other->_tag == (unsigned)ColliderTag::EDGES)
	{
		GetParentPtr()->SetDestory();
	}
}

void Bullet::OnCollision2DTrigger(Collider2D* other )
{
	std::string temp;
	switch (_bulletType)
	{
	case 1:
		BulletCollisionPlayer(other);
		break;
	case 2:
		BulletCollisionTurret(other);
		break;
	case 3:
		BulletCollisionEnemy(other);
		break;
	default:
		break;
	}
}
