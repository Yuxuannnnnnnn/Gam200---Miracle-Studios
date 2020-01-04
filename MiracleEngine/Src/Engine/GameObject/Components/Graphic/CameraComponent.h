#pragma once



class CameraComponent: public IComponent
{
private:
	bool _isCurrentCamera;


public:
	//Constructor
	CameraComponent(GameObject* parent = nullptr, size_t uId = 0, IComponent* component = nullptr);

	void SerialiseComponent(Serialiser& document) override
	{

	}

	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override
	{

	}

	std::string ComponentName() const override;

	virtual void Inspect() override
	{
		IComponent::Inspect();
	}
	void DeserialiseComponentSceneFile(IComponent* protoCom, DeSerialiser& SceneFile) { return; }



};

