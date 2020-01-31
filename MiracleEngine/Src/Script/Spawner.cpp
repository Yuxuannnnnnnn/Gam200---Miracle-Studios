#include "PrecompiledHeaders.h"
#include "Script/Spawner.h"

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

Spawner* Spawner::Clone()
{
	return new Spawner(*this);
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
	// reset timer for spawning
	_timerSpawn = _timerCooldownSpawn;
	
	// add code for rng spawning if want to

	// spawn enemy based on _spawntype
	GameObject* enemy = nullptr;
	switch (_spawntype)
	{
	case 1:
		enemy = MyFactory.CloneGameObject(MyResourceSystem.GetPrototypeMap()["Enemy"]);
		break;
	case 2:
		break;
	case 3:
		break;
	default:
		return;
	}

	// set enemy to position of the spawner
	((TransformComponent*)enemy->GetComponent(ComponentId::CT_Transform))->SetPos(
		((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetPos());
}
