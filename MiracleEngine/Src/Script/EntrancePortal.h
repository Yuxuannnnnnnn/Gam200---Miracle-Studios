#pragma once
#include "GameObject/Components/Logic/IScript2.h"

class EntrancePortal : public IScript2
{
	std::string _closePortalFileName;
	std::string _openPortalFileName;

	std::string _nextScene;

	int _progressCount;

	bool _clear;
	GraphicComponent* _graphicComponent;
	IScript2* _playerScript;

	GameObject* _popUp;
	TransformComponent* _player;
	TransformComponent* _popUpPos;

	bool _init;

	int _KillCount;
public:

	void SerialiseComponent(Serialiser& document);
	void DeSerialiseComponent(DeSerialiser& prototypeDoc);

	virtual void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator);

	virtual void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator);

	void Inspect();

	EntrancePortal();
	EntrancePortal* Clone();

	virtual void Init() override;
	void Update(double dt);

	void OpenPortal();

	virtual void OnTrigger2DEnter(Collider2D* other);

	void IncreaseKillCount(int kills = 0);
};

