#include "PrecompiledHeaders.h"
#include "BossHealthController.h"

void BossHealthController::SerialiseComponent(Serialiser& document)
{
	if (document.HasMember("BH.HealthBatteryPrototype") && document["BH.HealthBatteryPrototype"].IsString())	//Checks if the variable exists in .Json file
		_defaultBatteryPrototype = document["BH.HealthBatteryPrototype"].GetString();

	if (document.HasMember("BH.HealthStage") && document["BH.HealthStage"].IsArray() &&
		document.HasMember("BH.HealthStageFilename") && document["BH.HealthStageFilename"].IsArray())	//Checks if the variable exists in .Json file
	{
		for (unsigned i = 0; i < document["BH.HealthStage"].Size(); i++)
		{
			if (document["BH.HealthStage"][i].IsInt())
				_HpStageAmount.insert({ i,document["BH.HealthStage"][i].GetInt() });

			if (document["BH.HealthStageFilename"][i].IsString())	//Checks if the variable exists in .Json file
				_HpStageFilename.insert({ i,document["BH.HealthStageFilename"][i].GetString() });

		}

	}

	if (document.HasMember("BH.startPoistion") && document["BH.startPoistion"].IsArray())	//Checks if the variable exists in .Json file
	{
		if (document["BH.startPoistion"][0].IsFloat() && document["BH.startPoistion"][1].IsFloat())	//Check the array values
			_startPoistion = Vector3{ document["BH.startPoistion"][0].GetFloat(), document["BH.startPoistion"][1].GetFloat(), 1 };

		if (document["BH.startPoistion"].Size() == 3)
			_startPoistion.SetZ(document["BH.startPoistion"][2].GetFloat());
	}

	if (document.HasMember("BH.fullHPLength") && document["BH.fullHPLength"].IsFloat())	//Checks if the variable exists in .Json file
		_fullHPLength = (document["BH.fullHPLength"].GetFloat());

	if (document.HasMember("BH.HealthBarBaseLinkId") && document["BH.HealthBarBaseLinkId"].IsInt())	//Checks if the variable exists in .Json file
		_HealthBarBaseLinkId = document["BH.HealthBarBaseLinkId"].GetInt();

	if (document.HasMember("BH.HealthBarTopLinkId") && document["BH.HealthBarTopLinkId"].IsInt())	//Checks if the variable exists in .Json file
		_HealthBarTopLinkId = document["BH.HealthBarTopLinkId"].GetInt();
}

void BossHealthController::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{
	
}

void BossHealthController::DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator)
{
	
}

void BossHealthController::DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
{
	
}

void BossHealthController::Inspect()
{
	
}

BossHealthController::BossHealthController()
{
}

BossHealthController* BossHealthController::Clone()
{
	return new BossHealthController(*this);
}

void BossHealthController::Init()
{
	_deductedHealth = 0;

	for (auto& it : _HpStageAmount)
	{
		std::vector<GameObject*> stageHealthBar;

		_maxHealth += it.first;

		float StageBatteryScale = _fullHPLength / it.second;

		for (int i = 0; i < it.second; i++)
		{
			GameObject* battery = CreateObject(_defaultBatteryPrototype);

			UIComponent* temp = GetComponentObject(battery, UI);
			temp->_layer -= it.first;
			temp->SetFileName(_HpStageFilename[it.first]);

			TransformComponent* temp2 = GetComponentObject(battery, Transform);
			temp2->SetScale({ StageBatteryScale,temp2->GetScaleA()._y, 1.f });
			temp2->SetPos({ _startPoistion._x + StageBatteryScale * (0.45f + i * 0.72f), _startPoistion._y, _startPoistion._z });

			stageHealthBar.push_back(battery);
		}

		_HpStageBattery.insert({ it.first, stageHealthBar });

		_HpStageEnable.insert({ it.first, true });
	}
}

void BossHealthController::LoadResource()
{
#ifdef LEVELEDITOR
	MyResourceManager.AddNewPrototypeResource({ _defaultBatteryPrototype , MyResourceSystem.GetPrototypeResourcePath(_defaultBatteryPrototype) });

	for (auto& it : _HpStageFilename)
		MyResourceManager.AddNewTexture2DResource({ it.second, MyResourceSystem.GetTexture2DResourcePath(it.second) });
#endif
	
}

void BossHealthController::Update(double dt)
{
}

void BossHealthController::DecreaseHealth(int hit)
{
	if (hit < 0)
		return;

	_deductedHealth += hit;

	int temp = _deductedHealth;

	int stage = 0;

	for (auto& it : _HpStageAmount)
	{
		if (!_HpStageEnable[it.first])
		{
			temp -= it.second;
			continue;
		}

		if (temp < it.second)
		{
			stage = it.first;
			break;
		}

		temp -= it.second;
	}

	for (int i = 0; i < _HpStageAmount.size(); i++)
	{
		if (stage > i)
		{
			if (_HpStageEnable[i])
			{
				for (int n = 0; n < _HpStageBattery[i].size(); n++)
					_HpStageBattery[i][n]->SetEnable(false);

				_HpStageEnable[i] = false;
			}
		}
		else
		{
			for (int n = _HpStageBattery[i].size() - 1; n >= 0; n--)
			{
				if (temp > 0)
				{
					_HpStageBattery[i][n]->SetEnable(false);
					temp--;
				}
				else
				{
					return;
				}
			}
		}
	}
}

void BossHealthController::EnableHealthBar(bool enable)
{
	GetLinkObject(_HealthBarBaseLinkId)->SetEnable(enable);
	GetLinkObject(_HealthBarTopLinkId)->SetEnable(enable);


	for (auto& it : _HpStageEnable)
	{
		if (it.second)
		{
			for (int n = 0; n < _HpStageBattery[it.first].size(); n++)
				_HpStageBattery[it.first][n]->SetEnable(enable);
		}
	}

	if (enable)
		DecreaseHealth(0);
}