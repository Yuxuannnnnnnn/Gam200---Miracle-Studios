#include "PrecompiledHeaders.h"

void GraphicComponent::SetAlpha(float alphaValue)
{
	_alphaVal = alphaValue;
}

float GraphicComponent::GetAlpha()
{
	return _alphaVal;
}

const std::string& GraphicComponent::GetFileName() const
{
	return _fileName;
}

void GraphicComponent::SetFileName(const std::string& filename)
{
	_fileName = filename;
}



unsigned int GraphicComponent::GetTextureID() const
{
	//auto it = EngineSystems::GetInstance()._graphicsSystem->GetTextureManager()._textureMap.find(_fileName);
	//
	//// if there is a filename in texturemap
	//if (it != EngineSystems::GetInstance()._graphicsSystem->GetTextureManager()._textureMap.end())
	//{
	//	return it->second->GetTextureID();
	//}


	//return _textureID;
	return 0;
}




GraphicComponent::GraphicComponent() :
	_fileName{},
	_shader{},
	_layer{ 1 }, _hasAlpha{ false }, _hasAdjustableAlpha{ false }, _alphaVal{ 1.0f }, _isFadingOut{ false }, _isFlickering{ false }
{
	_alphaVal = 1.0f;
	_tintcolor = glm::vec4{ 0,0,0,0 };
}

GraphicComponent::~GraphicComponent()
{
	//delete[]_fileName;
}

//GraphicComponent::GraphicComponent(const GraphicComponent& rhs)
//{
//
//
//}
//
//GraphicComponent& GraphicComponent::operator= (const GraphicComponent& rhs)
//{
//
//	return *this;
//}

void GraphicComponent::RenderLayerResolver()
{
	IdentityComponent* IdCom = dynamic_cast<IdentityComponent*> (GetSibilingComponent(ComponentId::CT_Identity));
	std::string type = IdCom->ObjectType();


}


std::string GraphicComponent::ComponentName() const
{
	return "Graphic Component";
}





//unsigned& GraphicComponent::GetTypeId()
//{
//	return _typeIdGraphic;
//}


