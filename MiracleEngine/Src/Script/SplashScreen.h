#pragma once
#include "GameObject/Components/Logic/IScript2.h"


class SplashScreen : public IScript2
{
private:
	std::vector<int> _splashObjectLinkId;
	std::vector<GameObject*> _splashObject;
	std::vector<float> _splashObjectDuration;

	int _totalSplash;
	int _currSplash;
	double _timer;
public:
	void SerialiseComponent(Serialiser& document);
	void DeSerialiseComponent(DeSerialiser& prototypeDoc);

	virtual void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator);

	virtual void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator);

	void Inspect();

	SplashScreen();
	SplashScreen* Clone();

	void Init();
	void LoadResource();
	void Update(double dt);
};

