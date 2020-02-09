#pragma once
#include "GameObject/Components/Logic/IScript2.h"

class RegisterLink : public IScript2
{
private:
	bool _init;
public:

	void SerialiseComponent(Serialiser& document);
	void DeSerialiseComponent(DeSerialiser& prototypeDoc);
	void Inspect();

	RegisterLink();
	RegisterLink* Clone();

	virtual void Init() override;
	void Update(double dt);
};

