#pragma once


#include <string>


class FontComponent : public IComponentSystem
{
public:
	void SetFontID(int num)
	{
		_fontID = num;
	}


	void SerialiseComponent(Serialiser& document) override;

	std::string ComponentName() const override
	{
		return "Font Component";
	}

	std::string GetFontString()
	{
		return _fontString;
	}

	virtual void Inspect() override
	{
		
	}


private:
	int _fontID;
	std::string _fontString;
};