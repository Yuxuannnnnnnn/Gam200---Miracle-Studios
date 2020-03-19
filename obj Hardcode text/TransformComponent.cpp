#include "PrecompiledHeaders.h"

std::string TransformComponent::ComponentName() const
{
	return "Transform Component";
}


TransformComponent::TransformComponent()
	:_pos{ Vector3{ 0, 0, 1 } },
	_scale{ Vector3{ 100, 100, 1 } },
	_rotationAngle{ 0.0f },
	_pivotPoint{ Vector3{ 0, 0, 1 } },
	_localInspect{true}
{
}

TransformComponent::TransformComponent(const Vector3& pos, const Vector3& scale, const float& angle) :
	_pos{ pos }, _scale{ scale }, _rotationAngle{ angle }, _pivotPoint{ pos }
{

}

Vector3 TransformComponent::GetPos()
{
	return Vector3{ _pos._x * MyWindowsSystem.getWindow().GetWindowWidthRatio(),_pos._y * MyWindowsSystem.getWindow().GetWindowHeightRatio(),1.f } ;
}

Vector3 TransformComponent::GetPivot()
{
	return Vector3{ _pivotPoint._x * MyWindowsSystem.getWindow().GetWindowWidthRatio(),_pivotPoint._y * MyWindowsSystem.getWindow().GetWindowHeightRatio(),1.f };
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
	
	_pivotPoint = in;

	// local data
	_localPivotPoint = _pivotPoint;

	/*if (!this->GetParentPtr()->GetIndependent())
	{
		TransformComponent* parentTransform = GetComponentObject(this->GetParentPtr()->GetParent(), Transform);
		_localPos = _localPos - parentTransform->_pos;
	}*/


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

	// local data
	_localPos = _pos;
	_localPivotPoint = _pivotPoint;

	/*if (!this->GetParentPtr()->GetIndependent())
	{
		TransformComponent* parentTransform = GetComponentObject(this->GetParentPtr()->GetParent(), Transform);
		_localPos = _localPos - parentTransform->_pos;
	}*/


	if (OldPosition != _pos)
	{
		if (TileMapComponent* tilemap = (TileMapComponent*)(GetSibilingComponent(ComponentId::CT_TileMap)))
		{
			tilemap->ResizeNodeMap();
		}
	}
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

	Vector3  OldScale = _scale;

	_scale = in;

	// local data
	_localScale = _scale;

	/*if (!this->GetParentPtr()->GetIndependent())
	{
		TransformComponent* parentTransform = GetComponentObject(this->GetParentPtr()->GetParent(), Transform);
		_localScale = _localScale / parentTransform->_localScale;
	}*/



	if (OldScale != _scale)
	{
		if (TileMapComponent* tilemap = (TileMapComponent*)(GetSibilingComponent(ComponentId::CT_TileMap)))
		{
			tilemap->ResizeNodeMap();
		}
	}



}

float& TransformComponent::GetRotate()
{
	return _rotationAngle;
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

			child->MoveRotate(this,temp);
		}
	}

	Vec3 temp2;

	if (!parent)
	{
		Vec3 diff = _pos - _pivotPoint;
		float mag = diff.Length();
		float deg = atan2(diff._y, diff._x) + temp;
		temp2 = Vec3{ mag * cos(deg), mag * sin(deg) } - diff;
	}
	else
	{
		Vec3 diff = _pos - parent->_pivotPoint;
		float mag = diff.Length();
		float deg = atan2(diff._y, diff._x) + temp;
		temp2 = Vec3{ mag * cos(deg), mag * sin(deg) } -diff;
	}

	_pos += temp2;
	_rotationAngle = in;

	// local data
	_localPos = _pos;
	_localRotationAngle = _rotationAngle;

	if (!this->GetParentPtr()->GetIndependent())
	{
		TransformComponent* parentTransform = GetComponentObject(this->GetParentPtr()->GetParent(), Transform);
		_localPos = _localPos - parentTransform->_pos;
		_localRotationAngle = _localRotationAngle - parentTransform->_rotationAngle;
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

	ImGui::Checkbox("Inspect In Local Space", &_localInspect);

	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();

	/*if (_localInspect)
	{

		ImGui::InputFloat2("Input Local Pos X, Y", _localPos.m);
		ImGui::Spacing();
		ImGui::SliderFloat2("Slider Local Pos X, Y", _localPos.m, -1000, 1000);
		SetPos(_localPos);

		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();


		ImGui::InputFloat2("Input Local Scale X, Y", _localScale.m);
		ImGui::Spacing();
		ImGui::SliderFloat2("Slider Local Scale X, Y", _localScale.m, 1, 500);
		SetScale(_localScale);

		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();

		float DegAngle = RadToDeg(_localRotationAngle);

		ImGui::InputFloat("Input Local Rotation Angle", &DegAngle);
		ImGui::Spacing();
		ImGui::SliderFloat("Slider Local Rotation Angle", &DegAngle, -180, 180);
		ImGui::Spacing();

		SetRotate(DegToRad(DegAngle));
	}
	else
	{
		ImGui::InputFloat2("Input Global Pos X, Y", _pos.m);
		ImGui::Spacing();
		ImGui::SliderFloat2("Slider Global Pos X, Y", _pos.m, -1000, 1000);
		SetPos(_pos);

		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();


		ImGui::InputFloat2("Input Global Scale X, Y", _scale.m);
		ImGui::Spacing();
		ImGui::SliderFloat2("Slider Global Scale X, Y", _scale.m, 1, 500);
		SetScale(_scale);

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
	}*/

	Vec3 tempPivot = _pivotPoint - _pos;
	ImGui::InputFloat2("Input Pivot offset X, Y", tempPivot.m);
	ImGui::Spacing();
	ImGui::SliderFloat2("Slider Pivot offset X, Y", tempPivot.m, -1000, 1000);
	_pivotPoint = _pos + tempPivot;
}

///////////////////////////////////////////////////////////////

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

	SetPivot(_localPivotPoint);
	SetPos(_localPos);
	SetScale(_localScale);
	SetRotate(_localRotationAngle);
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

	_localPivotPoint -= _localPos;
	value.SetArray();
	value.PushBack(rapidjson::Value(_localPivotPoint.GetX()).Move(), prototypeDoc.Allocator());
	value.PushBack(rapidjson::Value(_localPivotPoint.GetY()).Move(), prototypeDoc.Allocator());
	value.PushBack(rapidjson::Value(_localPivotPoint.GetZ()).Move(), prototypeDoc.Allocator());
	prototypeDoc.AddMember("PivotPosition", value);
	_localPivotPoint += _localPos;
}

void TransformComponent::DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator)
{
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

	_localPivotPoint -= _localPos;
	value.SetArray();
	value.PushBack(rapidjson::Value(_localPivotPoint.GetX()).Move(), allocator);
	value.PushBack(rapidjson::Value(_localPivotPoint.GetY()).Move(), allocator);
	value.PushBack(rapidjson::Value(_localPivotPoint.GetZ()).Move(), allocator);
	prototypeDoc.AddMember("PivotPosition", value, allocator);
	_localPivotPoint += _localPos;
}

void TransformComponent::DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
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
		_localPivotPoint -= _localPos;
		pivot.SetArray();
		addComponentIntoSceneFile = true;
		pivot.PushBack(rapidjson::Value(_localPivotPoint._x), allocator);
		pivot.PushBack(rapidjson::Value(_localPivotPoint._y), allocator);
		pivot.PushBack(rapidjson::Value(_localPivotPoint._z), allocator);
		_localPivotPoint += _localPos;
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