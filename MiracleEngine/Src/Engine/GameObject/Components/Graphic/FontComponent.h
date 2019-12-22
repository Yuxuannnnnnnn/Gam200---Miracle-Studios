#pragma once


#include <string>


class FontComponent : public IComponent
{
private:
	std::string _fontString;
	std::string _fontType;

// -remove below----
	int _fontID;
public:
	void SerialiseComponent(Serialiser& document) override;
	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override;
	
	void SetFontID(int num);



	std::string ComponentName() const override;

	std::string& GetFontString();


	virtual void Inspect() override;

	void SetString(std::string in)
	{
		_fontString = in;
	}


};