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

	virtual void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator);

	virtual void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator);

	void Inspect();

	ShieldSkill();
	ShieldSkill* Clone();

	void Init() override;
	void Update(double dt);

	void ActionShield(double skilltimer);
};

