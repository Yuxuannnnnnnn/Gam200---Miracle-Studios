#pragma once



class CameraComponent: public IComponentSystem
{
private:
	float _movespeed;
	float _xZoom;
    float _yZoom;

public:
	//Constructor
	CameraComponent(GameObject* parent = nullptr, size_t uId = 0, IComponentSystem* component = nullptr);

	void SerialiseComponent(Serialiser& document) override;
	std::string ComponentName() const override;
	virtual void Inspect() override;


public:
	void SetMoveSpeed(int num)
	{
		_movespeed = num;
	}
	void SetxZoom(int num)
	{
		_xZoom = num;
	}
    void SetyZoom(int num)
	{
		_yZoom = num;
	}

};

