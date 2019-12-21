#pragma once
#include "GameObjectComponents/IComponent.h"
#include "MathLib/SYMath.h"

class TransformComponent: public IComponent
{
private:
	Vector3 _pos;
	Vector3 _scale;
	float _rotationAngle;

	Vector3 _transform;

public:
	TransformComponent(GameObject* parent, size_t uId, IComponent* component = nullptr);

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


	std::string ComponentName() const override;
	void SerialiseComponent(Serialiser& document) override;
	void SerialiseComponentFromLevelFile(rapidjson::Value& document);

	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override;
	virtual void Inspect() override;


// GetPID

	Vector3& GetPos();
	void SetPos(const Vector3& in);

	Vector3& GetScale();
	void SetScale(const Vector3& in);

	float& GetRotate();
	void SetRotate(const float in);
};

