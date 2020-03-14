#pragma once
#include "GameObject/Components/Logic/IScript2.h"

class BossHealthController : public IScript2
{
private:
	std::vector<int> _hpBatteryLinkID;
	std::vector<GameObject*> _hpBattery;
	std::vector<UIComponent*> _hpBatteryGraphic;

	int _maxHealth;
	int _currHealth;
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
};

