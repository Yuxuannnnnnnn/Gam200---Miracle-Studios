#pragma once
#include "GameObject/Components/Logic/IScript2.h"


class LoadingScreen : public IScript2
{
private:
	std::string _FileName;
	int _LoadingTextLinkId;

	GameObject* _cursorObj;

	bool _playerExist;
	IScript2* _player;

	bool _secondImage;
	std::string _FileName2;

	bool _panning;
	CameraComponent* _playerCamera;
	int _panningCameraLinkId;
	CameraComponent* _camera;
	TransformComponent* _cameraTransform;
	Vector3 _startPosition;
	Vector3 _endPosition;
	Vector3 _moveSpeed; // _endPosition - _startPosition * 0.01;

	float _startZoom;
	float _endZoom;
	float _zoomSpeed; // _endZoom - _startZoom * 0.01;

	float _panningSpeed;
	bool _panningComleted;

	bool _loadingCompleted;

	int _victoryTextLinkId;

	std::string _nextScene;
	
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

	void StartLoading(std::string nextScene);
};

