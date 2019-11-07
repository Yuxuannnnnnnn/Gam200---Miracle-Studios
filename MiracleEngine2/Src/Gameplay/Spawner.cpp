#include "PrecompiledHeaders.h"
#include "../Engine/EngineSystems.h"
#include "../GameObjectComponents/LogicComponents/PrecompiledScriptType.h"

Spawner::Spawner() :
	_typeId{ TypeIdGO::SPAWNER },
	_radiusSpawn{ 2.f },
	_timer{ -1.0 },
	_timeCooldown{ 20 },
	_health{ 10 },
	_init{ false }
{
}


void Spawner::Init()
{
	Spawn();
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
