#pragma once
#include "../../IComponent.h"
#include "Tools/MathLib/Math.h"

class TransformComponent: public IComponent
{
private:
	Vector3 _pos;	//Z value will be the renderlayer value, min 0, max 10 
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
	void SerialiseComponent(Serialiser& document) override
	{
		if (document.HasMember("Position") && document["Position"].IsArray())	//Checks if the variable exists in .Json file
		{
			if (document["Position"][0].IsFloat() && document["Position"][1].IsFloat())	//Check the array values
				_pos = Vector3{ document["Position"][0].GetFloat(), document["Position"][1].GetFloat(), 1 };
		}

		if (document.HasMember("Scale") && document["Scale"].IsArray())
		{
			if (document["Scale"][0].IsFloat() && document["Scale"][1].IsFloat())	//Check the array values
				_scale = Vector3{ document["Scale"][0].GetFloat(), document["Scale"][1].GetFloat(), 1 };
		}

		if (document.HasMember("Rotate") && document["Rotate"].IsFloat())	//Checks if the variable exists in .Json file
		{
			_rotationAngle = (document["Rotate"].GetFloat());
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
		prototypeDoc.AddMember("Position", value);

		value.SetArray();
		value.PushBack(rapidjson::Value(_scale.GetX()).Move(), prototypeDoc.Allocator());
		value.PushBack(rapidjson::Value(_scale.GetY()).Move(), prototypeDoc.Allocator());
		prototypeDoc.AddMember("Scale", value);

		value.SetFloat(_rotationAngle);
		prototypeDoc.AddMember("Rotate", value);
	}

	void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator)
	{
		rapidjson::Value value;

		value.SetBool(true);
		prototypeDoc.AddMember("TransformComponent", rapidjson::Value(true), allocator);

		value.SetArray();
		value.PushBack(rapidjson::Value(_pos.GetX()).Move(), allocator);
		value.PushBack(rapidjson::Value(_pos.GetY()).Move(), allocator);
		prototypeDoc.AddMember("Position", value, allocator);

		value.SetArray();
		value.PushBack(rapidjson::Value(_scale.GetX()).Move(), allocator);
		value.PushBack(rapidjson::Value(_scale.GetY()).Move(), allocator);
		prototypeDoc.AddMember("Scale", value, allocator);

		value.SetFloat(_rotationAngle);
		prototypeDoc.AddMember("Rotate", value, allocator);
	}

	virtual void Inspect() override
	{
		ImGui::Spacing();
		ImGui::InputFloat2("Input Pos X, Y", _pos.m);
		ImGui::Spacing();
		ImGui::SliderFloat2("Slider Pos X, Y", _pos.m, -1000, 1000);

		ImGui::Spacing();
		ImGui::InputFloat3("Input Scale X, Y, Z", _scale.m);
		ImGui::Spacing();
		ImGui::SliderFloat2("Slider Scale X, Y, Z", _scale.m, 0, 100);

		ImGui::Spacing();
		ImGui::InputFloat("Input Rotation Angle", &_rotationAngle);
		ImGui::Spacing();
		ImGui::SliderFloat("Slider Rotation Angle", &_rotationAngle, 0, 360);
		ImGui::Spacing();

	}
	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
	{
		TransformComponent* protoTransformCom = dynamic_cast<TransformComponent*>(protoCom);

		bool addComponentIntoSceneFile = false;
		rapidjson::Value position;
		position.SetArray();
		rapidjson::Value scale;
		scale.SetArray();
		rapidjson::Value rotate;

		if (protoTransformCom->_pos != _pos)
		{
			addComponentIntoSceneFile = true;
			position.PushBack(rapidjson::Value(_pos._x), allocator);
			position.PushBack(rapidjson::Value(_pos._y), allocator);
			position.PushBack(rapidjson::Value(_pos._z), allocator);
		}

		if (protoTransformCom->_scale != _scale)
		{
			addComponentIntoSceneFile = true;
			scale.PushBack(rapidjson::Value(_pos._x), allocator);
			scale.PushBack(rapidjson::Value(_pos._y), allocator);
			scale.PushBack(rapidjson::Value(_pos._z), allocator);
		}		
		
		if (protoTransformCom->_rotationAngle != _rotationAngle)
		{
			addComponentIntoSceneFile = true;
			rotate.SetFloat(_rotationAngle);
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
		}
	}


// GetPID

	Vector3& GetPos();
	void SetPos(const Vector3& in);

	Vector3& GetScale();
	void SetScale(const Vector3& in);

	float& GetRotate();
	void SetRotate(const float in);

	float* GetModel();
	void SetModel(const float* in);

	IComponent* CloneComponent() { return nullptr; }
};

