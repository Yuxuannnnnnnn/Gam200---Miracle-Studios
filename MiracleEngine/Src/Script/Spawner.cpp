#include "PrecompiledHeaders.h"
#include "Script/Spawner.h"

Spawner::Spawner() :
	_init{ false },
	_health{ 0 }, _healthMax{ 0 },
	_spawnType{ 0 },
	_spawnAmount{ 0 },

	_timerSpawn{ 0 }, _timerSpawnCooldown{ 10 },
	_timerLight{ 0 }, _timerLightDuration{ 0 },
	_light{ false }, _lightPrevState{ false }
{
}

Spawner* Spawner::Clone()
{
	return new Spawner(*this);
}

void Spawner::Init()
{
	_init = true;
	_light = _lightPrevState = false;
	((GraphicComponent*)GetParentPtr()->GetComponent(ComponentId::CT_Graphic))->SetFileName("Spawner_Platform_unlit.png");
}

void Spawner::Update(double dt)
{
	if (dt < 0)
		return;

	if (!_init)
		Init();

// spawn logic
	_timerSpawn -= dt;
	if (_timerSpawn <= 0)
		Spawn();

// lit unlit logic
	_timerLight -= dt;
	if (_timerLight < 0)
		_light = false;
	if (_light != _lightPrevState)
	{
		_lightPrevState = _light;
		if (!_light)
			((GraphicComponent*)GetParentPtr()->GetComponent(ComponentId::CT_Graphic))->SetFileName("Spawner_Platform_lit.png");
		else
			((GraphicComponent*)GetParentPtr()->GetComponent(ComponentId::CT_Graphic))->SetFileName("Spawner_Platform_unlit.png");
	}
}

void Spawner::Spawn()
{
	if (_spawnAmount <= 0)
	{
		_light = false;
		return;
	}

	_spawnAmount--;
	_light = true;
	_timerLight = _timerLightDuration;
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