void GraphicComponent::Inspect()
{
	IComponent::Inspect();

	//ImGui::InputText("Static Graphic File Name", _fileName, IM_ARRAYSIZE(_fileName));

	ImGui::Spacing();
	ImGui::Spacing();

	ImGui::InputInt("RenderLayer", &_layer);
	/*	if (_layer > 10)
			_layer = 30;
		else if (_layer < 0)
			_layer = 0;*/

	ImGui::Spacing();
	ImGui::Spacing();

	static auto& graphicList = MyResourceSystem.GetTexture2DList();
	std::vector<const char*> list(graphicList.size() + 1);
	//list[0] = "Choose a Texture ";

	int i = 0;

	list[i] = "type text here...";
	i++;
	int select = 0;
	for (auto graphicPair = graphicList.begin(); graphicPair != graphicList.end(); graphicPair++)
	{
		const char* ptr = graphicPair->first.c_str();


		list[i] = ptr;
		if (!strncmp(ptr, _fileName.c_str(), 20))
		{
			select = i;
		}


		i++;
	}

	//	//ImGui::Combo("Add Component", &item_current, items, (int)(ComponentId::COUNTCOMPONENT));
	//
	//	static const char* item_current = list[select];            // Here our selection is a single pointer stored outside the object.
	//	if (ImGui::BeginCombo(" Texture ", item_current, 0)) // The second parameter is the label previewed before opening the combo.
	//	{
	//		for (int n = 0; n < list.size(); n++)
	//		{
	//			bool is_selected = (item_current == list[n]);
	//			if (ImGui::Selectable(list[n], is_selected))
	//			{
	//				item_current = list[n];
	//				_fileName = list[n];
	//			}
	//
	//			//if (is_selected);
	//			//ImGui::SetItemDefaultFocus();   // Set the initial focus when opening the combo (scrolling + for keyboard navigation support in the upcoming navigation branch)
	//
	//		}
	//		ImGui::EndCombo();
	//	}
	//}

	static ComboFilterState s = { select, 0 };

	static char buf[128];

	static ImGuiFunctions Function;
	static bool op = false;
	static bool* open = &op;

	if (_fileName.empty())
	{
		strncpy(buf, "type text here...", 18 + 1);
	}
	else
	{
		strncpy(buf, _fileName.c_str(), _fileName.size() + 2);
	}

	if (Function.ComboFilter("Texture", buf, IM_ARRAYSIZE(buf), list, list.size(), s, _fileName, open))
	{
		//puts(buf);
	}

	{
		ImGui::Spacing();

		static auto& ShaderList = MyResourceSystem.GetShaderList();
		std::vector<const char*> list;
		list.push_back("Choose a Shader ");
		static const char* name = list[0];


		int i = 1;
		static int select = 0;
		for (auto shaderPair = ShaderList.begin(); shaderPair != ShaderList.end(); shaderPair++)
		{
			const char* ptr = shaderPair->first.c_str();
			if (shaderPair->first.find("System") == std::string::npos)
			{
				list.push_back(ptr);
				if (!strncmp(shaderPair->first.c_str(), _shader.c_str(), 20))
				{
					select = i;
				}
			}
			i++;
		}

		if (ImGui::BeginCombo("Shader", list[select], 0)) // The second parameter is the label previewed before opening the combo.
		{
			for (int n = 0; n < list.size(); n++)
			{
				bool is_selected = (name == list[n]);
				if (ImGui::Selectable(list[n], is_selected))
				{
					_shader = list[n];
					select = n;
				}

				//if (is_selected);
				//ImGui::SetItemDefaultFocus();   // Set the initial focus when opening the combo (scrolling + for keyboard navigation support in the upcoming navigation branch)

			}
			ImGui::EndCombo();
		}


		ImGui::Spacing();
		ImGui::Spacing();

		std::string string = "Has Alpha ";
		ImGui::Checkbox(string.c_str(), &_hasAlpha);

		ImGui::Spacing();
		ImGui::Spacing();

		string = "Activate Alpha Adjustment ";
		ImGui::Checkbox(string.c_str(), &_hasAdjustableAlpha);

		ImGui::Spacing();
		ImGui::Spacing();

		string = "Alpha Value";
		ImGui::InputFloat(string.c_str(), &_alphaVal);
		string = "Alpha Value Slider";
		ImGui::SliderFloat(string.c_str(), &_alphaVal, 0, 1);

		ImGui::Spacing();
		ImGui::Spacing();

		string = "Fade Out ";
		ImGui::Checkbox(string.c_str(), &_isFadingOut);

		ImGui::Spacing();
		ImGui::Spacing();

		string = "Flicker ";
		ImGui::Checkbox(string.c_str(), &_isFlickering);

		ImGui::Spacing();
		ImGui::Spacing();

		ImGui::Checkbox("start panning", &_startInterpolate);
		ImGui::InputFloat("start pos", &_startpos);
		ImGui::InputFloat("end pos", &_endpos);
		//ImGui::InputText("Static Graphic File Name", _fileName, IM_ARRAYSIZE(_fileName));

		//AssetsImguiWindow*  window = dynamic_cast<AssetsImguiWindow *>(_engineSystems._imguiSystem->GetWindows()["Assets"]);
		//static auto ShaderList = window->GetVertexShaderFiles();
		//static auto FragmentList = window->GetFragementShaderFiles();
		//ShaderList.insert(FragmentList.begin(), FragmentList.end());

		//ImGui::Spacing();
		//int shaderCount = 1;
		//static std::vector<int> select(_current_ShaderList.size(), 0);


		//if (ImGui::Button("Add Shader"))
		//{
		//	_current_ShaderList.push_back(" ");
		//	select.push_back(0);
		//}
		//
		//for (auto currshader : _current_ShaderList)
		//{
		//	ImGui::Spacing();
		//
		//	auto shader = _shaderList.begin();
		//
		//	std::vector<const char*> list(ShaderList.size() + 1);
		//	list[0] = " Choose a shader ";
		//
		//	int i = 1;
		//	//static int select = 0;
		//	for (auto shaderPair = ShaderList.begin(); shaderPair != ShaderList.end(); shaderPair++)
		//	{
		//		const char* ptr = shaderPair->first.c_str();
		//		list[i] = ptr;
		//		if (shader != _shaderList.end())
		//		{
		//			if (strncmp(shaderPair->first.c_str(), shader->c_str(), 20) && currshader != nullptr)
		//			{
		//				select[shaderCount - 1] = i;
		//			}
		//		}
		//		i++;
		//	}
		//	//ImGui::Combo("Add Component", &item_current, items, (int)(ComponentId::COUNTCOMPONENT));
		//	currshader = list[select[shaderCount - 1]];            // Here our selection is a single pointer stored outside the object.
		//
		//	std::string shaderCountString = " Shader " + std::to_string(shaderCount);
		//	if (ImGui::BeginCombo(shaderCountString.c_str(), currshader, 0)) // The second parameter is the label previewed before opening the combo.
		//	{
		//		for (int n = 0; n < list.size(); n++)
		//		{
		//			bool is_selected = (currshader == list[n]);
		//			if (ImGui::Selectable(list[n], is_selected))
		//			{
		//				currshader = list[n];
		//				select[shaderCount - 1] = n;
		//			}
		//
		//			//if (is_selected);
		//			//ImGui::SetItemDefaultFocus();   // Set the initial focus when opening the combo (scrolling + for keyboard navigation support in the upcoming navigation branch)
		//
		//		}
		//		ImGui::EndCombo();
		//	}
		//	if (shader != _shaderList.end())
		//	{
		//		shader++;
		//	}
		//	shaderCount++;
		//}



	}


	{
		//ImGui::Spacing();
		//ImGui::InputInt("Shader ID", &_shaderID);
		ImGui::Spacing();
		//ImGui::InputInt("RendeerLayer", &_renderLayer);
		ImGui::Spacing();
	}
}

