#pragma once
#include "GameObject/Components/Logic/IScript2.h"

class MouseCursor : public IScript2
{
	float _spinSpeed;
	TransformComponent* _transform;
public:

	void SerialiseComponent(Serialiser& document);
	void DeSerialiseComponent(DeSerialiser& prototypeDoc);
	void Inspect();

	MouseCursor();
	MouseCursor* Clone();

	virtual void Init() override;
	void Update(double dt);
};

