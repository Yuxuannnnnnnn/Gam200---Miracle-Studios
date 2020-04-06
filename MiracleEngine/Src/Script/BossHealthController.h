#pragma once
#include "GameObject/Components/Logic/IScript2.h"

class BossHealthController : public IScript2
{
private:

	std::string _defaultBatteryPrototype;
	std::unordered_map<size_t, std::vector<GameObject*>> _HpStageBattery;
	std::map<size_t,size_t> _HpStageAmount;
	std::unordered_map<size_t, std::string> _HpStageFilename;
	std::unordered_map<size_t, bool> _HpStageEnable;

	int _maxHealth;
	int _deductedHealth;

	Vector3 _startPoistion;
	float _fullHPLength;

	int _HealthBarBaseLinkId;
	int _HealthBarTopLinkId;
public:

	void SerialiseComponent(Serialiser& document);
	void DeSerialiseComponent(DeSerialiser& prototypeDoc);

	virtual void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator);

	virtual void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator);


	void Inspect();

	BossHealthController();
	BossHealthController* Clone();

	void Init();
	void LoadResource();
	void Update(double dt);

	void DecreaseHealth(int hit = 1);

	void EnableHealthBar(bool enable);

};

