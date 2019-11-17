#pragma once


#ifndef CAMERACOMPONENT_H
#define	CAMERACOMPONENT_H


class CameraComponent: public IComponentSystem
{
private:
	int _movespeed;
	int _zoomratio;

public:
	//Constructor
	CameraComponent(GameObject* parent, size_t uId, IComponentSystem * component = nullptr);

	void SerialiseComponent(Serialiser& document) override;
	std::string ComponentName() const override;
	virtual void Inspect() override;


	void SetMoveSpeed(int num)
	{
		_movespeed = num;
	}
	void SetZoomRatio(int num)
	{
		_zoomratio = num;
	}
};

#endif