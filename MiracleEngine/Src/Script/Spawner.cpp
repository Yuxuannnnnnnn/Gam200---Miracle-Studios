#include "PrecompiledHeaders.h"
#include "Script/Spawner.h"

Spawner::Spawner() :
	_init{ false },
	_health{ 0 },
	_spawnType{ 0 },
	_timerSpawn{ 0 },
	_timerSpawnCooldown{ 10 }
{
}

Spawner* Spawner::Clone()
{
	return new Spawner(*this);
}

void Spawner::Init()
{
	_init = true;
}

void Spawner::Update(double dt)
{
	if (!_init)
		Init();

	_timerSpawn -= dt;
	if (_timerSpawn <= 0)
		Spawn();
}

void Spawner::Spawn()
{
	// reset timer for spawning
	_timerSpawn = _timerSpawnCooldown;
	
	// add code for rng spawning if want to
	std::srand((unsigned)std::time(0));
	int random = 1 + std::rand() % 2;
	GameObject* enemy = nullptr;
	switch (_spawnType)
	{
	case 1:
		enemy = MyFactory.CloneGameObject(MyResourceSystem.GetPrototypeMap()["Enemy"]);
		break;
	case 2:
		enemy = MyFactory.CloneGameObject(MyResourceSystem.GetPrototypeMap()["EnemyTwo"]);
		break;
	default:
		return;
	}
	((TransformComponent*)enemy->GetComponent(ComponentId::CT_Transform))->SetPos(
		((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetPos());
}
