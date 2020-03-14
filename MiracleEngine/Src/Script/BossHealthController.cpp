#include "PrecompiledHeaders.h"
#include "BossHealthController.h"

void BossHealthController::SerialiseComponent(Serialiser& document)
{
	if (document.HasMember("BH.MaxHealth") && document["BH.MaxHealth"].IsInt())	//Checks if the variable exists in .Json file
		_maxHealth = document["BH.MaxHealth"].GetInt();

	if (document.HasMember("BH.HealthLinkID") && document["BH.HealthLinkID"].IsArray())	//Checks if the variable exists in .Json file
		for (unsigned i = 0; i < document["BH.HealthLinkID"].Size(); i++)
		{
			if (document["BH.HealthLinkID"][i].IsInt())
				_hpBatteryLinkID.push_back(document["BH.HealthLinkID"][i].GetInt());
		}

}

void BossHealthController::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{
	
}

void BossHealthController::DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator)
{
	rapidjson::Value value;

	value.SetString(rapidjson::StringRef(ToScriptName(_type)));
	prototypeDoc.AddMember("Script2Id", value, allocator);

	value.SetInt(_maxHealth);
	prototypeDoc.AddMember("BH.MaxHealth", value, allocator);

	value.SetArray();
	for (unsigned i = 0; i < _hpBatteryLinkID.size(); i++)
		value.PushBack(rapidjson::Value(_hpBatteryLinkID[i]).Move(), allocator);

	prototypeDoc.AddMember("BH.HealthLinkID", value, allocator);
}

void BossHealthController::DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
{
	BossHealthController* script = GetScriptByLogicComponent(dynamic_cast<LogicComponent*>(protoCom), BossHealthController);

	if (!script)
	{
		DeSerialiseComponent(value, allocator);
		return;
	}

	rapidjson::Value MaxHealth;
	rapidjson::Value HealthLinkID;

	bool addComponentIntoSceneFile = false;

	if (script->_maxHealth != _maxHealth)
	{
		addComponentIntoSceneFile = true;
		MaxHealth.SetInt(_maxHealth);
	}
	bool changes = false;

	if (script->_hpBatteryLinkID.size() == _hpBatteryLinkID.size())
	{
		for (int i = 0; i < _hpBatteryLinkID.size(); ++i)
			if (script->_hpBatteryLinkID[i] != _hpBatteryLinkID[i])
			{
				changes = true;
				break;
			}
	}
	else
		changes = true;

	if (changes)
	{
		addComponentIntoSceneFile = true;
		HealthLinkID.SetArray();
		for (unsigned i = 0; i < _hpBatteryLinkID.size(); i++)
			HealthLinkID.PushBack(rapidjson::Value(_hpBatteryLinkID[i]).Move(), allocator);
	}



	if (addComponentIntoSceneFile)	//If anyone of component data of obj is different from Prototype
	{
		rapidjson::Value scriptName;

		scriptName.SetString(rapidjson::StringRef(ToScriptName(_type)));
		value.AddMember("Script2Id", scriptName, allocator);

		if (!MaxHealth.IsNull())	//if rapidjson::value container is not empty
		{
			value.AddMember("H.MaxHealth", MaxHealth, allocator);
		}

		if (!HealthLinkID.IsNull())	//if rapidjson::value container is not empty
		{
			value.AddMember("H.HealthLinkID", HealthLinkID, allocator);
		}
	}
}

void BossHealthController::Inspect()
{
	ImGui::Spacing();
	ImGui::InputInt("MaxHealth ", &_maxHealth);
	ImGui::Spacing();

	int temp = _maxHealth - _hpBatteryLinkID.size();

	if (temp > 0)
		for (unsigned i = 0; i < temp; i++)
			_hpBatteryLinkID.push_back(0);
	else if (temp < 0)
		for (; temp < 0; temp++)
			_hpBatteryLinkID.pop_back();

	for (unsigned i = 0; i < _maxHealth; i++)
	{
		ImGui::Spacing();
		std::string temp = std::string{ "Hp Link ID " }  +std::to_string(i);
		ImGui::InputInt(temp.c_str(), &_hpBatteryLinkID[i]);
		ImGui::Spacing();
	}
	ImGui::Spacing();
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
	for (unsigned i = 0; i < _hpBatteryLinkID.size(); i++)
		_hpBattery.push_back(MyFactory.GetLinkIDObject(_hpBatteryLinkID[i]));

	for (unsigned i = 0; i < _hpBattery.size(); i++)
		_hpBatteryGraphic.push_back((UIComponent*)_hpBattery[i]->GetComponent(ComponentId::CT_UI));

	_currHealth = _maxHealth;
}

void BossHealthController::LoadResource()
{
}

void BossHealthController::Update(double dt)
{
}

void BossHealthController::DecreaseHealth(int hit)
{
	unsigned i = _currHealth - hit;

	if (i < 0)
		i = 0;

	if (_currHealth < 0)
		_currHealth = 0;

	for (; i < _currHealth; i++)
		_hpBattery[i]->SetEnable(false);

	_currHealth -= hit;
}
