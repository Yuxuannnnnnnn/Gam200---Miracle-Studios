#include "PrecompiledHeaders.h"


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


int GraphicComponent::GetRenderLayer()
{
	return _renderLayer;
}
void GraphicComponent::SetRenderLayer(int layer)
{
	_renderLayer = layer;
}

int GraphicComponent::GetTextureState()
{
	return _textureState;
}
void GraphicComponent::SetTextureState(int state)
{
	_textureState = state;
}


GraphicComponent::GraphicComponent() :
	_typeIdGraphic{ (unsigned)TypeIdGraphic::NONE },
	_fileName{}, 
	_shaderID{ 0 },
	_textureID{ 0 },
	_renderLayer{ 0 }
{
}

GraphicComponent::~GraphicComponent()
{
	//delete[]_fileName;
}

GraphicComponent::GraphicComponent(const GraphicComponent& rhs)
{
	_typeIdGraphic = rhs._typeIdGraphic;
	_fileName = rhs._fileName;;
	_shaderID = rhs._shaderID;
	_textureID = rhs._textureID;
	_renderLayer = rhs._renderLayer;

}

GraphicComponent& GraphicComponent::operator= (const GraphicComponent& rhs)
{
	_typeIdGraphic = rhs._typeIdGraphic;
	_fileName = rhs._fileName;
	_shaderID = rhs._shaderID;
	_textureID = rhs._textureID;
	_renderLayer = rhs._renderLayer;
	return *this;
}

void GraphicComponent::RenderLayerResolver()
{
	IdentityComponent* IdCom = dynamic_cast<IdentityComponent*> (GetSibilingComponent(ComponentId::IDENTITY_COMPONENT));
	std::string type = IdCom->ObjectType();

	if (type.compare("Floor"))
	{
		_renderLayer = -1;
	}
	else if (type.compare("Wall"))
	{
		_renderLayer = 10;
	}
	else if (type.compare("Spawner"))
	{
		_renderLayer = 1;
	}
	else if (type.compare("SpawnerTwo"))
	{
		_renderLayer = 2;
	}
	else if (type.compare("Player"))
	{
		_renderLayer = 7;
	}
	else if (type.compare("Enemy"))
	{
		_renderLayer = 4;
	}
	else if (type.compare("Turret"))
	{
		_renderLayer = 6;
	}
	else if (type.compare("EnemyTwo"))
	{
		_renderLayer = 3;
	}
	else if (type.compare("Bullet"))
	{
		_renderLayer = 9;
	}
	else if (type.compare("BulletT"))
	{
		_renderLayer = 9;
	}
	else if (type.compare("BulletE"))
	{
		_renderLayer = 9;
	}
	else if (type.compare("Explosion"))
	{
		_renderLayer = 9;
	}
	else if (type.compare("Button"))
	{		
		_renderLayer = -10;
	}
}


std::string GraphicComponent::ComponentName() const
{
	return "Graphic Component";
}


void GraphicComponent::SerialiseComponent(Serialiser& document)
{
	if (document.HasMember("G.TypeId") && document["G.TypeId"].IsInt())	//Checks if the variable exists in .Json file
		_typeIdGraphic = document["G.TypeId"].GetInt();

	if (document.HasMember("G.FileName") && document["G.FileName"].IsString())
		_fileName = document["G.FileName"].GetString();
}

void GraphicComponent::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{
	rapidjson::Value value;

	value.SetInt(_typeIdGraphic);
	prototypeDoc.AddMember("G.TypeId", value);


	value.SetString(rapidjson::StringRef(_fileName.c_str()));
	prototypeDoc.AddMember("G.FileName", value);
}

