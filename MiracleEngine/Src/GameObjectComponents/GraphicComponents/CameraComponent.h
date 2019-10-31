#pragma once



class CameraComponent: public IComponentSystem
{
public:
	void SetMoveSpeed(int num)
	{
		_movespeed = num;
	}
	void SetZoomRatio(int num)
	{
		_zoomratio = num;
	}
private:
	int _movespeed;
	int _zoomratio;
};

