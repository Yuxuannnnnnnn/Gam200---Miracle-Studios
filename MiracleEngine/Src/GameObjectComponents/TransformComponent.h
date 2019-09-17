#pragma once
#include "MathLib/Vector3.h"
#include "IComponentSystem.h"

class TransformComponent: public IComponentSystem
{
private:
	Vector3 _pos{ Vector3{ 0, 0, 1 } };
	Vector3 _scale{ Vector3{ 0, 0, 1 } };
	float _rotationAngle{ 0.0f };

	Vector3 _transform{ Vector3{ 0, 0, 1 } };

public:
	TransformComponent();

	TransformComponent(const Vector3& pos, const Vector3& scale, const float& angle) :
		_pos{ pos }, _scale{ scale }, _rotationAngle{ angle }
	{

	}

	std::string ComponentName() const override
	{
		return "Transform Component";
	}
};

