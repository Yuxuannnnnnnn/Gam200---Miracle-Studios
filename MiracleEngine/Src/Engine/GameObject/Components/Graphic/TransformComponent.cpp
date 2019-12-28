#include "PrecompiledHeaders.h"

std::string TransformComponent::ComponentName() const
{
	return "Transform Component";
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




void TransformComponent::Inspect()
{	
	ImGui::Spacing();
	ImGui::InputFloat3("Input Pos X, Y, Z", _pos.m);
	ImGui::Spacing();
	ImGui::SliderFloat3("Slider Pos X, Y, Z", _pos.m, -700, 700);
	
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



TransformComponent::TransformComponent(GameObject* parent, size_t uId, IComponent* component)
	:IComponent(parent, uId),
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

float* TransformComponent::GetModel()
{
	// calculate model matrix = TRS
	Mtx44 translate = Mtx44::CreateTranslation(_pos);
	_model = translate * Mtx44::CreateRotationZ(-_rotationAngle) * Mtx44::CreateScale(_scale);

	/*glm::mat4 model = translate * rotate * glm::scale(glm::mat4(1.0f),
		glm::vec3(transformComp->GetScale()._x, transformComp->GetScale()._y, 1.0f));*/


	return _model.m;
}

void TransformComponent::SetModel(const float* in)
{
	_model = in;
}