void GraphicComponent::Inspect()
{
	//_fileName
	//	_shaderID
	//	_renderLayer
	IComponent::Inspect();

	{
		ImGui::Spacing();
		//ImGui::InputText("Static Graphic File Name", _fileName, IM_ARRAYSIZE(_fileName));


		static auto graphicList = ResourceManager::GetInstance().GetTexture2DList();
		std::vector<const char*> list(graphicList.size());
		//list[0] = "Texture Files ";

		int i = 0;
		int select;
		for (auto graphicPair = graphicList.begin(); graphicPair != graphicList.end(); graphicPair++)
		{
			const char* ptr = graphicPair->first.c_str();
			list[i] = ptr;
			if (strncmp(graphicPair->first.c_str(), _fileName.c_str(), 20))
			{
				select = i;
			}
			i++;
		}
		//ImGui::Combo("Add Component", &item_current, items, (int)(ComponentId::COUNTCOMPONENT));

		static const char* item_current = list[select];            // Here our selection is a single pointer stored outside the object.
		if (ImGui::BeginCombo(" Texture ", item_current, 0)) // The second parameter is the label previewed before opening the combo.
		{
			for (int n = 0; n < list.size(); n++)
			{
				bool is_selected = (item_current == list[n]);
				if (ImGui::Selectable(list[n], is_selected))
				{
					item_current = list[n];
				}

				//if (is_selected);
				//ImGui::SetItemDefaultFocus();   // Set the initial focus when opening the combo (scrolling + for keyboard navigation support in the upcoming navigation branch)

			}
			ImGui::EndCombo();
		}
	}

	{
		ImGui::Spacing();
		//ImGui::InputText("Static Graphic File Name", _fileName, IM_ARRAYSIZE(_fileName));

		AssetsImguiWindow*  window = dynamic_cast<AssetsImguiWindow *>(_engineSystems._imguiSystem->GetWindows()["Assets"]);
		static auto ShaderList = window->GetVertexShaderFiles();
		static auto FragmentList = window->GetFragementShaderFiles();
		ShaderList.insert(FragmentList.begin(), FragmentList.end());




		ImGui::Spacing();
		int shaderCount = 1;
		static std::vector<int> select(_current_ShaderList.size(), 0);


		if (ImGui::Button("Add Shader"))
		{
			_current_ShaderList.push_back(" ");
			select.push_back(0);
		}

		for (auto currshader : _current_ShaderList)
		{
			ImGui::Spacing();

			auto shader = _shaderList.begin();

			std::vector<const char*> list(ShaderList.size() + 1);
			list[0] = " Choose a shader ";

			int i = 1;
			//static int select = 0;
			for (auto shaderPair = ShaderList.begin(); shaderPair != ShaderList.end(); shaderPair++)
			{
				const char* ptr = shaderPair->first.c_str();
				list[i] = ptr;
				if (shader != _shaderList.end())
				{
					if (strncmp(shaderPair->first.c_str(), shader->c_str(), 20) && currshader != nullptr)
					{
						select[shaderCount - 1] = i;
					}
				}
				i++;
			}
			//ImGui::Combo("Add Component", &item_current, items, (int)(ComponentId::COUNTCOMPONENT));
			currshader = list[select[shaderCount - 1]];            // Here our selection is a single pointer stored outside the object.

			std::string shaderCountString = " Shader " + std::to_string(shaderCount);
			if (ImGui::BeginCombo(shaderCountString.c_str(), currshader, 0)) // The second parameter is the label previewed before opening the combo.
			{
				for (int n = 0; n < list.size(); n++)
				{
					bool is_selected = (currshader == list[n]);
					if (ImGui::Selectable(list[n], is_selected))
					{
						currshader = list[n];
						select[shaderCount - 1] = n;
					}

					//if (is_selected);
					//ImGui::SetItemDefaultFocus();   // Set the initial focus when opening the combo (scrolling + for keyboard navigation support in the upcoming navigation branch)

				}
				ImGui::EndCombo();
			}
			if (shader != _shaderList.end())
			{
				shader++;
			}
			shaderCount++;
		}



	}


	//ImGui::Spacing();
	//ImGui::InputInt("Shader ID", &_shaderID);
	ImGui::Spacing();
	ImGui::InputInt("RendeerLayer", &_renderLayer);
	ImGui::Spacing();
}

unsigned& GraphicComponent::GetTypeId()
{
	return _typeIdGraphic;
}