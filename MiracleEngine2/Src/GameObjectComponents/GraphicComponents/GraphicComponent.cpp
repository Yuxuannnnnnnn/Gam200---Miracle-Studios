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
	auto it = EngineSystems::GetInstance()._graphicsSystem->GetTextureManager()._textureMap.find(_fileName);
	
	// if there is a filename in texturemap
	if (it != EngineSystems::GetInstance()._graphicsSystem->GetTextureManager()._textureMap.end())
	{
		return it->second->GetTextureID();
	}


	return _textureID;
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
	else if (type.compare("Bullet_T"))
	{
		_renderLayer = 9;
	}
	else if (type.compare("Bullet_E"))
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
	IComponentSystem::Inspect();

	ImGui::Spacing();
	//ImGui::InputText("Static Graphic File Name", _fileName, IM_ARRAYSIZE(_fileName));
	std::string string = "Graphic File Name: " + _fileName;
	ImGui::Text(string.c_str());
	ImGui::Spacing();
	ImGui::InputInt("Shader ID", &_shaderID);
	ImGui::Spacing();
	ImGui::InputInt("RendeerLayer", &_renderLayer);
	ImGui::Spacing();
}

unsigned& GraphicComponent::GetTypeId()
{
	return _typeIdGraphic;
}