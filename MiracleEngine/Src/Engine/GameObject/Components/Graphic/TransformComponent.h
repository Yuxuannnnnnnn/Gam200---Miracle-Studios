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

	TransformComponent(GameObject* parent, size_t uId, IComponent* component = nullptr);

	TransformComponent()
		:_pos{ Vector3{ 0, 0, 1 } },
		_scale{ Vector3{ 100, 100, 1 } },
		_rotationAngle{ 0.0f },
		_pivotPoint{ Vector3{ 0, 0, 1 } }
	{
	}

	TransformComponent(const Vector3& pos, const Vector3& scale, const float& angle) :
		_pos{ pos }, _scale{ scale }, _rotationAngle{ angle }, _pivotPoint{ pos }
	{

	}


	std::string ComponentName() const override;
	void SerialiseComponent(Serialiser& document) override
	{
		if (document.HasMember("Position" ) && document["Position" ].IsArray())	//Checks if the variable exists in .Json file
		{
			if (document["Position"][0].IsFloat() && document["Position" ][1].IsFloat())	//Check the array values
				_localPos = Vector3{ document[ "Position"][0].GetFloat(), document[ "Position" ][1].GetFloat(), 1};

			if (document["Position"].Size() == 3)
			{
				_localPos.SetZ(document["Position"][2].GetFloat());
			}
		}

		if (document.HasMember( "Scale") && document["Scale"].IsArray())
		{
			if (document["Scale"][0].IsFloat() && document["Scale"][1].IsFloat())	//Check the array values
				_scale = Vector3{ document["Scale"][0].GetFloat(), document["Scale"][1].GetFloat(), 1 };

			if (document["Scale"].Size() == 3)
			{
				_scale.SetZ(document["Scale"][2].GetFloat());
			}
		}

		if (document.HasMember("Rotate") && document["Rotate"].IsFloat())	//Checks if the variable exists in .Json file
		{
			_localRotationAngle = (document["Rotate"].GetFloat());
		}

		if (document.HasMember("PivotPosition") && document["PivotPosition"].IsArray())	//Checks if the variable exists in .Json file
		{
			if (document["PivotPosition"][0].IsFloat() && document["PivotPosition"][1].IsFloat())	//Check the array values
				_localPivotPoint = Vector3{ document["PivotPosition"][0].GetFloat(), document["PivotPosition"][1].GetFloat(), 1 };

			if (document["PivotPosition"].Size() == 3)
			{
				_localPivotPoint.SetZ(document["PivotPosition"][2].GetFloat());
			}
		}
	}

	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override
	{
		rapidjson::Value value;

		value.SetBool(true);
		prototypeDoc.AddMember("TransformComponent", rapidjson::Value(true));

		value.SetArray();
		value.PushBack(rapidjson::Value(_pos.GetX()).Move(), prototypeDoc.Allocator());
		value.PushBack(rapidjson::Value(_pos.GetY()).Move(), prototypeDoc.Allocator());
		value.PushBack(rapidjson::Value(_pos.GetZ()).Move(), prototypeDoc.Allocator());
		prototypeDoc.AddMember("Position", value);

		value.SetArray();
		value.PushBack(rapidjson::Value(_scale.GetX()).Move(), prototypeDoc.Allocator());
		value.PushBack(rapidjson::Value(_scale.GetY()).Move(), prototypeDoc.Allocator());
		value.PushBack(rapidjson::Value(_scale.GetZ()).Move(), prototypeDoc.Allocator());
		prototypeDoc.AddMember("Scale", value);

		value.SetFloat(_rotationAngle);
		prototypeDoc.AddMember("Rotate", value);

		value.SetArray();
		value.PushBack(rapidjson::Value(_pivotPoint.GetX()).Move(), prototypeDoc.Allocator());
		value.PushBack(rapidjson::Value(_pivotPoint.GetY()).Move(), prototypeDoc.Allocator());
		value.PushBack(rapidjson::Value(_pivotPoint.GetZ()).Move(), prototypeDoc.Allocator());
		prototypeDoc.AddMember("PivotPosition", value);
	}

	void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator)
	{
		rapidjson::Value value;

		value.SetBool(true);
		prototypeDoc.AddMember("TransformComponent", rapidjson::Value(true), allocator);

		value.SetArray();
		value.PushBack(rapidjson::Value(_pos.GetX()).Move(), allocator);
		value.PushBack(rapidjson::Value(_pos.GetY()).Move(), allocator);
		value.PushBack(rapidjson::Value(_pos.GetZ()).Move(), allocator);
		prototypeDoc.AddMember("Position", value, allocator);

		value.SetArray();
		value.PushBack(rapidjson::Value(_scale.GetX()).Move(), allocator);
		value.PushBack(rapidjson::Value(_scale.GetY()).Move(), allocator);
		value.PushBack(rapidjson::Value(_scale.GetZ()).Move(), allocator);
		prototypeDoc.AddMember("Scale", value, allocator);

		value.SetFloat(_rotationAngle);
		prototypeDoc.AddMember("Rotate", value, allocator);

		value.SetArray();
		value.PushBack(rapidjson::Value(_pivotPoint.GetX()).Move(), allocator);
		value.PushBack(rapidjson::Value(_pivotPoint.GetY()).Move(), allocator);
		value.PushBack(rapidjson::Value(_pivotPoint.GetZ()).Move(), allocator);
		prototypeDoc.AddMember("PivotPosition", value, allocator);
	}

	virtual void Inspect() override;
	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
	{
		TransformComponent* protoTransformCom = dynamic_cast<TransformComponent*>(protoCom);

		if (!protoTransformCom)
		{
			DeSerialiseComponent(value, allocator);
			return;
		}

		bool addComponentIntoSceneFile = false;
		rapidjson::Value position;
		rapidjson::Value scale;
		rapidjson::Value rotate;

		rapidjson::Value pivot;

		if (protoTransformCom->_pos != _pos)
		{
			position.SetArray();
			addComponentIntoSceneFile = true;
			position.PushBack(rapidjson::Value(_pos._x), allocator);
			position.PushBack(rapidjson::Value(_pos._y), allocator);
			position.PushBack(rapidjson::Value(_pos._z), allocator);
		}

		if (protoTransformCom->_scale != _scale)
		{
			scale.SetArray();
			addComponentIntoSceneFile = true;
			scale.PushBack(rapidjson::Value(_scale._x), allocator);
			scale.PushBack(rapidjson::Value(_scale._y), allocator);
			scale.PushBack(rapidjson::Value(_scale._z), allocator);
		}		
		
		if (protoTransformCom->_rotationAngle != _rotationAngle)
		{
			addComponentIntoSceneFile = true;
			rotate.SetFloat(_rotationAngle);
		}

		if (protoTransformCom->_pivotPoint != _pivotPoint)
		{
			pivot.SetArray();
			addComponentIntoSceneFile = true;
			pivot.PushBack(rapidjson::Value(_pivotPoint._x), allocator);
			pivot.PushBack(rapidjson::Value(_pivotPoint._y), allocator);
			pivot.PushBack(rapidjson::Value(_pivotPoint._z), allocator);
		}

		if (addComponentIntoSceneFile)	//If anyone of component data of obj is different from Prototype
		{
			value.AddMember("TransformComponent", rapidjson::Value(true), allocator);

			if (!position.IsNull())	//if rapidjson::value container is not empty
			{
				value.AddMember("Position", position, allocator);
			}

			if (!scale.IsNull())
			{
				value.AddMember("Scale", scale, allocator);
			}

			if (!rotate.IsNull())
			{
				value.AddMember("Rotate", rotate, allocator);
			}

			if (!pivot.IsNull())
			{
				value.AddMember("PivotPosition", pivot, allocator);
			}
		}
	}


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

	void SetPivotPointRotation(const float& in);

	///////////////////////////////////////////////////////////////

	void MovePos(const Vector3& in);
	void MoveScale(const Vector3& in);
	void MoveRotate(TransformComponent* parent, const float& in);

	virtual void Init() override;

};

