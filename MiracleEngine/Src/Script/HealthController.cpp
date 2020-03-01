#include "PrecompiledHeaders.h"
#include "HealthController.h"

void HealthController::SerialiseComponent(Serialiser& document)
{
	if (document.HasMember("H.MaxHealth") && document["H.MaxHealth"].IsInt())	//Checks if the variable exists in .Json file
		_maxHealth = document["H.MaxHealth"].GetInt();

	if (document.HasMember("H.HealthLinkID") && document["H.HealthLinkID"].IsArray())	//Checks if the variable exists in .Json file
		for (unsigned i = 0; i < document["H.HealthLinkID"].Size(); i++)
		{
			if (document["H.HealthLinkID"][i].IsInt())
				_hpBatteryLinkID.push_back(document["H.HealthLinkID"][i].GetInt());
		}

	if (document.HasMember("H.ProgressLinkID") && document["H.ProgressLinkID"].IsInt())	//Checks if the variable exists in .Json file
		_progressBarLinkID = document["H.ProgressLinkID"].GetInt();

	if (document.HasMember("H.ProgressScale") && document["H.ProgressScale"].IsFloat())	//Checks if the variable exists in .Json file
		_maxProgressScale = document["H.ProgressScale"].GetFloat();

	if (document.HasMember("H.GreenFileName") && document["H.GreenFileName"].IsString())
		_greenHealthFileName = document["H.GreenFileName"].GetString();

	if (document.HasMember("H.OrangeFileName") && document["H.OrangeFileName"].IsString())
		_orangeHealthFileName = document["H.OrangeFileName"].GetString();

	if (document.HasMember("H.RedFileName") && document["H.RedFileName"].IsString())
		_redHealthFileName = document["H.RedFileName"].GetString();
}

void HealthController::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{
	rapidjson::Value value;

	value.SetInt(_maxHealth);
	prototypeDoc.AddMember("H.MaxHealth", value);

	value.SetInt(_progressBarLinkID);
	prototypeDoc.AddMember("H.ProgressLinkID", value);

	value.SetFloat(_maxProgressScale);
	prototypeDoc.AddMember("H.ProgressScale", value);

	value.SetArray();
	for (unsigned i = 0; i < _hpBatteryLinkID.size(); i++)
		value.PushBack(rapidjson::Value(_hpBatteryLinkID[i]).Move(), prototypeDoc.Allocator());

	prototypeDoc.AddMember("H.HealthLinkID", value);

	value.SetString(rapidjson::StringRef(_greenHealthFileName.c_str()));
	prototypeDoc.AddMember("H.GreenFileName", value);

	value.SetString(rapidjson::StringRef(_orangeHealthFileName.c_str()));
	prototypeDoc.AddMember("H.OrangeFileName", value);

	value.SetString(rapidjson::StringRef(_redHealthFileName.c_str()));
	prototypeDoc.AddMember("H.RedFileName", value);
}

void HealthController::Inspect()
{
	static auto& graphicList = MyResourceSystem.GetTexture2DList();
	std::vector<const char*> list(graphicList.size());

	int i = 0;
	int select1 = 0;
	int select2 = 0;
	int select3 = 0;

	for (auto& graphicPair = graphicList.begin(); graphicPair != graphicList.end(); graphicPair++)
	{
		const char* ptr = graphicPair->first.c_str();
		list[i] = ptr;

		if (!strncmp(ptr, _greenHealthFileName.c_str(), 20))
			select1 = i;

		if (!strncmp(ptr, _orangeHealthFileName.c_str(), 20))
			select2 = i;

		if (!strncmp(ptr, _redHealthFileName.c_str(), 20))
			select3 = i;

		i++;
	}

	static ComboFilterState s1 = { select1, 0 };
	static char buf1[128];
	static ImGuiFunctions function;
	static bool op = false;
	static bool* open = &op;

	if (_greenHealthFileName.empty())
		strncpy(buf1, "type text here...", 18);
	else
		strncpy(buf1, _greenHealthFileName.c_str(), _greenHealthFileName.size());

	function.ComboFilter("Green Hp Texture", buf1, IM_ARRAYSIZE(buf1), list, (int)list.size(), s1, _greenHealthFileName, open);
	ImGui::Spacing();

	static ComboFilterState s2 = { select2, 0 };
	static char buf2[128];

	if (_orangeHealthFileName.empty())
		strncpy(buf2, "type text here...", 18);
	else
		strncpy(buf2, _orangeHealthFileName.c_str(), _orangeHealthFileName.size());

	function.ComboFilter("Orange Hp Texture", buf2, IM_ARRAYSIZE(buf2), list, (int)list.size(), s2, _orangeHealthFileName, open);
	ImGui::Spacing();

	static ComboFilterState s3 = { select3, 0 };
	static char buf3[128];

	if (_redHealthFileName.empty())
		strncpy(buf3, "type text here...", 18);
	else
		strncpy(buf3, _redHealthFileName.c_str(), _redHealthFileName.size());

	function.ComboFilter("Red Hp Texture", buf3, IM_ARRAYSIZE(buf3), list, (int)list.size(), s3, _redHealthFileName, open);
	ImGui::Spacing();

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
		std::string temp = std::string{ "Hp Link ID " }  + std::to_string(i);
		ImGui::InputInt(temp.c_str(), &_hpBatteryLinkID[i]);
		ImGui::Spacing();
	}
	ImGui::Spacing();
	ImGui::InputInt("Progress bar Link ID ", &_progressBarLinkID);
	ImGui::Spacing();

	ImGui::Spacing();
	ImGui::InputFloat("Progress bar Max Scale ", &_maxProgressScale);
	ImGui::Spacing();

}

