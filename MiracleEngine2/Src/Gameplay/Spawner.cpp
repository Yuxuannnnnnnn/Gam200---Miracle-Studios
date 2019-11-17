#include "PrecompiledHeaders.h"
#include "../Engine/EngineSystems.h"
#include "../GameObjectComponents/LogicComponents/PrecompiledScriptType.h"

Spawner::Spawner() :
	_init{ false },
	_health{ 10 },
	_timer{ -1.0 },
	_timeCooldown{ 20 },
	_radiusSpawn{ 2.f },
	_typeId{ TypeIdGO::SPAWNER }
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
	_timer -= dt;
	if (_timer <= 0)
		Spawn();
}

void Spawner::Spawn()
{
	_timer = _timeCooldown;
	//std::cout << "Spawned!" << std::endl;
	GameObject* enemy = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()[TypeIdGO::ENEMY]);
	((TransformComponent*)enemy->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetPos(
		((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetPos());
}
