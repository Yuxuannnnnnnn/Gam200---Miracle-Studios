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




GraphicComponent::GraphicComponent():
	_fileName{}, 
	_shader{},
	_layer{ 1 }, _hasAlpha{ false }, _hasAdjustableAlpha{ false }, _alphaVal{ 1.0f }, _isFadingOut{ false }, _isFlickering{false}
{
	_alphaVal = 1.0f;
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
	std::vector<const char*> list(graphicList.size());
	//list[0] = "Choose a Texture ";

	int i = 0;
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
	static bool * open = &op;

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