#include "PrecompiledHeaders.h"

std::string TransformComponent::ComponentName() const
{
	return "Transform Component";
}


TransformComponent::TransformComponent()
	:_pos{ Vector3{ 0, 0, 1 } },
	_scale{ Vector3{ 100, 100, 1 } },
	_rotationAngle{ 0.0f },
	_pivotPoint{ Vector3{ 0, 0, 1 } }
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

	if (temp != Vector3{0,0,0})
	{
		if (TileMapComponent* tilemap = (TileMapComponent*)(GetSibilingComponent(ComponentId::CT_TileMap)))
		{
			tilemap->ResizeNodeMap();
		}
	}
	
	_pos += temp;

	_pivotPoint = in;
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

	if (in != _pos)
	{
		if (TileMapComponent* tilemap = (TileMapComponent*)(GetSibilingComponent(ComponentId::CT_TileMap)))
		{
			tilemap->ResizeNodeMap();
		}
	}
	

	_pivotPoint = _pivotPoint - _pos;
	_pos = in;
	_pivotPoint = _pos + _pivotPoint;
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

	if (in != _scale)
	{
		if (TileMapComponent* tilemap = (TileMapComponent*)(GetSibilingComponent(ComponentId::CT_TileMap)))
		{
			tilemap->ResizeNodeMap();
		}
	}

	_scale = in;
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

	Vec3 tempPos = _pos;

	ImGui::InputFloat2("Input Pos X, Y", tempPos.m);
	ImGui::Spacing();
	ImGui::SliderFloat2("Slider Pos X, Y", tempPos.m, -1000, 1000);

	if (tempPos != _pos)
	{
		if (TileMapComponent * TMCom = (TileMapComponent *)(GetSibilingComponent(ComponentId::CT_TileMap)))
		{
			//Reset array of nodes position. 
			//TMCom->CalcOffset();

		}
	}

	SetPos(tempPos);

	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();

	Vec3 tempScale = _scale;

	ImGui::InputFloat2("Input Scale X, Y", tempScale.m);
	ImGui::Spacing();
	ImGui::SliderFloat2("Slider Scale X, Y", tempScale.m, 1, 500);

	if (tempScale != _scale)
	{
		if (TileMapComponent * TMCom = (TileMapComponent *)(GetSibilingComponent(ComponentId::CT_TileMap)))
		{
			//Reset array of nodes position. 
			//TMCom->CalcTileSize();
		}
	}

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

	Vec3 tempPivot = _pivotPoint - _pos;

	ImGui::InputFloat2("Input Pivot X, Y", tempPivot.m);
	ImGui::Spacing();
	ImGui::SliderFloat2("Slider Pivot X, Y", tempPivot.m, -1000, 1000);

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

	SetPos(_localPos);

	_pivotPoint = _localPos + _localPivotPoint;
	_pivotPoint._z = 1.f;

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

void TransformComponent::DeSerialiseComponent(DeSerialiser& prototypeDoc)
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

	_pivotPoint -= _pos;
	value.SetArray();
	value.PushBack(rapidjson::Value(_pivotPoint.GetX()).Move(), prototypeDoc.Allocator());
	value.PushBack(rapidjson::Value(_pivotPoint.GetY()).Move(), prototypeDoc.Allocator());
	value.PushBack(rapidjson::Value(_pivotPoint.GetZ()).Move(), prototypeDoc.Allocator());
	prototypeDoc.AddMember("PivotPosition", value);
	_pivotPoint += _pos;
}

void TransformComponent::DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator)
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

	_pivotPoint -= _pos;
	value.SetArray();
	value.PushBack(rapidjson::Value(_pivotPoint.GetX()).Move(), allocator);
	value.PushBack(rapidjson::Value(_pivotPoint.GetY()).Move(), allocator);
	value.PushBack(rapidjson::Value(_pivotPoint.GetZ()).Move(), allocator);
	prototypeDoc.AddMember("PivotPosition", value, allocator);
	_pivotPoint += _pos;
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
		_pivotPoint -= _pos;
		pivot.SetArray();
		addComponentIntoSceneFile = true;
		pivot.PushBack(rapidjson::Value(_pivotPoint._x), allocator);
		pivot.PushBack(rapidjson::Value(_pivotPoint._y), allocator);
		pivot.PushBack(rapidjson::Value(_pivotPoint._z), allocator);
		_pivotPoint += _pos;
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