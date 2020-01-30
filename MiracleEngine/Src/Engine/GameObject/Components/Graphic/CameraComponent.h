#pragma once



class CameraComponent: public IComponent
{
private:
	bool _isCurrentCamera;
public:
	float _cameraZoom;

	//Constructor
	CameraComponent(GameObject* parent = nullptr, size_t uId = 0, IComponent* component = nullptr);

	void SerialiseComponent(Serialiser& document) override
	{

	}

	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override
	{
		rapidjson::Value value;

		value.SetBool(true);
		prototypeDoc.AddMember("CameraComponent", rapidjson::Value(true));

	}

	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
	{
		//value.AddMember("CameraComponent", rapidjson::Value(true), allocator);
	}


	std::string ComponentName() const override;

	virtual void Inspect() override;



	void DeserialiseComponentSceneFile(IComponent* protoCom, DeSerialiser& SceneFile) 
	{ 
	
	}


	CameraComponent* CloneComponent() { return new CameraComponent(*this); }


	void SetMainCamera(bool main);
};

