#include "PrecompiledHeaders.h"

std::string TransformComponent::ComponentName() const
{
	return "Transform Component";
}


void TransformComponent::SerialiseComponent(Serialiser& document)
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

//void TransformComponent::SerialiseComponentFromLevelFile(rapidjson::Value& document)
//{
//	if (document.HasMember("Position"))	//Checks if the variable exists in .Json file
//	{
//		_pos = Vector3{ document["Position"][0].GetFloat(), document["Position"][1].GetFloat(), 1 };
//	}
//
//	if (document.HasMember("Scale"))
//	{
//		_scale = Vector3{ document["Scale"][0].GetFloat(), document["Scale"][1].GetFloat(), 1 };
//	}
//
//	if (document.HasMember("Rotate"))	//Checks if the variable exists in .Json file
//	{
//		_rotationAngle = (document["Rotate"].GetFloat());
//	}
//}

void TransformComponent::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{
	rapidjson::Value value;

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



void TransformComponent::Inspect()
{	
	ImGui::Spacing();
	ImGui::InputFloat3("Input Position X, Y, Z", _pos.m);
	ImGui::Spacing();
	ImGui::SliderFloat3("Slider Position X, Y, Z", _pos.m, -700, 700);
	
	ImGui::Spacing();
	ImGui::InputFloat3("Input Scale X, Y, Z", _scale.m);
	ImGui::Spacing();
	ImGui::SliderFloat3("Slider Scale X, Y, Z", _scale.m, 0, 100);
	
	ImGui::Spacing();
	ImGui::InputFloat("Input Rotation Angle", &_rotationAngle);
	ImGui::Spacing();
	ImGui::SliderFloat("Slider Rotation Angle", &_rotationAngle, 0, 360);
	ImGui::Spacing();

}



TransformComponent::TransformComponent(GameObject* parent, size_t uId, IComponentSystem* component)
	:IComponentSystem(parent, uId),
	_pos{ Vector3{ 0, 0, 0 } },
	_scale{ Vector3{ 1, 1, 1 } },
	_rotationAngle{ 0.0f }
{
	if (component)
	{
		TransformComponent* transformComponent = dynamic_cast<TransformComponent*>(component);
		_pos = transformComponent->_pos;
		_scale = transformComponent->_scale;
		_rotationAngle = transformComponent->_rotationAngle;
	}
}



Vector3& TransformComponent::GetPos()
{
	return _pos;
}

void TransformComponent::SetPos(const Vector3& in)
{
	_pos = in;
}

Vector3& TransformComponent::GetScale()
{
	return _scale;
}

void TransformComponent::SetScale(const Vector3& in)
{
	_scale = in;
}

float& TransformComponent::GetRotate()
{
	return _rotationAngle;
}

void TransformComponent::SetRotate(const float in)
{
	_rotationAngle = in;
}
