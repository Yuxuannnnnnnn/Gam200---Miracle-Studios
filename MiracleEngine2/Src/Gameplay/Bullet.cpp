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

Bullet::Bullet() : _lifeTime{ 0.0 }, _bulletType{ 0 } {}

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

void Bullet::BulletCollisionPlayer(Collider2D* other)
{
	if (other->GetParentPtr()->Get_typeId() == (unsigned)TypeIdGO::ENEMY ||
		other->GetParentPtr()->Get_typeId() == (unsigned)TypeIdGO::ENEMYTWO)
	{
		DestoryThis();
		Enemy* enemy = reinterpret_cast<Enemy*>(other->GetParentPtr()->GetComponent(ComponentId::LOGIC_COMPONENT, ScriptId::ENEMY));
		enemy->DecrementHealth();
		enemy->SetStunned();
	}
	if (other->GetParentPtr()->Get_typeId() == (unsigned)TypeIdGO::ENEMYTHREE)
	{
		DestoryThis();
		EnemyThree* enemy = reinterpret_cast<EnemyThree*>(other->GetParentPtr()->GetComponent(ComponentId::LOGIC_COMPONENT, ScriptId::ENEMYTHREE));
		enemy->DecrementHealth();
	}

	if (other->GetParentPtr()->Get_typeId() == (unsigned)TypeIdGO::SPAWNER ||
		other->_tag == (unsigned)ColliderTag::BUILDING ||
		other->_tag == (unsigned)ColliderTag::EDGES)
	{
		DestoryThis();
	}
}
void Bullet::BulletCollisionTurret(Collider2D* other)
{
	GameObject* explosion = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()[TypeIdGO::EXPLOSION]);
	((TransformComponent*)explosion->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetPos(
		((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetPos());
	DestoryThis();
}
void Bullet::BulletCollisionEnemy(Collider2D* other)
{
	if (other->GetParentPtr()->Get_typeId() == (unsigned)TypeIdGO::PLAYER)
	{
		DestoryThis();
		Player* player = reinterpret_cast<Player*>(other->GetParentPtr()->GetComponent(ComponentId::LOGIC_COMPONENT, ScriptId::PLAYER));
		int hp = player->GetHealth();
		hp -= 2;
		player->SetHealth(hp);
	}
	if (other->GetParentPtr()->Get_typeId() == (unsigned)TypeIdGO::SPAWNER ||
		other->GetParentPtr()->Get_typeId() == (unsigned)TypeIdGO::WALL ||
		other->_tag == (unsigned)ColliderTag::EDGES)
	{
		DestoryThis();
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
