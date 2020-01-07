#include "PrecompiledHeaders.h"
#include "GameObject/Components/Logic/PrecompiledScriptType.h"

SpawnerTwo::SpawnerTwo() :
	_init{ false },
	_health{ 10 },
	_timer{ -1.0 },
	_timeCooldown{ 20 },
	_radiusSpawn{ 2.f }
	//_typeId{ TypeIdGO::SPAWNERTWO }
{
}


void SpawnerTwo::Init()
{
	//Spawn();
}

void SpawnerTwo::Update(double dt)
{
	if (!_init)
	{
		Init();
		_init = true;
	}
	_timer -= dt;
	if (_timer <= 0)
		Spawn();
}

void SpawnerTwo::Spawn()
{
	_timer = _timeCooldown;
	//std::cout << "Spawned!" << std::endl;
	GameObject* enemy = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(MyResourceSystem.GetPrototypeMap()["EnemyTwo"]);
	((TransformComponent*)enemy->GetComponent(ComponentId::CT_Transform))->SetPos(
		((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetPos());
}
