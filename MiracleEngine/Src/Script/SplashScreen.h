#pragma once
#include "GameObject/Components/Logic/IScript2.h"


class SplashScreen : public IScript2
{
private:
	double _ScreenDuration;
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

