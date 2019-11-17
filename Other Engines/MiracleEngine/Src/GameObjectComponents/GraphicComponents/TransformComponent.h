#pragma once
#include "GameObjectComponents/IComponentSystem.h"
#include "MathLib/SYMath.h"


#ifndef TRANSFORMCOMPONENT_H
#define	TRANSFORMCOMPONENT_H

class TransformComponent: public IComponentSystem
{
private:
	Vector3 _pos;
	Vector3 _scale;
	float _rotationAngle;

public:
	TransformComponent(GameObject* parent, size_t uId, IComponentSystem * component = nullptr);
	TransformComponent(GameObject* parent, size_t uId, const Vector3& pos, const Vector3& scale, const float& angle);


	std::string ComponentName() const override;
	void SerialiseComponent(Serialiser& document) override;
	virtual void Inspect() override;


// GetPID

	Vector3& GetPos();
	void SetPos(const Vector3& in);

	Vector3& GetScale();
	void SetScale(const Vector3& in);

	float& GetRotate();
	void SetRotate(const float in);


};

#endif



