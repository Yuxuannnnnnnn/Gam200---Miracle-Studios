#pragma once


#include <string>


class FontComponent : public IComponent
{
private:
	std::string _fontString;
	std::string _fontType;


public:
	void SerialiseComponent(Serialiser& document) override
	{

		if (document.HasMember("FontString") && document["FontString"].IsString())	//Checks if the variable exists in .Json file
		{
			_fontString = (document["FontString"].GetString());
		}


		if (document.HasMember("FontType") && document["FontType"].IsString())	//Checks if the variable exists in .Json file
		{
			_fontString = (document["FontType"].GetString());
		}
	}


	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override 
	{
		rapidjson::Value value;

		value.SetBool(true);
		prototypeDoc.AddMember("FontComponent", rapidjson::Value(true));

		value.SetString(rapidjson::StringRef(_fontString.c_str()));
		prototypeDoc.AddMember("FontString", value);

		value.SetString(rapidjson::StringRef(_fontString.c_str()));
		prototypeDoc.AddMember("FontType", value);
	}



	virtual void DeserialiseComponentSceneFile(IComponent* protoCom, DeSerialiser& SceneFile) override
	{
		FontComponent* protoFontCom = dynamic_cast<FontComponent*>(protoCom);

		rapidjson::Value fontString;
		rapidjson::Value fontType;
		bool addComponentIntoSceneFile = false;

		if (protoFontCom->_fontString.compare(_fontString))
		{
			addComponentIntoSceneFile = true;
			fontString.SetString(rapidjson::StringRef(_fontString.c_str()));
		}

		if (protoFontCom->_fontType.compare(_fontType))
		{
			addComponentIntoSceneFile = true;
			fontType.SetString(rapidjson::StringRef(_fontType.c_str()));
		}


		if (addComponentIntoSceneFile)	//If anyone of component data of obj is different from Prototype
		{
			SceneFile.AddMember("FontComponent", rapidjson::Value(true));

			if (!fontType.IsNull())	//if rapidjson::value container is not empty
			{
				SceneFile.AddMember("FontId", fontType);
			}

			if (!fontString.IsNull())
			{
				SceneFile.AddMember("FontString", fontString);
			}
		}

	}


	std::string ComponentName() const override;

	std::string& GetFontString();

	const std::string& GetFontType()
	{
		return _fontType;
	}

	virtual void Inspect() override;

	void SetString(std::string in)
	{
		_fontString = in;
	}


};