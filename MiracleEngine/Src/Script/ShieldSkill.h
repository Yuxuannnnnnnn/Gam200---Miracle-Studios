#pragma once
#include "GameObject/Components/Logic/IScript2.h"


class ShieldSkill : public IScript2
{
private:
	double _timer;
	double _animTimer;

	AnimationComponent* _animation;
	TransformComponent* _obj;
	TransformComponent* _player;
	AudioComponent* _audcom;
public:
	void SerialiseComponent(Serialiser& document);
	void DeSerialiseComponent(DeSerialiser& prototypeDoc);

	virtual void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator);

	virtual void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator);

	void Inspect();

	ShieldSkill();
	ShieldSkill* Clone();

	void Init();
	void LoadResource();
	void Update(double dt);

	void ActionShield(double skilltimer);
};

