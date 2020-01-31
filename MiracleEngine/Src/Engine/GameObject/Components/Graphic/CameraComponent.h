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
		if (document.HasMember("isCurrentCamera"))
		{
			_isCurrentCamera = document["isCurrentCamera"].GetBool();

			SetMainCamera(_isCurrentCamera);
		}

		if (document.HasMember("cameraZoom"))
		{
			_cameraZoom = document["cameraZoom"].GetFloat();
		}
	}

	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override
	{
		rapidjson::Value value;

		value.SetBool(true);
		prototypeDoc.AddMember("isCurrentCamera", rapidjson::Value(true));

		value.SetFloat(_cameraZoom);
		prototypeDoc.AddMember("cameraZoom", value);
	}


	void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator)
	{
		rapidjson::Value value;

		value.SetBool(true);
		prototypeDoc.AddMember("isCurrentCamera", rapidjson::Value(true), allocator);

		value.SetFloat(_cameraZoom);
		prototypeDoc.AddMember("cameraZoom", value, allocator);
	}


	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
	{
		//value.AddMember("CameraComponent", rapidjson::Value(true), allocator);
		CameraComponent* protoTransformCom = dynamic_cast<CameraComponent*>(protoCom);

		bool addComponentIntoSceneFile = false;
		rapidjson::Value currentCamera;
		rapidjson::Value cameraZoom;

		if (protoTransformCom->_isCurrentCamera != _isCurrentCamera)
		{
			currentCamera.SetBool(_isCurrentCamera);
			addComponentIntoSceneFile = true;

		}

		if (protoTransformCom->_cameraZoom != _cameraZoom)
		{
			cameraZoom.SetFloat(_cameraZoom);
			addComponentIntoSceneFile = true;
		}


		if (addComponentIntoSceneFile)	//If anyone of component data of obj is different from Prototype
		{
			value.AddMember("CameraComponent", rapidjson::Value(true), allocator);

			if (!currentCamera.IsNull())	//if rapidjson::value container is not empty
			{
				value.AddMember("Position", currentCamera, allocator);
			}

			if (!cameraZoom.IsNull())
			{
				value.AddMember("Scale", cameraZoom, allocator);
			}
		}
	}


	std::string ComponentName() const override;

	virtual void Inspect() override;


	CameraComponent* CloneComponent() { return new CameraComponent(*this); }

	bool isMainCamera() const;

	void SetMainCamera(bool main);
};

