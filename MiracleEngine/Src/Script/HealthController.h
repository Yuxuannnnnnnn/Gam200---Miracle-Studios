#pragma once
#include "GameObject/Components/Logic/IScript2.h"

class HealthController : public IScript2
{
private:
	std::string _greenHealthFileName;
	std::string _orangeHealthFileName;
	std::string _redHealthFileName;

	std::vector<int> _hpBatteryLinkID;
	std::vector<GameObject*> _hpBattery;
	std::vector<UIComponent*> _hpBatteryGraphic;

	int _progressBarLinkID;
	UIComponent* _progressBarUI;
	TransformComponent* _progressBar;

	std::string _progressBarYellow;
	std::string _progressBarBlue;

	float _maxProgressScale;
	float _progressTotalTime;
	float _progressCurrTime;

	int _maxHealth;
	int _currHealth;

	int _currColor;

	bool _progressCharge;
	bool _progressUse;
public:

	void SerialiseComponent(Serialiser& document);
	void DeSerialiseComponent(DeSerialiser& prototypeDoc);

	virtual void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator);

	virtual void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator);


	void Inspect();

	HealthController();
	HealthController* Clone();

	void Init();
	void LoadResource();
	void Update(double dt);

	void DecreaseHealth(int hit = 1);
	void IncreaseHealth(int heal = 1);

	void UseShield(float timer);
	void ChargeShield(float time);

	void UpdateHealthColor();
	void UpdateProgressBar();
};

