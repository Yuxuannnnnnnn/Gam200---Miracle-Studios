#pragma once
#include "../../IComponent.h"
#include "GameObject/IAllocator.h"
#include "Tools/Resource/ResourceSystem.h"

#include "Editor/ImguiFunctions.h"


enum class TypeIdGraphic {
	NONE = 0,

};

class GraphicComponent : public IComponent
{
private:

	std::string _fileName;      
	std::string _shader;
	//RenderLayer _renderlayer; Not Used anymore because Z value is computed in Transformcomponent
	
	// has alpha from PNG
	bool _hasAlpha;

	// has alpha adjustable in programming
	bool _hasAdjustableAlpha; //when the button is ticked, _alphaVal is taken into account
	float _alphaVal;	//alpha value is between 0 to 1

	bool _isFadingOut; //if box is checked, the object will slowly fade out
	bool _isFlickering;//if box is checked, the objecy will randomly flicker on and off

	int _layer;



	float u0, v0;
	float u1, v1;

public:

	void Init()
	{
		_alphaVal = 1.0f;
	}


	inline bool HasAlpha() 
	{
		return _hasAlpha; 
	}

	inline bool HasAdjustableAlpha()
	{
		return _hasAdjustableAlpha;
	}

	inline bool IsFadingOut()
	{
		return _isFadingOut;
	}

	inline bool IsFlickering()
	{
		return _isFlickering;
	}

	void EnableFadingOut(bool isFading)
	{
		_isFadingOut = isFading;
	}

	void EnableAdjustableAlpha(bool isAlpha)
	{
		_hasAdjustableAlpha = isAlpha;
	}

	void EnableAlpha(bool isAlpha)
	{
		_hasAlpha = isAlpha;
	}

	void EnableFlickering(bool isAlpha)
	{
		_isFlickering = isAlpha;
	}

	void SetAlpha(float alphaValue);
	float GetAlpha();
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


	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override
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

	void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator)
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

	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
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
		return _layer;
	}
	void SetRenderLayer(int state);


	unsigned& GetTypeId();

	GraphicComponent* CloneComponent() { return new GraphicComponent(*this); }
};