HealthController::HealthController() :
	_greenHealthFileName{},
	_orangeHealthFileName{},
	_redHealthFileName{},
	_progressPercent{ 0.f },
	_maxProgressScale{0.f},
	_progressBarLinkID{ 0 },
	_maxHealth{ 0 },
	_currHealth{ 0 },
	_currColor{ 3 }
{
}

HealthController* HealthController::Clone()
{
	return new HealthController(*this);
}

void HealthController::Init()
{
	for (unsigned i = 0; i < _hpBatteryLinkID.size(); i++)
		_hpBattery.push_back(MyFactory.GetLinkIDObject(_hpBatteryLinkID[i]));

	for (unsigned i = 0; i < _hpBattery.size(); i++)
		_hpBatteryGraphic.push_back((UIComponent*)_hpBattery[i]->GetComponent(ComponentId::CT_UI));

	_progressBar = (TransformComponent*)MyFactory.GetLinkIDObject(_progressBarLinkID)->GetComponent(ComponentId::CT_Transform);

	_currHealth = _maxHealth;
	_currColor = 3;
}

void HealthController::Update(double dt)
{
	/*if (EngineSystems::GetInstance()._inputSystem->KeyDown(KeyCode::KEYB_O))
		DecreaseHealth();

	if (EngineSystems::GetInstance()._inputSystem->KeyDown(KeyCode::KEYB_I))
		IncreaseHealth();


	if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_U))
		IncreaseEXP();*/

}

void HealthController::DecreaseHealth(int hit)
{
	unsigned i = _currHealth - hit;

	if (i < 0)
		i = 0;

	if (_currHealth < 0)
		_currHealth = 0;

	for (; i < _currHealth; i++)
		_hpBattery[i]->SetEnable(false);

	_currHealth -= hit;

	if(_currHealth <= 0)
		MyFactory.ChangeScene("DefeatScene");

	UpdateHealthColor();
}

void HealthController::IncreaseHealth(int heal)
{
	if (_currHealth == _maxHealth)
		return;

	unsigned i = _currHealth;

	if (_currHealth + heal > _maxHealth)
		_currHealth = _maxHealth;
	else
		_currHealth += heal;

	for (; i < _currHealth ; i++)
		_hpBattery[i]->SetEnable(true);

	UpdateHealthColor();
}

void HealthController::UpdateHealthColor()
{
	if (_currHealth > 8)
	{
		if (_currColor == 3)
			return;

		for (unsigned i = 0; i < _currHealth; i++)
			_hpBatteryGraphic[i]->SetFileName(_greenHealthFileName);

		_currColor = 3;
	}
	else if (_currHealth > 4)
	{
		if (_currColor == 2)
			return;

		for (unsigned i = 0; i < _currHealth; i++)
			_hpBatteryGraphic[i]->SetFileName(_orangeHealthFileName);

		_currColor = 2;
	}
	else
	{
		if (_currColor == 1)
			return;

		for (unsigned i = 0; i < _currHealth; i++)
			_hpBatteryGraphic[i]->SetFileName(_redHealthFileName);

		_currColor = 1;
	}
}

void HealthController::IncreaseEXP(float exp)
{
	_progressPercent += exp;

	if (_progressPercent >= 1.f)
		_progressPercent = 0.001f;

	UpdateProgressBar();
}

void HealthController::UpdateProgressBar()
{
	_progressBar->SetScale(Vec3{ _progressPercent * _maxProgressScale, _progressBar->GetScale()._y, 1.f });
}