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
	if (document.HasMember("BulletSpeed") && document["BulletSpeed"].IsDouble())	//Checks if the variable exists in .Json file
	{
		_bulletSpeed = (document["BulletSpeed"].GetDouble());
	}
}

//This function is not needed for scripts
void Bullet::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{
	//rapidjson::Value value;
	//
	//value.SetString(rapidjson::StringRef(ToScriptName(_type)));
	//prototypeDoc.AddMember("Script2Id", value);
	//
	//value.SetDouble(_lifeTime);
	//prototypeDoc.AddMember("Lifetime", value);
	//
	//value.SetString(rapidjson::StringRef(IntToString(_bulletType).c_str()));
	//prototypeDoc.AddMember("BulletType", value);
	//
	//value.SetDouble(_bulletSpeed);
	//prototypeDoc.AddMember("BulletSpeed", value);
}

//For nonclonables Or Prototypes
void Bullet::DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator)
{
	rapidjson::Value value;

	value.SetString(rapidjson::StringRef(ToScriptName(_type)));
	prototypeDoc.AddMember("Script2Id", value, allocator);

	value.SetDouble(_lifeTime);
	prototypeDoc.AddMember("Lifetime", value, allocator);

	value.SetString(rapidjson::StringRef(IntToString(_bulletType).c_str()));
	prototypeDoc.AddMember("BulletType", value, allocator);

	value.SetDouble(_bulletSpeed);
	prototypeDoc.AddMember("BulletSpeed", value, allocator);
}

void Bullet::DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
{
	Bullet* script = GetScriptByLogicComponent(dynamic_cast<LogicComponent*>(protoCom), Bullet);

	if (!script)
	{
		DeSerialiseComponent(value, allocator);
		return;
	}

	rapidjson::Value lifetime;
	rapidjson::Value BulletType;
	rapidjson::Value BulletSpeed;

	bool addComponentIntoSceneFile = false;

	if (script->_lifeTime != _lifeTime)
	{
		addComponentIntoSceneFile = true;
		lifetime.SetDouble(_lifeTime);
	}

	if (script->_bulletType != _bulletType)
	{
		addComponentIntoSceneFile = true;
		BulletType.SetString(rapidjson::StringRef(IntToString(_bulletType).c_str()));
	}

	if (script->_bulletSpeed != _bulletSpeed)
	{
		addComponentIntoSceneFile = true;
		BulletSpeed.SetDouble(_bulletSpeed);
	}

	if (addComponentIntoSceneFile)	//If anyone of component data of obj is different from Prototype
	{
		rapidjson::Value scriptName;

		scriptName.SetString(rapidjson::StringRef(ToScriptName(_type)));
		value.AddMember("Script2Id", scriptName, allocator);

		
		if (!lifetime.IsNull())	//if rapidjson::value container is not empty
		{
			value.AddMember("Lifetime", lifetime, allocator);
		}
		
		if (!BulletType.IsNull())	//if rapidjson::value container is not empty
		{
			value.AddMember("BulletType", BulletType, allocator);
		}
		
		if (!BulletSpeed.IsNull())	//if rapidjson::value container is not empty
		{
			value.AddMember("BulletSpeed", BulletSpeed, allocator);
		}
	}

}

void Bullet::Inspect()
{
	ImGui::Spacing();
	ImGui::InputDouble("Lifetime ", &_lifeTime);
	ImGui::Spacing();
	ImGui::InputInt("BulletType ", &_bulletType);
	ImGui::Spacing();
	ImGui::InputDouble("BulletSpeed ", &_bulletSpeed);
	ImGui::Spacing();
}

Bullet::Bullet() : 
	_lifeTime{ 0.0 },
	_bulletType{ 0 },
	_bulletSpeed{ 0.0 },
	_justCollided{ false }
{}

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

