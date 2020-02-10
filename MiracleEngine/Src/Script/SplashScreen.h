#pragma once
#include "GameObject/Components/Logic/IScript2.h"


class SplashScreen : public IScript2
{
private:
	bool _init;

	double _ScreenDuration;
	double _timer;

	bool _once;
public:
	void SerialiseComponent(Serialiser& document);
	void DeSerialiseComponent(DeSerialiser& prototypeDoc);
	void Inspect();

	SplashScreen();
	SplashScreen* Clone();

	void Init() override;
	void Update(double dt);
};

