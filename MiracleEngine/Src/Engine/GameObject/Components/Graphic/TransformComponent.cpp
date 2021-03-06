#include "PrecompiledHeaders.h"

std::string TransformComponent::ComponentName() const
{
	return "Transform Component";
}


TransformComponent::TransformComponent()
	:_pos{ Vector3{ 0, 0, 1 } },
	_scale{ Vector3{ 1, 1, 1 } },
	_rotationAngle{ 0.0f },
	_pivotPoint{ Vector3{ 0, 0, 1 } },
	_localInspect{ true }
{
}

TransformComponent::TransformComponent(const Vector3& pos, const Vector3& scale, const float& angle) :
	_pos{ pos }, _scale{ scale }, _rotationAngle{ angle }, _pivotPoint{ pos }
{

}



void TransformComponent::SetPivot(const Vector3& in)
{
	Vec3 temp = Vector3{ in._x - _pivotPoint._x , in._y - _pivotPoint._y };

	if (this->GetParentPtr()->GetChild())
	{
		for (auto& it : this->GetParentPtr()->GetChildList())
		{
			TransformComponent* child = (TransformComponent*)GetComponentMap(Transform)[it.first];

			if (!child)
				continue;

			child->MovePos(temp);
		}
	}

	_pos += temp;
	_pivotPoint = in;

	if (temp != Vector3{ 0,0,0 })
	{
		if (TileMapComponent* tilemap = (TileMapComponent*)(GetSibilingComponent(ComponentId::CT_TileMap)))
		{
			tilemap->ResizeNodeMap();
		}
	}
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

	Vector3  OldPosition = _pos;

	_pivotPoint = _pivotPoint - _pos;
	_pos = in;
	_pivotPoint = _pos + _pivotPoint;


	if (OldPosition != _pos)
	{
		if (TileMapComponent* tilemap = (TileMapComponent*)(GetSibilingComponent(ComponentId::CT_TileMap)))
		{
			tilemap->ResizeNodeMap();
		}
	}
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

	Vector3  OldScale = _scale;

	_scale = in;

	if (OldScale != _scale)
	{
		if (TileMapComponent* tilemap = (TileMapComponent*)(GetSibilingComponent(ComponentId::CT_TileMap)))
		{
			tilemap->ResizeNodeMap();
		}
	}
}



void TransformComponent::SetRotate(const float& in, TransformComponent* parent)
{
	float temp = in - _rotationAngle;

	if (this->GetParentPtr()->GetChild())
	{
		for (auto& it : this->GetParentPtr()->GetChildList())
		{
			TransformComponent* child = (TransformComponent*)GetComponentMap(Transform)[it.first];

			if (!child)
				continue;

			child->MoveRotate(this, temp);
		}
	}

	Vec3 temp2;

	if (!parent)
	{
		Vec3 diff = _pos - _pivotPoint;
		diff._z = 0.f;
		float mag = diff.Length();
		float deg = atan2(diff._y, diff._x) + temp;
		temp2 = Vec3{ mag * cos(deg), mag * sin(deg) } -diff;
	}
	else
	{
		Vec3 diff = _pos - parent->_pos;
		diff._z = 0.f;
		float mag = diff.Length();
		float deg = atan2(diff._y, diff._x) + temp;
		temp2 = Vec3{ mag * cos(deg), mag * sin(deg) } -diff;
	}

	_pos += temp2;
	_rotationAngle = in;
}


void TransformComponent::SetPivotByLocal(const Vector3& in)
{
	_pivotPoint = in;
}

void TransformComponent::SetPosByLocal(const Vector3& in)
{
	if (this->GetParentPtr()->GetChild())
	{
		for (auto& it : this->GetParentPtr()->GetChildList())
		{
			TransformComponent* child = (TransformComponent*)GetComponentMap(Transform)[it.first];

			if (!child)
				continue;

			child->MovePos(in);
		}
	}

	_pos = in;
	_pivotPoint = _pivotPoint + _pos;
}