void  Bullet::Init()
{
	if (_bulletType == 1)
		((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->SetAnimationPlaying(false);

	_body = (RigidBody2DComponent*)GetParentPtr()->GetComponent(ComponentId::CT_RigidBody2D);
}

void Bullet::LoadResource()
{
#ifdef LEVELEDITOR
	MyResourceManager.AddNewPrototypeResource({ "Explosion" , MyResourceSystem.GetPrototypeResourcePath("Explosion") });
#endif
}

void Bullet::Update(double dt)
{
	if (dt < 0)
		return;
	
	if (_bulletType == 1)
		if (_justCollided && !((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->IsAnimationPlaying())
		{
			GetParentPtr()->SetDestory();
		}


	if (_lifeTime > 0.0f)
		_lifeTime -= dt;

	if (_lifeTime < 0.0f && _lifeTime != -666.f)
		GetParentPtr()->SetDestory();

	if (_body && _body->_appliedForce == Vec3::Vec3Zero && _body->_velocity.SquaredLength() < 0.005f)
		GetParentPtr()->SetDestory();
}

void Bullet::BulletCollisionPlayer(Collider2D* other)
{
	IdentityComponent* IdCom = dynamic_cast<IdentityComponent*>(other->GetSibilingComponent(ComponentId::CT_Identity));
	std::string Id = IdCom->ObjectType();

	if (other->_tag == (unsigned)ColliderTag::BUILDING || other->_tag == (unsigned)ColliderTag::EDGES)
	{
		GetParentPtr()->SetDestory();
	}

	if (other->_tag == (unsigned)ColliderTag::ENEMY)
	{
		GetParentPtr()->SetDestory();

		LogicComponent* enemy = (LogicComponent*)other->GetParentPtr()->GetComponent(ComponentId::CT_Logic);

		if (!enemy)
			return;
			
		Enemy* enemyScript = (Enemy*)MyLogicSystem.GetScriptList()[enemy->GetScript2Id(ScriptType::SCRIPT_Enemy)];

		if (!enemyScript)
			return;

		enemyScript->DecrementHealth();
		enemyScript->SetStunned();

		return;
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
	GameObject* explosion = MyFactory.CloneGameObject(MyResourceSystem.GetPrototypeMap()["Explosion"]);
	((TransformComponent*)explosion->GetComponent(ComponentId::CT_Transform))->SetPos(
		((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetPos());
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
		player->DamagePlayer();
	}
	else if (IdCom->ObjectType().compare("Spawner") == 0 ||
		IdCom->ObjectType().compare("Wall") == 0 ||
		other->_tag == (unsigned)ColliderTag::EDGES)
	{
		GetParentPtr()->SetDestory();
	}
}

void Bullet::OnCollision2DTrigger(Collider2D* other)
{
	std::string otherType = ((IdentityComponent*)other->GetParentPtr()->GetComponent(ComponentId::CT_Identity))->ObjectType();
	if (!otherType.compare("PlayerShield"))
		;
	else
	{
		_justCollided = true;
		if (_bulletType == 1)
		{
			((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->SetCurrentAnimOnce("Explosion");
			((TransformComponent*)this->GetSibilingComponent(ComponentId::CT_Transform))->SetScaleA({300, 300, 1});
			((RigidBody2DComponent*)this->GetSibilingComponent(ComponentId::CT_RigidBody2D))->SetEnable(false);
			((Collider2D*)this->GetSibilingComponent(ComponentId::CT_CircleCollider2D))->SetEnable(false);
		}
		else
			GetParentPtr()->SetDestory();


	}

	//if (_bulletType == 1)
	//	BulletCollisionTurret(other);

	//switch (_bulletType)
	//{
	//case 1:
	//	BulletCollisionPlayer(other);
	//	break;
	//case 2:
	//	BulletCollisionTurret(other);
	//	break;
	//case 3:
	//	BulletCollisionEnemy(other);
	//	break;
	//default:
	//	break;
	//}
}