glm::vec4 GraphicComponent::GetTintColor() const
{
	return _tintcolor;
}

void GraphicComponent::SetTintColor(const glm::vec4& color)
{
	_tintcolor = color;
}

void  GraphicComponent::Init()
{
	_alphaVal = 1.0f;
}

void  GraphicComponent::LoadResource()
{
#ifdef LEVELEDITOR
	MyResourceManager.AddNewTexture2DResource({ _fileName, MyResourceSystem.GetTexture2DResourcePath(_fileName) });
	//MyResourceManager.AddNewShaderResource({ _shader, MyResourceSystem.GetShaderResourcePath(_shader) });
#endif // LEVELEDITOR
}


void  GraphicComponent::EnableFadingOut(bool isFading)
{
	_isFadingOut = isFading;
}

void GraphicComponent::EnableAdjustableAlpha(bool isAlpha)
{
	_hasAdjustableAlpha = isAlpha;
}

void GraphicComponent::EnableAlpha(bool isAlpha)
{
	_hasAlpha = isAlpha;
}

void  GraphicComponent::EnableFlickering(bool isAlpha)
{
	_isFlickering = isAlpha;
}

const std::string& GraphicComponent::GetShaderType()
{
	return _shader;
}

int  GraphicComponent::GetRenderLayer()
{
	return _layer;
}

void GraphicComponent::StartInterpolate()
{
	int a = (int)_interpolateTimer;

	if (_interpolateTimer > 1.00f)
	{
		_interpolateTimer -= 1.00f;
		_interpoateState += 1;
	}

	if (_interpoateState % 2 == 0)
	{
		Vector3 result = _startpos * (1 - _interpolateTimer) + _endpos * _interpolateTimer;
		auto b = (TransformComponent*)GetSibilingComponent(ComponentId::CT_Transform);
		b->SetPos(result);
	}
	// return form point 2
	else
	{
		Vector3 result = _endpos * (1 - _interpolateTimer) + _startpos * _interpolateTimer;
		auto b = (TransformComponent*)GetSibilingComponent(ComponentId::CT_Transform);
		b->SetPos(result);

	}

}

bool GraphicComponent::IsInterpolateStarting()
{
	return _startInterpolate;
}

void GraphicComponent::SetInterpolateTimer(float time)
{
	_interpolateTimer = time;
}

