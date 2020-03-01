#pragma once
#include "../../IComponent.h"
#include "Tools/MathLib/Math.h"

class TransformComponent: public IComponent
{
private:
	Vector3 _pos;	//Z value will be the renderlayer value, min 0, max 10 
	Vector3 _scale;
	float _rotationAngle;

	Vector3 _localPos;
	Vector3 _localScale;
	float _localRotationAngle;

	Vector3 _pivotPoint;

	Vector3 _localPivotPoint;

	Matrix4x4 _model;
public:

	TransformComponent();

	TransformComponent(const Vector3& pos, const Vector3& scale, const float& angle);


	std::string ComponentName() const override;

	void SerialiseComponent(Serialiser& document) override;

	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override;

	void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator);

	virtual void Inspect() override;
	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator);

// GetPID

	Vector3& GetPositionA() { return _pos; }
	void SetPositionA(Vector3 in) { _pos = in; }
	float& GetRotationA() { return _rotationAngle; }
	void SetRotationA(float in) { _rotationAngle = in; }
	Vector3& GetScaleA() { return _scale; }
	void SetScaleA(Vector3 in) { _scale = in; }


	Vector3 GetPos();
	void SetPos(const Vector3& in);

	Vector3 GetPivot();
	void SetPivot(const Vector3& in);

	Vector3 GetScale();
	void SetScale(const Vector3& in);

	float& GetRotate();
	void SetRotate(const float& in, TransformComponent* parent = nullptr);

	float* GetModel(); // for gzmo
	void SetModel(const float* in);

	float* GetMatrix(int layer = 1); // for graphic

	TransformComponent* CloneComponent() { return new TransformComponent(*this); }

	//void SetPivotPointRotation(const float& in);

	///////////////////////////////////////////////////////////////

	void MovePos(const Vector3& in);
	void MoveScale(const Vector3& in);
	void MoveRotate(TransformComponent* parent, const float& in);

	virtual void Init() override;

};

