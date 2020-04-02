#pragma once
#include "GameObject/Components/Logic/IScript2.h"


class LoadingCompletedScreen : public IScript2
{
private:
	std::string _CompletedFileName;
	int _CompletedTextLinkId;

	GameObject* _cursorObj;

	IScript2* _player;

	bool _secondImage;
	std::string _CompletedFileName2;

	bool _panning;
	CameraComponent* _camera;
	Vector3 _startPosition;
	Vector3 _endPosition;
	float _startZoom;
	float _endZoom;
	float _panningSpeed;

	int _victoryTextLinkId;
public:
	void SerialiseComponent(Serialiser& document);
	void DeSerialiseComponent(DeSerialiser& prototypeDoc);

	virtual void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator);

	virtual void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator);

	void Inspect();

	LoadingCompletedScreen();
	LoadingCompletedScreen* Clone();

	void Init();
	void LoadResource();
	void Update(double dt);
};