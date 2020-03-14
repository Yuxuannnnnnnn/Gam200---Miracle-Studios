#pragma once
#include "GameObject/Components/Logic/IScript2.h"


class LoadingScreen : public IScript2
{
private:
	std::string _LoadingFileName;
	std::string _CompletedFileName;

	int _playerLinkId;
	int _continueLinkId;

	bool _loadingComplete;

	IScript2* _player;

	GameObject* _continueButton;
public:
	void SerialiseComponent(Serialiser& document);
	void DeSerialiseComponent(DeSerialiser& prototypeDoc);

	virtual void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator);

	virtual void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator);

	void Inspect();

	LoadingScreen();
	LoadingScreen* Clone();

	void Init();
	void LoadResource();
	void Update(double dt);
};

