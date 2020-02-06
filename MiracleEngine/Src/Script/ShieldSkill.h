#pragma once
#include "GameObject/Components/Logic/IScript2.h"


class ShieldSkill : public IScript2
{
private:
	bool _init;

	double _timer;
	double _animTimer;

	AnimationComponent* _animation;
	TransformComponent* _obj;
	TransformComponent* _player;
public:
	void SerialiseComponent(Serialiser& document);
	void DeSerialiseComponent(DeSerialiser& prototypeDoc);
	void Inspect();

	ShieldSkill();
	ShieldSkill* Clone();

	void Init() override;
	void Update(double dt);

	void ActionShield(double skilltimer);
};

