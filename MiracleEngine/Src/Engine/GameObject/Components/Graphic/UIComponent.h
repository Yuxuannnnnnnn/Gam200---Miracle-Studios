#pragma once
#include "../../IComponent.h"
#include "Tools/Resource/ResourceSystem.h"
#include "Editor/ImguiFunctions.h"

class UIComponent : public IComponent
{
private:
	std::string _fileName;
	//unsigned int _textureID;

	
	// has alpha from PNG
	bool _hasAlpha{false};

	// has alpha adjustable in programming
	bool _hasAdjustableAlpha; //when the button is ticked, _alphaVal is taken into account
	float _alphaVal;	//alpha value is between 0 to 1

	bool _isFadingOut; //if box is checked, the object will slowly fade out
	bool _isFlickering;//if box is checked, the objecy will randomly flicker on and off

	int _layer;



public:
	bool HasAlpha() const;
	bool HasAdjustableAlpha() const;
	bool IsFadingOut() const;
	bool IsFlickering() const;
	float GetValue() const;

	const std::string& GetFileName() const;
	void SetFileName(const std::string& filename);


	std::string ComponentName() const override;
	void SerialiseComponent(Serialiser& document) override
	{
		if (document.HasMember("UIComponent") && document["UIComponent"].IsBool())
			SetEnable(document["UIComponent"].GetBool());

		if (document.HasMember("UI.FileName") && document["UI.FileName"].IsString())
			_fileName = document["UI.FileName"].GetString();

		if (document.HasMember("UI.Layer") && document["UI.Layer"].IsInt())	//Checks if the variable exists in .Json file
		{
			_layer = (document["UI.Layer"].GetInt());
		}

		if (document.HasMember("UI.HasAlpha") && document["UI.HasAlpha"].IsBool())	//Checks if the variable exists in .Json file
		{
			_hasAlpha = (document["UI.HasAlpha"].GetBool());
		}
	}

	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override
	{
		rapidjson::Value value;

		value.SetBool(GetEnable());
		prototypeDoc.AddMember("UIComponent", value);

		value.SetString(rapidjson::StringRef(_fileName.c_str()));
		prototypeDoc.AddMember("UI.FileName", value);

		value.SetInt(_layer);
		prototypeDoc.AddMember("UI.Layer", value);

		value.SetBool(_hasAlpha);
		prototypeDoc.AddMember("UI.HasAlpha", value);
	}

	void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator)
	{
		rapidjson::Value value;

		value.SetBool(GetEnable());
		prototypeDoc.AddMember("UIComponent", value, allocator);


		value.SetString(rapidjson::StringRef(_fileName.c_str()));
		prototypeDoc.AddMember("UI.FileName", value, allocator);

		value.SetInt(_layer);
		prototypeDoc.AddMember("UI.Layer", value, allocator);

		value.SetBool(_hasAlpha);
		prototypeDoc.AddMember("UI.HasAlpha", value, allocator);
	}


	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
	{
		UIComponent* protoIdentityCom = dynamic_cast<UIComponent*>(protoCom);

		if (!protoIdentityCom)
		{
			DeSerialiseComponent(value, allocator);
			return;
		}

		bool addComponentIntoSceneFile = false;

		rapidjson::Value enable;
		rapidjson::Value filename;
		rapidjson::Value layer;
		rapidjson::Value HasAlpha;

		if (protoIdentityCom->GetEnable() != this->GetEnable())
		{
			addComponentIntoSceneFile = true;
			enable.SetBool(GetEnable());
		}

		if (protoIdentityCom->_fileName.compare(_fileName))	//If audiofile of Object is diff from prototype
		{
			addComponentIntoSceneFile = true;
			filename.SetString(rapidjson::StringRef(_fileName.c_str()));

		}

		if (protoIdentityCom->_layer != _layer)
		{
			addComponentIntoSceneFile = true;
			layer.SetInt(_layer);
		}		
		
		if (protoIdentityCom->_hasAlpha != _hasAlpha)
		{
			addComponentIntoSceneFile = true;
			HasAlpha.SetBool(_hasAlpha);
		}

		if (addComponentIntoSceneFile)	//If anyone of component data of obj is different from Prototype
		{
			if (!enable.IsNull())
				value.AddMember("UIComponent", enable, allocator);
			else
				value.AddMember("UIComponent", protoIdentityCom->GetEnable(), allocator);

			if (!filename.IsNull())
			{
				value.AddMember("UI.FileName", filename, allocator);
			}

			if (!layer.IsNull())
			{
				value.AddMember("UI.Layer", layer, allocator);
			}

			if (!HasAlpha.IsNull())
			{
				value.AddMember("UI.HasAlpha", HasAlpha, allocator);
			}
		}
	}


	virtual void Inspect() override
	{
		IComponent::Inspect();

		ImGui::Spacing();
		ImGui::Spacing();

		_layer -= 100;

		ImGui::InputInt("RenderLayer", &_layer);
		if (_layer > 10)
			_layer = 10;
		else if (_layer < 0)
			_layer = 0;

		_layer += 100;

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


		ImGui::Spacing();
		ImGui::Spacing();


		ImGui::Checkbox("Has Alpha", &_hasAlpha);
	}


	//Constructor
	UIComponent();
	virtual ~UIComponent();
	UIComponent(const UIComponent& rhs) = default;
	UIComponent& operator=(const UIComponent& rhs) = default;

	int GetRenderLayer()
	{
		return _layer;
	}

	virtual void Init() override;
	virtual void LoadResource() override;

	UIComponent* CloneComponent() { return new UIComponent(*this); }
};

