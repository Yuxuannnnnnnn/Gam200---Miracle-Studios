#pragma once



class CameraComponent: public IComponentSystem
{
private:
	int _movespeed;
	int _zoomratio;

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
	void SetZoomRatio(int num)
	{
		_zoomratio = num;
	}

};

