#pragma once


#include <string>


class FontComponent : public IComponent
{
private:
	std::string _fontString;
	std::string _fontType;

	/*
	float _r;
	float _g;
	float _b;
	float _a;

	*/


	float _color[4] = { 1.0f,1.0f,1.0f,1.0f }; //color of font


	float _delayTime = 0.0f; //how long it takes to show the entire font object 
	bool _isDelayedText = false;


	/* dont need serialize private var below*/
	bool _startDisplaying = false; //start feature of showing one character at a time
									//Script will set to true


	float _currentDelaytime = 200.0f;
	size_t _fontCounter = 0;

public:
	size_t GetFontCounter();
	void SetFontCounter(size_t count);

	float GetCurrentDelayTime() const;
	void SetCurrentDelayTime(float time);

	void SetFontColor(const glm::vec3& color);
	glm::vec3 GetFontColor() const;

	float GetDelayTime() const;
	void SetDelayTime(float time);

	bool IsStartDisplaying() const;
	void  SetStartDisplaying(bool start);

	bool IsDelayedText();
	void SetisDelayedText(bool text);

	void SetText(const std::string& text);
	std::string GetText();


	void SetFontType(const std::string& type);
	std::string GetType();


	void SerialiseComponent(Serialiser& document) override
	{

		if (document.HasMember("FontComponent") && document["FontComponent"].IsBool())
			SetEnable(document["FontComponent"].GetBool());

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

		value.SetBool(GetEnable());
		prototypeDoc.AddMember("FontComponent", value);

		value.SetString(rapidjson::StringRef(_fontString.c_str()));
		prototypeDoc.AddMember("FontString", value);

		value.SetString(rapidjson::StringRef(_fontString.c_str()));
		prototypeDoc.AddMember("FontType", value);
	}

	void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator)
	{
		rapidjson::Value value;

		value.SetBool(GetEnable());
		prototypeDoc.AddMember("FontComponent", value, allocator);

		value.SetString(rapidjson::StringRef(_fontString.c_str()));
		prototypeDoc.AddMember("FontString", value, allocator);

		value.SetString(rapidjson::StringRef(_fontString.c_str()));
		prototypeDoc.AddMember("FontType", value, allocator);
	}


	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
	{
		FontComponent* protoFontCom = dynamic_cast<FontComponent*>(protoCom);

		if (!protoFontCom)
		{
			DeSerialiseComponent(value, allocator);
			return;
		}

		rapidjson::Value enable;
		rapidjson::Value fontString;
		rapidjson::Value fontType;
		bool addComponentIntoSceneFile = false;

		if (protoFontCom->GetEnable() != this->GetEnable())
		{
			addComponentIntoSceneFile = true;
			enable.SetBool(GetEnable());
		}

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
			if (enable.IsNull())
				value.AddMember("FontComponent", enable, allocator);
			else
				value.AddMember("FontComponent", protoFontCom->GetEnable(), allocator);

			if (!fontType.IsNull())	//if rapidjson::value container is not empty
			{
				value.AddMember("FontType", fontType, allocator);
			}

			if (!fontString.IsNull())
			{
				value.AddMember("FontString", fontString, allocator);
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

	FontComponent* CloneComponent() { return new FontComponent(*this); }
};