void TransformComponent::SetScaleByLocal(const Vector3& in)
{
	if (this->GetParentPtr()->GetChild())
	{
		for (auto& it : this->GetParentPtr()->GetChildList())
		{
			TransformComponent* child = (TransformComponent*)GetComponentMap(Transform)[it.first];

			if (!child)
				continue;

			child->MoveScale(in);
		}
	}

	_scale = in;
}

void TransformComponent::SetRotateByLocal(const float& in)
{
	if (this->GetParentPtr()->GetChild())
	{
		for (auto& it : this->GetParentPtr()->GetChildList())
		{
			TransformComponent* child = (TransformComponent*)GetComponentMap(Transform)[it.first];

			if (!child)
				continue;

			child->MoveRotate(this, in);
		}
	}

	_rotationAngle = in;
}


Vector3 TransformComponent::GetPos()
{
	return Vector3{ _pos._x * MyWindowsSystem.getWindow().GetWindowWidthRatio(),_pos._y * MyWindowsSystem.getWindow().GetWindowHeightRatio(),1.f };
}

Vector3 TransformComponent::GetPivot()
{
	return Vector3{ _pivotPoint._x * MyWindowsSystem.getWindow().GetWindowWidthRatio(),_pivotPoint._y * MyWindowsSystem.getWindow().GetWindowHeightRatio(),1.f };
}

Vector3 TransformComponent::GetScale()
{
	return Vector3{ _scale._x * MyWindowsSystem.getWindow().GetWindowWidthRatio(),_scale._y * MyWindowsSystem.getWindow().GetWindowHeightRatio(),1.f };
}

float& TransformComponent::GetRotate()
{
	return _rotationAngle;
}


void TransformComponent::UpdateLocalData()
{
	if (this->GetParentPtr()->GetIndependent())
	{
		_localPivotPoint = _pivotPoint;
		_localPos = _pos;
		_localScale = _scale;
		_localRotationAngle = _rotationAngle;
	}
	else
	{
		TransformComponent* parentTransform = GetComponentObject(this->GetParentPtr()->GetParent(), Transform);
	
		_localScale = _scale / parentTransform->_scale;
		_localRotationAngle = _rotationAngle - parentTransform->_rotationAngle;


		Vec3 diff = _pos - parentTransform->_pos;
		diff._z = 0.f;
		float mag = diff.Length();
		float deg = atan2(diff._y, diff._x) - (parentTransform->_rotationAngle - _localRotationAngle);
		Vector3 temp2 = Vec3{ mag * cos(deg), mag * sin(deg) } -diff;

		Vector3 temp = _pos + temp2;

		_localPos = temp - parentTransform->_pos;
		_localPos._z = 1.f;

		_localPivotPoint = _pivotPoint - parentTransform->_pos;
		_localPivotPoint._z = 2.f;
	}
}

float* TransformComponent::GetModel()
{
	// calculate model matrix = TRS
	Mtx44 translate = Mtx44::CreateTranslation(GetPivot());
	_model = translate * Mtx44::CreateRotationZ(-_rotationAngle) * Mtx44::CreateScale(GetScale());

	/*glm::mat4 model = translate * rotate * glm::scale(glm::mat4(1.0f),
		glm::vec3(transformComp->GetScale()._x, transformComp->GetScale()._y, 1.0f));*/


	return _model.m;
}

