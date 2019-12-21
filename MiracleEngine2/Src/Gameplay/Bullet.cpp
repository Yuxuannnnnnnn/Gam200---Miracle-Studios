#include "PrecompiledHeaders.h"
#include "../Engine/EngineSystems.h"
#include "../GameObjectComponents/LogicComponents/PrecompiledScriptType.h"

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
	if (document.HasMember("BulletSpeed") && document["BulletSpeed"].IsDouble())	//Checks if the variable exists in .Json file
	{
		_bulletSpeed = (document["BulletSpeed"].GetDouble());
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
		DestoryThis();
}

void Bullet::BulletCollisionPlayer(ICollider2D* other)
{
	IdentityComponent* IdCom = dynamic_cast<IdentityComponent*>(other->GetSibilingComponent(ComponentId::IDENTITY_COMPONENT));
	std::string Id = IdCom->ObjectType();

	if (Id.compare("Enemy") == 0 ||
		Id.compare("EnemyTwo") == 0)
	{
		DestoryThis();
		Enemy* enemy = reinterpret_cast<Enemy*>(other->GetParentPtr()->GetComponent(ComponentId::LOGIC_COMPONENT, ScriptId::ENEMY));
		enemy->DecrementHealth();
		enemy->SetStunned();
	}
	if (Id.compare("EnemyThree") == 0)
	{
		DestoryThis();
		EnemyThree* enemy = reinterpret_cast<EnemyThree*>(other->GetParentPtr()->GetComponent(ComponentId::LOGIC_COMPONENT, ScriptId::ENEMYTHREE));
		enemy->DecrementHealth();
	}

	//if (Id.compare("Spawner") == 0 ||
	//	other->_tag == (unsigned)ColliderTag::BUILDING ||
	//	other->_tag == (unsigned)ColliderTag::EDGES)
	//{
	//	DestoryThis();
	//}
}
void Bullet::BulletCollisionTurret(ICollider2D* other)
{
	GameObject* explosion = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()["Explosion"]);
	((TransformComponent*)explosion->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetPos(
		((TransformComponent*)(GetSibilingComponent(ComponentId::TRANSFORM_COMPONENT)))->GetPos());
	DestoryThis();
}
void Bullet::BulletCollisionEnemy(ICollider2D* other)
{
	IdentityComponent* IdCom = dynamic_cast<IdentityComponent*>(other->GetSibilingComponent(ComponentId::IDENTITY_COMPONENT));

	if (IdCom->ObjectType().compare("Player") == 0)
	{
		DestoryThis();
		Player* player = reinterpret_cast<Player*>(other->GetParentPtr()->GetComponent(ComponentId::LOGIC_COMPONENT, ScriptId::PLAYER));
		int hp = player->GetHealth();
		hp -= 2;
		player->SetHealth(hp);
	}
	else if (IdCom->ObjectType().compare("Spawner") == 0 ||
		IdCom->ObjectType().compare("Wall") == 0 ||
		other->_tag == (unsigned)ColliderTag::EDGES)
	{
		DestoryThis();
	}
}

void Bullet::OnCollision2DTrigger(ICollider2D* other )
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
