#pragma once
#include "../../IComponent.h"
#include "Tools/MathLib/Math.h"

class TransformComponent : public IComponent
{
private:
	Vector3 _pos;	//Z value will be the renderlayer value, min 0, max 10 
	Vector3 _scale;
	float _rotationAngle;
	Vector3 _pivotPoint;

	Vector3 _localPos;
	Vector3 _localScale;
	float _localRotationAngle;
	Vector3 _localPivotPoint;

	Matrix4x4 _model;

	bool _localInspect;
public:

	TransformComponent();
	TransformComponent(const Vector3& pos, const Vector3& scale, const float& angle);
	TransformComponent* CloneComponent() { return new TransformComponent(*this); }

	std::string ComponentName() const override;

	void SerialiseComponent(Serialiser& document) override;
	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override;
	void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator);
	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator);

	virtual void Inspect() override;
	virtual void Init() override;
	
	//////////////////////////////////////////////////////////////
	Vector3& GetPositionA() { return _pos; }
	Vector3& GetScaleA() { return _scale; }
	float& GetRotationA() { return _rotationAngle; }
	
	void SetPositionA(Vector3 in) { _pos = in; }
	void SetScaleA(Vector3 in) { _scale = in; }
	void SetRotationA(float in) { _rotationAngle = in; }

	//////////////////////////////////////////////////////////////


	void SetPivot(const Vector3& in);
	void SetPos(const Vector3& in);
	void SetScale(const Vector3& in);
	void SetRotate(const float& in, TransformComponent* parent = nullptr);

	void SetPivotByLocal(const Vector3& in);
	void SetPosByLocal(const Vector3& in);
	void SetScaleByLocal(const Vector3& in);
	void SetRotateByLocal(const float& in);


	Vector3 GetPivot();
	Vector3 GetPos();
	Vector3 GetScale();
	float& GetRotate();

	void UpdateLocalData();

	//////////////////////////////////////////////////////

	float* GetModel(); // for gzmo
	void SetModel(const float* in);

	float* GetMatrix(int layer = 1); // for graphic
	///////////////////////////////////////////////////////////////

	void MovePos(const Vector3& in);
	void MoveScale(const Vector3& in);
	void MoveRotate(TransformComponent* parent, const float& in);



};