float* TransformComponent::GetMatrix(int layer)
{
	// calculate model matrix = TRS
	Mtx44 translate = Mtx44::CreateTranslation(Vec3{ GetPos()._x,GetPos()._y, (float)layer });
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

	ImGui::Checkbox("Inspect In Local Space", &_localInspect);

	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();

	if (_localInspect)
	{
		UpdateLocalData();

		ImGui::InputFloat2("Local Pos X, Y", _localPos.m);
		ImGui::Spacing();
		ImGui::InputFloat2("Local Scale X, Y", _localScale.m);
		ImGui::Spacing();

		float DegAngle = RadToDeg(_localRotationAngle);
		ImGui::InputFloat("Local Rotation Angle", &DegAngle);
		ImGui::Spacing();

		Vec3 tempPivot = _localPivotPoint - _localPos;
		ImGui::InputFloat2("Local Pivot offset X, Y", tempPivot.m);
		ImGui::Spacing();
	}
	else
	{

		Vector3 temp = _pos;
		ImGui::InputFloat2("Input Global Pos X, Y", temp.m);
		ImGui::Spacing();
		ImGui::SliderFloat2("Slider Global Pos X, Y", temp.m, -1000, 1000);
		SetPos(temp);

		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();

		temp = _scale;
		ImGui::InputFloat2("Input Global Scale X, Y", temp.m);
		ImGui::Spacing();
		ImGui::SliderFloat2("Slider Global Scale X, Y", temp.m, 1, 500);
		SetScale(temp);

		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();

		float DegAngle = RadToDeg(_rotationAngle);

		ImGui::InputFloat("Input Global Rotation Angle", &DegAngle);
		ImGui::Spacing();
		ImGui::SliderFloat("Slider Global Rotation Angle", &DegAngle, -180, 180);
		ImGui::Spacing();

		SetRotate(DegToRad(DegAngle));

		Vec3 tempPivot = _pivotPoint - _pos;
		ImGui::InputFloat2("Input Pivot offset X, Y", tempPivot.m);
		ImGui::Spacing();
		ImGui::SliderFloat2("Slider Pivot offset X, Y", tempPivot.m, -1000, 1000);
		_pivotPoint = _pos + tempPivot;
	}

}

void TransformComponent::MovePos(const Vector3& in)
{
	SetPos(_pos + in);
}

void TransformComponent::MoveScale(const Vector3& in)
{
	SetScale(_scale * in);
}

void TransformComponent::MoveRotate(TransformComponent* parent, const float& in)
{
	SetRotate(_rotationAngle + in, parent);
}

void TransformComponent::Init()
{
	if (GetParentPtr()->GetChild())
		for (auto& it : GetParentPtr()->GetChildList())
			it.second->GetComponent(ComponentId::CT_Transform)->Init();

	SetPivotByLocal(_localPivotPoint);
	SetPosByLocal(_localPos);
	SetScaleByLocal(_localScale);
	SetRotateByLocal(_localRotationAngle);
}

