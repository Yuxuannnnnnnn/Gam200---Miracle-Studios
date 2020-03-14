#pragma once
#include "GameObject/Components/Logic/IScript2.h"

class EntrancePortal : public IScript2
{
	std::string _closePortalFileName;
	std::string _openPortalFileName;

	std::string _nextScene;

	int _loadingLinkId;

	int _progressCount;
	int _KillCount;

	int _level;

	bool _clear;

	GraphicComponent* _graphicComponent;
	
	TransformComponent* _popUpPos;
	GameObject* _popUp;

	TransformComponent* _player;

	IScript2* _loadingScreen;

public:

	void SerialiseComponent(Serialiser& document);
	void DeSerialiseComponent(DeSerialiser& prototypeDoc);

	virtual void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator);

	virtual void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator);

	void Inspect();

	EntrancePortal();
	EntrancePortal* Clone();

	void Init();
	void LoadResource();
	void Update(double dt);

	void OpenPortal();

	virtual void OnTrigger2DEnter(Collider2D* other);

	void IncreaseKillCount(int kills = 0);

	void GoNextScene();
};