float GraphicComponent::GetInterpolateTimer()
{
	return _interpolateTimer;
}

void GraphicComponent::SerialiseComponent(Serialiser& document)
{
	//if (document.HasMember("G.TypeId") && document["G.TypeId"].IsInt())	//Checks if the variable exists in .Json file
	//	_typeIdGraphic = document["G.TypeId"].GetInt();

	if (document.HasMember("GraphicsComponent") && document["GraphicsComponent"].IsBool())
		SetEnable(document["GraphicsComponent"].GetBool());

	if (document.HasMember("G.FileName") && document["G.FileName"].IsString())
		_fileName = document["G.FileName"].GetString();


	if (document.HasMember("G.Shader") && document["G.Shader"].IsString())
		_shader = document["G.Shader"].GetString();

	if (document.HasMember("G.Layer") && document["G.Layer"].IsInt())	//Checks if the variable exists in .Json file
	{
		_layer = (document["G.Layer"].GetInt());
	}

	if (document.HasMember("_hasAlpha") && document["_hasAlpha"].IsBool())	//Checks if the variable exists in .Json file
	{
		_hasAlpha = (document["_hasAlpha"].GetBool());
	}


	if (document.HasMember("_hasAdjustableAlpha") && document["_hasAdjustableAlpha"].IsBool())	//Checks if the variable exists in .Json file
	{
		_hasAdjustableAlpha = (document["_hasAdjustableAlpha"].GetBool());
	}

	if (document.HasMember("_alphaVal") && document["_alphaVal"].IsFloat())	//Checks if the variable exists in .Json file
	{
		_alphaVal = (document["_alphaVal"].GetFloat());
	}

	if (document.HasMember("_isFadingOut") && document["_isFadingOut"].IsBool())	//Checks if the variable exists in .Json file
	{
		_isFadingOut = (document["_isFadingOut"].GetBool());
	}

	if (document.HasMember("_isFlickering") && document["_isFlickering"].IsBool())	//Checks if the variable exists in .Json file
	{
		_isFlickering = (document["_isFlickering"].GetBool());
	}

}


void GraphicComponent::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{
	rapidjson::Value value;

	value.SetBool(GetEnable());
	prototypeDoc.AddMember("GraphicsComponent", value);
	//value.SetInt(_typeIdGraphic);
	//prototypeDoc.AddMember("G.TypeId", value);

	value.SetString(rapidjson::StringRef(_fileName.c_str()));
	prototypeDoc.AddMember("G.FileName", value);

	value.SetString(rapidjson::StringRef(_shader.c_str()));
	prototypeDoc.AddMember("G.Shader", value);

	value.SetInt(_layer);
	prototypeDoc.AddMember("G.Layer", value);

	value.SetBool(_hasAlpha);
	prototypeDoc.AddMember("_hasAlpha", value);

	value.SetBool(_hasAdjustableAlpha);
	prototypeDoc.AddMember("_hasAdjustableAlpha", value);


	value.SetFloat(_alphaVal);
	prototypeDoc.AddMember("_alphaVal", value);


	value.SetBool(_isFadingOut);
	prototypeDoc.AddMember("_isFadingOut", value);


	value.SetBool(_isFlickering);
	prototypeDoc.AddMember("_isFlickering", value);

}

void GraphicComponent::DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator)
{
	rapidjson::Value value;

	value.SetBool(GetEnable());
	prototypeDoc.AddMember("GraphicsComponent", value, allocator);

	//value.SetInt(_typeIdGraphic);
	//prototypeDoc.AddMember("G.TypeId", value);

	value.SetString(rapidjson::StringRef(_fileName.c_str()));
	prototypeDoc.AddMember("G.FileName", value, allocator);

	value.SetString(rapidjson::StringRef(_shader.c_str()));
	prototypeDoc.AddMember("G.Shader", value, allocator);

	value.SetInt(_layer);
	prototypeDoc.AddMember("G.Layer", value, allocator);

	value.SetBool(_hasAlpha);
	prototypeDoc.AddMember("_hasAlpha", value, allocator);


	value.SetBool(_hasAdjustableAlpha);
	prototypeDoc.AddMember("_hasAdjustableAlpha", value, allocator);


	value.SetFloat(_alphaVal);
	prototypeDoc.AddMember("_alphaVal", value, allocator);


	value.SetBool(_isFadingOut);
	prototypeDoc.AddMember("_isFadingOut", value, allocator);


	value.SetBool(_isFlickering);
	prototypeDoc.AddMember("_isFlickering", value, allocator);

}

