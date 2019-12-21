#include "PrecompiledHeaders.h"
#include "GameObject/Components/Logic/PrecompiledScriptType.h"

void Spawner::SerialiseComponent(Serialiser& document)
{
	if (document.HasMember("Health") && document["Health"].IsInt())
	{
		_health = (document["Health"].GetInt());
	}
	if (document.HasMember("SpawnType") && document["SpawnType"].IsInt())
	{
		_spawntype = (document["SpawnType"].GetInt());
	}
	if (document.HasMember("SpawnRate") && document["SpawnRate"].IsDouble())
	{
		_timerCooldownSpawn = (document["SpawnRate"].GetDouble());
	}

}
void Spawner::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{
	rapidjson::Value value;

}
void Spawner::Inspect()
{

}

Spawner::Spawner() :
	_init{ false },
	_health{ 10 },
	_spawntype{ 0 },
	_timerSpawn{ -1.0 },
	_timerCooldownSpawn{ 20 }
{
}


void Spawner::Init()
{
	//Spawn();
}

void Spawner::Update(double dt)
{
	if (!_init)
	{
		Init();
		_init = true;
	}
	_timerSpawn -= dt;
	if (_timerSpawn <= 0)
		Spawn();
}

void Spawner::Spawn()
{
	_timerSpawn = _timerCooldownSpawn;
	GameObject* enemy = nullptr;
	switch (_spawntype)
	{
	case 1:
		enemy = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(
			EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()["Enemy"]);
		break;
	case 2:
		enemy = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(
			EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()["EnemyTwo"]);
		break;
	case 3:
		enemy = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(
			EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()["EnemyThree"]);
		break;
	default:
		return;
	}
	((TransformComponent*)enemy->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetPos(
		((TransformComponent*)(GetSibilingComponent(ComponentId::TRANSFORM_COMPONENT)))->GetPos());
}
