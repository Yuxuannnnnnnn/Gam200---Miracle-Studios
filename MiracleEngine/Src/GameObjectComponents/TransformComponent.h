#pragma once
#include "IComponentSystem.h"
#include "MathLib/SYMath.h"

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

	Vector3& GetPos()
	{ return _pos; }
	void SetPos(const Vector3& in)
	{ _pos = in; }
	Vector3& GetScale()
	{ return _scale; }
	void SetScale(const Vector3& in)
	{ _scale = in; }
	float& GetRotate()
	{ return _rotationAngle; }
	void SetRotate(const float in)
	{ _rotationAngle = in; }

	std::string ComponentName() const override
	{
		return "Transform Component";
	}
};