void GraphicComponent::DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
{
	GraphicComponent* protoGraphicCom = dynamic_cast<GraphicComponent*>(protoCom);

	if (!protoGraphicCom)
	{
		DeSerialiseComponent(value, allocator);
		return;
	}


	rapidjson::Value enable;
	rapidjson::Value fileName;
	rapidjson::Value shader;
	rapidjson::Value layer;
	rapidjson::Value HasAlpha;

	rapidjson::Value hasAdjustableAlpha;
	rapidjson::Value alphaVal;
	rapidjson::Value isFadingOut;
	rapidjson::Value isFlickering;

	bool addComponentIntoSceneFile = false;

	if (protoGraphicCom->GetEnable() != this->GetEnable())
	{
		addComponentIntoSceneFile = true;
		enable.SetBool(GetEnable());
	}

	if (protoGraphicCom->_hasAlpha != this->_hasAlpha)
	{
		addComponentIntoSceneFile = true;
		HasAlpha.SetBool(_hasAlpha);
	}

	if (protoGraphicCom->_fileName.compare(_fileName))
	{
		addComponentIntoSceneFile = true;
		fileName.SetString(rapidjson::StringRef(_fileName.c_str()));
	}

	if (protoGraphicCom->_shader.compare(_shader))
	{
		addComponentIntoSceneFile = true;
		shader.SetString(rapidjson::StringRef(_shader.c_str()));
	}

	if (protoGraphicCom->_layer != _layer)
	{
		addComponentIntoSceneFile = true;
		layer.SetInt(_layer);
	}

	if (protoGraphicCom->_hasAdjustableAlpha != _hasAdjustableAlpha)
	{
		addComponentIntoSceneFile = true;
		hasAdjustableAlpha.SetBool(_hasAdjustableAlpha);
	}

	if (protoGraphicCom->_alphaVal != _alphaVal)
	{
		addComponentIntoSceneFile = true;
		alphaVal.SetFloat(_alphaVal);
	}

	if (protoGraphicCom->_isFadingOut != _isFadingOut)
	{
		addComponentIntoSceneFile = true;
		isFadingOut.SetBool(_isFadingOut);
	}

	if (protoGraphicCom->_isFlickering != _isFlickering)
	{
		addComponentIntoSceneFile = true;
		isFlickering.SetBool(_isFlickering);
	}


	if (addComponentIntoSceneFile)	//If anyone of component data of obj is different from Prototype
	{
		if (!enable.IsNull())
			value.AddMember("GraphicsComponent", enable, allocator);
		else
			value.AddMember("GraphicsComponent", protoGraphicCom->GetEnable(), allocator);

		if (!HasAlpha.IsNull())	//if rapidjson::value container is not empty
		{
			value.AddMember("_hasAlpha", HasAlpha, allocator);
		}

		if (!fileName.IsNull())	//if rapidjson::value container is not empty
		{
			value.AddMember("G.FileName", fileName, allocator);
		}

		if (!shader.IsNull())
		{
			value.AddMember("G.Shader", shader, allocator);
		}

		if (!layer.IsNull())
		{
			value.AddMember("G.Layer", layer, allocator);
		}

		if (!hasAdjustableAlpha.IsNull())
		{
			value.AddMember("_hasAdjustableAlpha", hasAdjustableAlpha, allocator);
		}

		if (!alphaVal.IsNull())
		{
			value.AddMember("_alphaVal", alphaVal, allocator);
		}

		if (!isFadingOut.IsNull())
		{
			value.AddMember("_isFadingOut", isFadingOut, allocator);
		}

		if (!isFlickering.IsNull())
		{
			value.AddMember("_isFlickering", isFlickering, allocator);
		}
	}

}