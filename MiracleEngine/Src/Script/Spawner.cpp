#include "PrecompiledHeaders.h"
#include "Script/Spawner.h"

Spawner::Spawner() :
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
	_light = _lightPrevState = false;
	GetSibilingComponentObject(Graphic)->SetFileName("Spawner_Platform_unlit.png");
}

void Spawner::LoadResource()
{
#ifdef LEVELEDITOR
	MyResourceManager.AddNewTexture2DResource({ "Spawner_Platform_unlit.png", MyResourceSystem.GetTexture2DResourcePath("Spawner_Platform_unlit.png") });
	MyResourceManager.AddNewTexture2DResource({ "Spawner_Platform_lit.png", MyResourceSystem.GetTexture2DResourcePath("Spawner_Platform_lit.png") });

	MyResourceManager.AddNewPrototypeResource({ "Enemy" , MyResourceSystem.GetPrototypeResourcePath("Enemy") });
	MyResourceManager.AddNewPrototypeResource({ "EnemyTwo" , MyResourceSystem.GetPrototypeResourcePath("EnemyTwo") });
#endif
}

void Spawner::Update(double dt)
{
	if (dt < 0)
		return;

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
			GetSibilingComponentObject(Graphic)->SetFileName("Spawner_Platform_lit.png");
		else
			GetSibilingComponentObject(Graphic)->SetFileName("Spawner_Platform_unlit.png");
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
		enemy = CreateObject("Enemy");
		break;
	case 2:
		enemy = CreateObject("EnemyTwo");
		break;
	default:
		return;
	}
	GetComponentObject(enemy,Transform)->SetPos(GetSibilingComponentObject(Transform)->GetPos());
}

void Spawner::SerialiseComponent(Serialiser& document)
{
	if (document.HasMember("Health") && document["Health"].IsInt())
		_health = _healthMax = document["Health"].GetInt();

	if (document.HasMember("SpawnType") && document["SpawnType"].IsInt())
		_spawnType = document["SpawnType"].GetInt();

	if (document.HasMember("SpawnCooldown") && document["SpawnCooldown"].GetDouble())
		_timerSpawn = _timerSpawnCooldown = document["SpawnCooldown"].GetDouble();

	if (document.HasMember("LightDuration") && document["LightDuration"].GetDouble())
		_timerLightDuration = document["LightDuration"].GetDouble();

	if (document.HasMember("SpawnAmount") && document["SpawnAmount"].IsInt())
		_spawnAmount = document["SpawnAmount"].GetInt();
}

//Function Not needed for Scripts
void Spawner::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{
	//rapidjson::Value value;
	//prototypeDoc.AddMember("Script2Data", rapidjson::Value(true));
	//value.SetArray();
	//{
	//	rapidjson::Value object;
	//	object.SetObject();
	//	object.AddMember("Health", rapidjson::Value(_healthMax), prototypeDoc.Allocator());
	//	object.AddMember("SpawnType", rapidjson::Value(_spawnType), prototypeDoc.Allocator());
	//	object.AddMember("SpawnCooldown", rapidjson::Value(_timerSpawnCooldown), prototypeDoc.Allocator());
	//	object.AddMember("LightDuration", rapidjson::Value(_timerLightDuration), prototypeDoc.Allocator());
	//	object.AddMember("SpawnAmount", rapidjson::Value(_spawnAmount), prototypeDoc.Allocator());
	//	value.PushBack(object, prototypeDoc.Allocator());
	//}
}

void Spawner::DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator)
{
	rapidjson::Value value;

	value.SetString(rapidjson::StringRef(ToScriptName(_type)));
	prototypeDoc.AddMember("Script2Id", value, allocator);

	value.SetInt(_healthMax);
	prototypeDoc.AddMember("Health", value, allocator);

	value.SetInt(_spawnType);
	prototypeDoc.AddMember("SpawnType", value, allocator);

	value.SetDouble(_timerSpawnCooldown);
	prototypeDoc.AddMember("SpawnCooldown", value, allocator);

	value.SetDouble(_timerLightDuration);
	prototypeDoc.AddMember("LightDuration", value, allocator);

	value.SetInt(_spawnAmount);
	prototypeDoc.AddMember("SpawnAmount", value, allocator);

}


void Spawner::DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
{
	Spawner* script = GetScriptByLogicComponent(dynamic_cast<LogicComponent*>(protoCom), Spawner);

	if (!script)
	{
		DeSerialiseComponent(value, allocator);
		return;
	}

	rapidjson::Value Health;
	rapidjson::Value SpawnType;
	rapidjson::Value SpawnCooldown;
	rapidjson::Value LightDuration;
	rapidjson::Value SpawnAmount;

	bool addComponentIntoSceneFile = false;

	if (script->_healthMax != _healthMax)
	{
		addComponentIntoSceneFile = true;
		Health.SetInt(_healthMax);
	}

	if (script->_spawnType != _spawnType)
	{
		addComponentIntoSceneFile = true;
		SpawnType.SetInt(_spawnType);
	}

	if (script->_timerSpawnCooldown != _timerSpawnCooldown)
	{
		addComponentIntoSceneFile = true;
		SpawnCooldown.SetDouble(_timerSpawnCooldown);
	}

	if (script->_timerLightDuration != _timerLightDuration)
	{
		addComponentIntoSceneFile = true;
		LightDuration.SetDouble(_timerLightDuration);
	}

	if (script->_spawnAmount != _spawnAmount)
	{
		addComponentIntoSceneFile = true;
		SpawnAmount.SetInt(_spawnAmount);
	}


	if (addComponentIntoSceneFile)	//If anyone of component data of obj is different from Prototype
	{
		rapidjson::Value scriptName;

		scriptName.SetString(rapidjson::StringRef(ToScriptName(_type)));
		value.AddMember("Script2Id", scriptName, allocator);

		if (!Health.IsNull())	//if rapidjson::value container is not empty
		{
			value.AddMember("Health", Health, allocator);
		}

		if (!SpawnType.IsNull())	//if rapidjson::value container is not empty
		{
			value.AddMember("SpawnType", SpawnType, allocator);
		}

		if (!SpawnCooldown.IsNull())	//if rapidjson::value container is not empty
		{
			value.AddMember("SpawnCooldown", SpawnCooldown, allocator);
		}

		if (!LightDuration.IsNull())	//if rapidjson::value container is not empty
		{
			value.AddMember("LightDuration", LightDuration, allocator);
		}

		if (!SpawnAmount.IsNull())	//if rapidjson::value container is not empty
		{
			value.AddMember("SpawnAmount", SpawnAmount, allocator);
		}
	}

}
void Spawner::Inspect()
{
	ImGui::Spacing();
	ImGui::InputInt("Health ", &_health);
	ImGui::Spacing();
	ImGui::InputInt("SpawnType ", &_spawnType);
	ImGui::Spacing();
	ImGui::InputDouble("SpawnCooldown ", &_timerSpawnCooldown);
	ImGui::Spacing();
	ImGui::InputDouble("LightDuration ", &_timerLightDuration);
	ImGui::Spacing();
	ImGui::InputInt("SpawnAmount ", &_spawnAmount);
	ImGui::Spacing();
}