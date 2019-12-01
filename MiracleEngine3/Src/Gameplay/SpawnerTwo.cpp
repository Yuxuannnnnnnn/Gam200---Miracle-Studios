#include "PrecompiledHeaders.h"
#include "../Engine/EngineSystems.h"
#include "../GameObjectComponents/LogicComponents/PrecompiledScriptType.h"

SpawnerTwo::SpawnerTwo() :
	_init{ false },
	_health{ 10 },
	_timer{ -1.0 },
	_timeCooldown{ 20 },
	_radiusSpawn{ 2.f },
	_typeId{ TypeIdGO::SPAWNERTWO }
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
	GameObject* enemy = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()[TypeIdGO::ENEMYTWO]);
	((TransformComponent*)enemy->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetPos(
		((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetPos());
}