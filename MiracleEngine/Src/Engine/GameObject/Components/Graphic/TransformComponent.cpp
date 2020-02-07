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

TransformComponent::TransformComponent(GameObject* parent, size_t uId, IComponent* component)
	:IComponent(parent, uId),
	_pos{ Vector3{ 0, 0, 1} },
	_scale{ Vector3{ 100, 100, 1 } },
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



Vector3 TransformComponent::GetPos()
{
	return Vector3{ _pos._x * MyWindowsSystem.getWindow().GetWindowWidthRatio(),_pos._y * MyWindowsSystem.getWindow().GetWindowHeightRatio(),1.f } ;
}

void TransformComponent::SetPos(const Vector3& in)
{

	if (this->GetParentPtr()->GetChild())
	{
		Vec3 temp = in - _pos;

		for (auto& it : this->GetParentPtr()->GetChildList())
		{
			TransformComponent* child = (TransformComponent*)GetComponentMap(Transform)[it.first];

			if (!child)
				continue;

			child->MovePos(temp);
		}
	}

	_pos = in;
}

Vector3 TransformComponent::GetScale()
{
	return Vector3{ _scale._x * MyWindowsSystem.getWindow().GetWindowWidthRatio(),_scale._y * MyWindowsSystem.getWindow().GetWindowHeightRatio(),1.f };
}

void TransformComponent::SetScale(const Vector3& in)
{
	if (this->GetParentPtr()->GetChild())
	{
		Vec3 temp = in / _scale;

		for (auto& it : this->GetParentPtr()->GetChildList())
		{
			TransformComponent* child = (TransformComponent*)GetComponentMap(Transform)[it.first];

			if (!child)
				continue;

			child->MoveScale(temp);
		}
	}

	_scale = in;
}

float& TransformComponent::GetRotate()
{
	return _rotationAngle;
}

void TransformComponent::SetRotate(const float& in)
{
	if (this->GetParentPtr()->GetChild())
	{
		float temp = in - _rotationAngle;

		for (auto& it : this->GetParentPtr()->GetChildList())
		{
			TransformComponent* child = (TransformComponent*)GetComponentMap(Transform)[it.first];

			if (!child)
				continue;

			Vec3 diff = child->_pos - this->_pos;
			float mag = diff.Length();
			float deg = atan2(diff._y, diff._x) + temp;

			Vec3 temp2{ mag * cos(deg), mag * sin(deg) };

			temp2 -= diff;

			child->MovePos(temp2);

			child->MoveRotate(temp);
		}
	}

	_rotationAngle = in;
}

float* TransformComponent::GetModel()
{
	// calculate model matrix = TRS
	Mtx44 translate = Mtx44::CreateTranslation(GetPos());
	_model = translate * Mtx44::CreateRotationZ(-_rotationAngle) * Mtx44::CreateScale(GetScale());

	/*glm::mat4 model = translate * rotate * glm::scale(glm::mat4(1.0f),
		glm::vec3(transformComp->GetScale()._x, transformComp->GetScale()._y, 1.0f));*/


	return _model.m;
}

float* TransformComponent::GetMatrix(int layer)
{
	// calculate model matrix = TRS
	Mtx44 translate = Mtx44::CreateTranslation(Vec3{ GetPos()._x,GetPos()._y, (float)layer});
	_model = translate * Mtx44::CreateRotationZ(-_rotationAngle) * Mtx44::CreateScale(GetScale());

	/*glm::mat4 model = translate * rotate * glm::scale(glm::mat4(1.0f),
		glm::vec3(transformComp->GetScale()._x, transformComp->GetScale()._y, 1.0f));*/


	return _model.m;
}

void TransformComponent::SetModel(const float* in)
{
	_model = in;
}


void TransformComponent::Inspect()
{
	ImGui::Spacing();

	Vec3 tempPos = _pos;

	ImGui::InputFloat2("Input Pos X, Y", tempPos.m);
	ImGui::Spacing();
	ImGui::SliderFloat2("Slider Pos X, Y", tempPos.m, -1000, 1000);

	SetPos(tempPos);

	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();

	Vec3 tempScale = _scale;

	ImGui::InputFloat2("Input Scale X, Y", tempScale.m);
	ImGui::Spacing();
	ImGui::SliderFloat2("Slider Scale X, Y", tempScale.m, 1, 500);

	SetScale(tempScale);

	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();

	float DegAngle = RadToDeg(_rotationAngle);

	ImGui::InputFloat("Input Rotation Angle", &DegAngle);
	ImGui::Spacing();
	ImGui::SliderFloat("Slider Rotation Angle", &DegAngle, -180, 180);
	ImGui::Spacing();

	SetRotate(DegToRad(DegAngle));
}

///////////////////////////////////////////////////////////////

void TransformComponent::MovePos(const Vector3& in)
{
	if (GetParentPtr()->GetChild())
		SetPos(_pos + in);
	else
		_pos += in;
}

void TransformComponent::MoveScale(const Vector3& in)
{
	_scale *= in;
}

void TransformComponent::MoveRotate(const float& in)
{
	if (GetParentPtr()->GetChild())
		SetRotate(_rotationAngle + in);
	else
	_rotationAngle += in;
}

void TransformComponent::Init()
{
	if (_init)
		return;

	if (GetParentPtr()->GetChild())
		for (auto& it : GetParentPtr()->GetChildList())
			it.second->GetComponent(ComponentId::CT_Transform)->Init();

	SetPos(_localPos);
	SetRotate(_localRotationAngle);

	_init = true;
}