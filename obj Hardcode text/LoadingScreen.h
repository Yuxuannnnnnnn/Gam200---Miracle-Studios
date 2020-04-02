#pragma once
#include "GameObject/Components/Logic/IScript2.h"


class LoadingScreen : public IScript2
{
private:
	std::string _LoadingFileName;
	int _LoadingTextLinkId;

	GameObject* _cursorObj;

	bool _playerExist;
	IScript2* _player;

	bool _secondImage;
	std::string _LoadingFileName2;

	bool _panning;
	CameraComponent* _camera;
	Vector3 _startPosition;
	Vector3 _endPosition;
	float _startZoom;
	float _endZoom;
	float _panningSpeed;

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

	void StartLoading();
};

