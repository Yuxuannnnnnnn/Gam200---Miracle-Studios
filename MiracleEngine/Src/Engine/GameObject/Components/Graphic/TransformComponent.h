#pragma once
#include "../../IComponent.h"
#include "Tools/MathLib/Math.h"

class TransformComponent: public IComponent
{
private:
	Vector3 _pos;
	Vector3 _scale;
	float _rotationAngle;

	Matrix4x4 _model;

public:
	TransformComponent(GameObject* parent, size_t uId, IComponent* component = nullptr);

	TransformComponent() 
		:_pos{ Vector3{ 0, 0, 1 } }, 
		_scale{ Vector3{ 0, 0, 1 } }, 
		_rotationAngle{ 0.0f }
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

	float* GetModel();
	void SetModel(const float* in);
};

