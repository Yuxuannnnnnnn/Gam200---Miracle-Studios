#pragma once



class CameraComponent: public IComponent
{
private:
	bool _isCurrentCamera;
public:
	float _cameraZoom;

	//Constructor
	CameraComponent(GameObject* parent = nullptr, size_t uId = 0, IComponent* component = nullptr);

	void SerialiseComponent(Serialiser& document) override;
	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override;
	void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator);
	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator);


	std::string ComponentName() const override;

	virtual void Inspect() override;

	void Init() override;


	CameraComponent* CloneComponent() { return new CameraComponent(*this); }

	bool isMainCamera() const;

	void SetMainCamera(bool main);
};

