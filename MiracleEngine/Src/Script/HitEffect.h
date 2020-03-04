#pragma once
#include "GameObject/Components/Logic/IScript2.h"


class HitEffect : public IScript2
{
private:
	bool _init;

	AnimationComponent* _animation;
	TransformComponent* _obj;
	TransformComponent* _player;
public:
	void SerialiseComponent(Serialiser& document);
	void DeSerialiseComponent(DeSerialiser& prototypeDoc);

	virtual void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator);

	virtual void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator);


	void Inspect();

	HitEffect();
	HitEffect* Clone();

	void Init() override;
	void Update(double dt);

	void PlayHit();
};

