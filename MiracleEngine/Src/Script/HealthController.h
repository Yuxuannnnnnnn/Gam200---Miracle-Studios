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
	TransformComponent* _progressBar;

	float _maxProgressScale;

	float _progressPercent;
	int _maxHealth;
	int _currHealth;

	int _currColor;
public:

	void SerialiseComponent(Serialiser& document);
	void DeSerialiseComponent(DeSerialiser& prototypeDoc);

	virtual void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator);

	virtual void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator);


	void Inspect();

	HealthController();
	HealthController* Clone();

	virtual void Init() override;
	void Update(double dt);

	void DecreaseHealth(int hit = 1);
	void IncreaseHealth(int heal = 1);

	void IncreaseEXP(float exp = 0.01f);

	void UpdateHealthColor();
	void UpdateProgressBar();
};

