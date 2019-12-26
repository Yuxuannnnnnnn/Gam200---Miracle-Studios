#pragma once


#include <string>


class FontComponent : public IComponent
{
private:
	std::string _fontString;
	std::string _fontType;


public:
	void SerialiseComponent(Serialiser& document) override;
	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override;




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