void TransformComponent::SerialiseComponent(Serialiser& document)
{
	if (document.HasMember("Position") && document["Position"].IsArray())	//Checks if the variable exists in .Json file
	{
		if (document["Position"][0].IsFloat() && document["Position"][1].IsFloat())	//Check the array values
			_localPos = Vector3{ document["Position"][0].GetFloat(), document["Position"][1].GetFloat(), 1 };

		if (document["Position"].Size() == 3)
		{
			_localPos.SetZ(document["Position"][2].GetFloat());
		}
	}

	if (document.HasMember("Scale") && document["Scale"].IsArray())
	{
		if (document["Scale"][0].IsFloat() && document["Scale"][1].IsFloat())	//Check the array values
			_localScale = Vector3{ document["Scale"][0].GetFloat(), document["Scale"][1].GetFloat(), 1 };

		if (document["Scale"].Size() == 3)
		{
			_localScale.SetZ(document["Scale"][2].GetFloat());
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

void TransformComponent::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{
	UpdateLocalData();

	rapidjson::Value value;

	value.SetBool(true);
	prototypeDoc.AddMember("TransformComponent", rapidjson::Value(true));

	value.SetArray();
	value.PushBack(rapidjson::Value(_localPos.GetX()).Move(), prototypeDoc.Allocator());
	value.PushBack(rapidjson::Value(_localPos.GetY()).Move(), prototypeDoc.Allocator());
	value.PushBack(rapidjson::Value(_localPos.GetZ()).Move(), prototypeDoc.Allocator());
	prototypeDoc.AddMember("Position", value);

	value.SetArray();
	value.PushBack(rapidjson::Value(_localScale.GetX()).Move(), prototypeDoc.Allocator());
	value.PushBack(rapidjson::Value(_localScale.GetY()).Move(), prototypeDoc.Allocator());
	value.PushBack(rapidjson::Value(_localScale.GetZ()).Move(), prototypeDoc.Allocator());
	prototypeDoc.AddMember("Scale", value);

	value.SetFloat(_localRotationAngle);
	prototypeDoc.AddMember("Rotate", value);

	Vector3 temp = _localPivotPoint - _localPos;
	value.SetArray();
	value.PushBack(rapidjson::Value(temp.GetX()).Move(), prototypeDoc.Allocator());
	value.PushBack(rapidjson::Value(temp.GetY()).Move(), prototypeDoc.Allocator());
	value.PushBack(rapidjson::Value(temp.GetZ()).Move(), prototypeDoc.Allocator());
	prototypeDoc.AddMember("PivotPosition", value);
}

void TransformComponent::DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator)
{
	UpdateLocalData();

	rapidjson::Value value;

	value.SetBool(true);
	prototypeDoc.AddMember("TransformComponent", rapidjson::Value(true), allocator);

	value.SetArray();
	value.PushBack(rapidjson::Value(_localPos.GetX()).Move(), allocator);
	value.PushBack(rapidjson::Value(_localPos.GetY()).Move(), allocator);
	value.PushBack(rapidjson::Value(_localPos.GetZ()).Move(), allocator);
	prototypeDoc.AddMember("Position", value, allocator);

	value.SetArray();
	value.PushBack(rapidjson::Value(_localScale.GetX()).Move(), allocator);
	value.PushBack(rapidjson::Value(_localScale.GetY()).Move(), allocator);
	value.PushBack(rapidjson::Value(_localScale.GetZ()).Move(), allocator);
	prototypeDoc.AddMember("Scale", value, allocator);

	value.SetFloat(_localRotationAngle);
	prototypeDoc.AddMember("Rotate", value, allocator);

	Vector3 temp = _localPivotPoint - _localPos;
	value.SetArray();
	value.PushBack(rapidjson::Value(temp.GetX()).Move(), allocator);
	value.PushBack(rapidjson::Value(temp.GetY()).Move(), allocator);
	value.PushBack(rapidjson::Value(temp.GetZ()).Move(), allocator);
	prototypeDoc.AddMember("PivotPosition", value, allocator);
}

void TransformComponent::DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
{
	TransformComponent* protoTransformCom = dynamic_cast<TransformComponent*>(protoCom);

	if (!protoTransformCom)
	{
		DeSerialiseComponent(value, allocator);
		return;
	}

	UpdateLocalData();

	bool addComponentIntoSceneFile = false;
	rapidjson::Value position;
	rapidjson::Value scale;
	rapidjson::Value rotate;

	rapidjson::Value pivot;

	if (protoTransformCom->_localPos != _localPos)
	{
		position.SetArray();
		addComponentIntoSceneFile = true;
		position.PushBack(rapidjson::Value(_localPos._x), allocator);
		position.PushBack(rapidjson::Value(_localPos._y), allocator);
		position.PushBack(rapidjson::Value(_localPos._z), allocator);
	}

	if (protoTransformCom->_localScale != _localScale)
	{
		scale.SetArray();
		addComponentIntoSceneFile = true;
		scale.PushBack(rapidjson::Value(_localScale._x), allocator);
		scale.PushBack(rapidjson::Value(_localScale._y), allocator);
		scale.PushBack(rapidjson::Value(_localScale._z), allocator);
	}

	if (protoTransformCom->_localRotationAngle != _localRotationAngle)
	{
		addComponentIntoSceneFile = true;
		rotate.SetFloat(_localRotationAngle);
	}

	if (protoTransformCom->_localPivotPoint != _localPivotPoint)
	{
		Vector3 temp = _localPivotPoint - _localPos;
		pivot.SetArray();
		addComponentIntoSceneFile = true;
		pivot.PushBack(rapidjson::Value(temp._x), allocator);
		pivot.PushBack(rapidjson::Value(temp._y), allocator);
		pivot.PushBack(rapidjson::Value(temp._z), allocator);
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