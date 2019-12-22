#pragma once



class CameraComponent: public IComponent
{
private:
	float _movespeed;
	float _xZoom;
    float _yZoom;
public:
	//Constructor
	CameraComponent(GameObject* parent = nullptr, size_t uId = 0, IComponent* component = nullptr);

	void SerialiseComponent(Serialiser& document) override;
	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override;
	std::string ComponentName() const override;
	virtual void Inspect() override;


public:
	void SetMoveSpeed(float num);

	void SetxZoom(float num);

	void SetyZoom(float num);

};
