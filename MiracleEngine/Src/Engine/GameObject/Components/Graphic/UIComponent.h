#pragma once
#include "../../IComponent.h"


class UIComponent : public IComponent
{
private:

	std::string _fileName;
	//unsigned int _textureID;

public:

	const std::string& GetFileName() const;
	void SetFileName(const std::string& filename);


	std::string ComponentName() const override;
	void SerialiseComponent(Serialiser& document) override
	{
		if (document.HasMember("UI.FileName") && document["UI.FileName"].IsString())
			_fileName = document["UI.FileName"].GetString();
	}

	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override
	{
		rapidjson::Value value;

		value.SetString(rapidjson::StringRef(_fileName.c_str()));
		prototypeDoc.AddMember("UI.FileName", value);
	}


	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
	{
		UIComponent* protoIdentityCom = dynamic_cast<UIComponent*>(protoCom);

		bool addComponentIntoSceneFile = false;

		rapidjson::Value filename;
		if (protoIdentityCom->_fileName.compare(_fileName))	//If audiofile of Object is diff from prototype
		{
			addComponentIntoSceneFile = true;
			filename.SetString(rapidjson::StringRef(_fileName.c_str()));

		}

		if (addComponentIntoSceneFile)	//If anyone of component data of obj is different from Prototype
		{
			value.AddMember("UIComponent", rapidjson::Value(true), allocator);
			
			if (filename.IsNull())
			{
				value.AddMember("UI.FileName", filename, allocator);
			}
		}
	}


	virtual void Inspect() override
	{
		IComponent::Inspect();
	}

	void DeserialiseComponentSceneFile(IComponent* protoCom, DeSerialiser& SceneFile) { 
	
	}


	//Constructor
	UIComponent();
	virtual ~UIComponent();
	UIComponent(const UIComponent& rhs);
	UIComponent& operator=(const UIComponent& rhs);

	UIComponent* CloneComponent() { return new UIComponent(*this); }
};

