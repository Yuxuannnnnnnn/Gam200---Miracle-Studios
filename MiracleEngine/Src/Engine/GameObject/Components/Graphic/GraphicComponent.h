#pragma once
#include "../../IComponent.h"
#include "GameObject/IAllocator.h"
#include "SystemGraphics/RenderLayer.h"

enum class TypeIdGraphic {
	NONE = 0,

};

class GraphicComponent : public IComponent
{
private:

	std::string _fileName;      
	std::string _shader;
	RenderLayer _renderlayer;

	float u0, v0;
	float u1, v1;

public:

	unsigned int GetTextureID() const;               // base on asset file name, get the textureID on OpenGL for imgui
	
	const std::string& GetFileName() const;
	void SetFileName(const std::string& filename);


	const std::string& GetShaderType()
	{
		return _shader;
	}


	std::string ComponentName() const override;
	void SerialiseComponent(Serialiser& document) override
	{
		//if (document.HasMember("G.TypeId") && document["G.TypeId"].IsInt())	//Checks if the variable exists in .Json file
		//	_typeIdGraphic = document["G.TypeId"].GetInt();

		if (document.HasMember("G.FileName") && document["G.FileName"].IsString())
			_fileName = document["G.FileName"].GetString();


		if (document.HasMember("G.Shader") && document["G.Shader"].IsString())
			_shader = document["G.Shader"].GetString();

		if (document.HasMember("G.RenderLayer") && document["G.RenderLayer"].IsInt())
			_renderlayer = document["G.RenderLayer"].GetInt();
	}


	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override
	{
		rapidjson::Value value;

		value.SetBool(true);
		prototypeDoc.AddMember("GraphicComponent", rapidjson::Value(true));
		//value.SetInt(_typeIdGraphic);
		//prototypeDoc.AddMember("G.TypeId", value);

		value.SetString(rapidjson::StringRef(_fileName.c_str()));
		prototypeDoc.AddMember("G.FileName", value);

		value.SetString(rapidjson::StringRef(_shader.c_str()));
		prototypeDoc.AddMember("G.Shader", value);

		value.SetInt(_renderlayer.GetLayer());
		prototypeDoc.AddMember("G.RenderLayer", value);
	}


	virtual void DeserialiseComponentSceneFile(IComponent* protoCom, DeSerialiser& SceneFile) override
	{
		GraphicComponent* protoGraphicCom = dynamic_cast<GraphicComponent*>(protoCom);

		rapidjson::Value fileName;
		rapidjson::Value shader;
		rapidjson::Value renderlayer;
		bool addComponentIntoSceneFile = false;

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
		
		if (protoGraphicCom->_renderlayer.GetLayer() == _renderlayer.GetLayer())
		{
			addComponentIntoSceneFile = true;
			renderlayer.SetInt(_renderlayer.GetLayer());
		}


		if (addComponentIntoSceneFile)	//If anyone of component data of obj is different from Prototype
		{
			SceneFile.AddMember("GraphicComponent", rapidjson::Value(true));

			if (!fileName.IsNull())	//if rapidjson::value container is not empty
			{
				SceneFile.AddMember("G.FileName", fileName);
			}

			if (!shader.IsNull())
			{
				SceneFile.AddMember("G.Shader", shader);
			}

			if (!renderlayer.IsNull())
			{
				SceneFile.AddMember("G.RenderLayer", renderlayer);
			}
		}

	}


	virtual void Inspect() override;

	//Constructor
	GraphicComponent();
	virtual ~GraphicComponent();
	GraphicComponent(const GraphicComponent& rhs) = default;
	GraphicComponent& operator=(const GraphicComponent& rhs) = default;


	void RenderLayerResolver();

	int GetTextureState();
	void SetTextureState(int state)
	{

	}

	int GetRenderLayer()
	{
		return 0;
	}
	void SetRenderLayer(int state);


	unsigned& GetTypeId();
};

