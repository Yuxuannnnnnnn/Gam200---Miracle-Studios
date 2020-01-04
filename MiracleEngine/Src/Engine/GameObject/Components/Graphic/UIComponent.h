#pragma once
#include "../../IComponent.h"
#include "GameObject/IAllocator.h"


class UIComponent : public IComponent, public IBase<UIComponent>
{
private:

	std::string _fileName;
	unsigned int _textureID;

public:

	const std::string& GetFileName() const;
	void SetFileName(const std::string& filename);


	std::string ComponentName() const override;
	void SerialiseComponent(Serialiser& document) override
	{
		if (document.HasMember("G.FileName") && document["G.FileName"].IsString())
			_fileName = document["G.FileName"].GetString();
	}

	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override
	{
		rapidjson::Value value;

		value.SetString(rapidjson::StringRef(_fileName.c_str()));
		prototypeDoc.AddMember("G.FileName", value);
	}


	virtual void Inspect() override;

	void DeserialiseComponentSceneFile(IComponent* protoCom, DeSerialiser& SceneFile) { 
	
	}


	//Constructor
	UIComponent();
	virtual ~UIComponent();
	UIComponent(const UIComponent& rhs);
	UIComponent& operator=(const UIComponent& rhs);
};

