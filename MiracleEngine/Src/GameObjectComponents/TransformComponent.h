#pragma once
#include "IComponentSystem.h"
#include "MathLib/Vector3.h"

class TransformComponent: public IComponentSystem
{
private:
	Vector3 _pos;
	Vector3 _scale;
	float _rotationAngle;

	Vector3 _transform;

public:
	TransformComponent() 
		:_pos{ Vector3{ 0, 0, 1 } }, 
		_scale{ Vector3{ 0, 0, 1 } }, 
		_rotationAngle{ 0.0f }, 
		_transform{ Vector3{ 0, 0, 1 } }
	{
	}

	TransformComponent(const Vector3& pos, const Vector3& scale, const float& angle) :
		_pos{ pos }, _scale{ scale }, _rotationAngle{ angle }
	{

	}

	std::string ComponentName() const override
	{
		return "Transform Component";
	}
};

