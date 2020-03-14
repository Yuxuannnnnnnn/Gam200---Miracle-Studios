#pragma once
#include "GameObject/Components/Logic/IScript2.h"


class ButtonController : public IScript2
{
private:
	int _currScene;

	int _loadingLinkId;

	IScript2* _pauseMenu;

	GameObject* _LoadingObj;
public:
	void SerialiseComponent(Serialiser& document);
	void DeSerialiseComponent(DeSerialiser& prototypeDoc);
	virtual void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator);
	virtual void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator);

	void Inspect();

	ButtonController();
	ButtonController* Clone();

	void Init();
	void LoadResource();
	void Update(double dt);
};

